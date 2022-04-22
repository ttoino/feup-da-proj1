#include <fstream>
#include <numeric>
#include <random>

#include "../includes/constants.hpp"
#include "../includes/utils.hpp"
#include "../includes/van.hpp"

unsigned int Van::GLOBAL_ID = 1;

Van::Van(unsigned int maxVol, unsigned int maxWeight, unsigned int cost)
    : maxVolume(maxVol), currentVolume(0), maxWeight(maxWeight),
      currentWeight(0), cost(cost), id(Van::GLOBAL_ID++){};

unsigned int Van::getMaxVolume() const { return this->maxVolume; };
unsigned int Van::getMaxWeight() const { return this->maxWeight; };
unsigned int Van::getCost() const { return this->cost; };
unsigned int Van::getCurrentVolume() const { return this->currentVolume; };
unsigned int Van::getCurrentWeight() const { return this->currentWeight; };
std::vector<Order> Van::getOrders() const { return this->orders; };

Van Van::from(const std::vector<std::string> &tokens) {
    unsigned int maxVol = std::stoul(tokens.at(0));
    unsigned int maxWeight = std::stoul(tokens.at(1));
    unsigned int cost = std::stoul(tokens.at(2));

    return Van{maxVol, maxWeight, cost};
}

std::vector<Van> Van::processDataset(const std::string &path) {
    GLOBAL_ID = 1;

    std::ifstream dataset_file{DATASETS_PATH + path + VANS_FILE};

    if (!dataset_file.is_open())
        return {};

    std::string line;
    std::vector<Van> result;

    std::getline(dataset_file, line); // ignore dataset header

    while (std::getline(dataset_file, line))
        result.push_back(Van::from(split(line, ' ')));

    return result;
}

std::vector<Van> Van::generateDataset(const std::string &name,
                                      const DatasetGenerationParams &params) {
    std::vector<Van> vans{params.numberOfVans, {0, 0, 0}};

    GLOBAL_ID = 1;

    std::ofstream dataset_file{DATASETS_PATH + name + VANS_FILE};

    if (!dataset_file.is_open())
        return {};

    dataset_file << VANS_HEADER;

    // Setup random generators
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Generate vans
    std::uniform_int_distribution vanWeightDist{params.minVanWeight,
                                                params.maxVanWeight},
        vanVolumeDist{params.minVanVolume, params.maxVanVolume},
        vanCostDist{params.minVanCost, params.maxVanCost};

    for (Van &v : vans) {
        v = {
            vanVolumeDist(gen),
            vanWeightDist(gen),
            vanCostDist(gen),
        };

        dataset_file << v.maxVolume << ' ' << v.maxWeight << ' ' << v.cost
                     << '\n';
    }

    return vans;
}

std::ostream &operator<<(std::ostream &out, const Van &v) {
    if (v.getCurrentVolume() > 0)
        out << v.getCurrentVolume() << '/';

    out << v.getMaxVolume() << '\t';

    if (v.getCurrentWeight() > 0)
        out << v.getCurrentWeight() << '/';

    out << v.getMaxWeight() << '\t' << v.getCost();

    if (!v.getOrders().empty())
        out << '\t' << v.getOrders().size();

    return out;
}

bool Van::canFit(const Order &o) const {
    return getCurrentVolume() + o.getVolume() <= getMaxVolume() &&
           getCurrentWeight() + o.getWeight() <= getMaxWeight();
}

bool Van::addOrder(const Order &order) {
    if (!canFit(order))
        return false;

    orders.push_back(order);
    this->currentVolume += order.getVolume();
    this->currentWeight += order.getWeight();
    return true;
}

bool Van::compareByVolume(const Van &v1, const Van &v2) {
    if (v1.getMaxVolume() == v2.getMaxVolume()) {
        return v1.getMaxWeight() > v2.getMaxWeight();
    }
    return v1.getMaxVolume() > v2.getMaxVolume();
}

bool Van::compareByWeight(const Van &v1, const Van &v2) {
    if (v1.getMaxWeight() == v2.getMaxWeight()) {
        return v1.getMaxVolume() > v2.getMaxVolume();
    }
    return v1.getMaxWeight() > v2.getMaxWeight();
}

bool Van::compareByArea(const Van &v1, const Van &v2) {
    return v1.getMaxVolume() * v1.getMaxWeight() >
           v2.getMaxVolume() * v2.getMaxWeight();
}

bool Van::compareByVolumeOverCost(const Van &v1, const Van &v2) {
    return (double)v1.getMaxVolume() / v1.getCost() >
           (double)v2.getMaxVolume() / v2.getCost();
}

bool Van::compareByWeightOverCost(const Van &v1, const Van &v2) {
    return (double)v1.getMaxWeight() / v1.getCost() >
           (double)v2.getMaxWeight() / v2.getCost();
}

bool Van::compareByAreaOverCost(const Van &v1, const Van &v2) {
    return (double)v1.getMaxVolume() * v1.getMaxWeight() / v1.getCost() >
           (double)v2.getMaxVolume() * v2.getMaxWeight() / v2.getCost();
}
