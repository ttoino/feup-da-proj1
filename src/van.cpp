#include <fstream>
#include <numeric>

#include "../includes/constants.hpp"
#include "../includes/utils.hpp"
#include "../includes/van.hpp"

int Van::GLOBAL_ID = 1;

Van::Van(int maxVol, int maxWeight, int cost)
    : maxVolume(maxVol), currentVolume(0), maxWeight(maxWeight),
      currentWeight(0), cost(cost), id(Van::GLOBAL_ID++){};

int Van::getMaxVolume() const { return this->maxVolume; };
int Van::getMaxWeight() const { return this->maxWeight; };
int Van::getCost() const { return this->cost; };
int Van::getCurrentVolume() const { return this->currentVolume; };
int Van::getCurrentWeight() const { return this->currentWeight; };
std::vector<Order> Van::getOrders() const { return this->orders; };

Van Van::from(const std::vector<std::string> &tokens) {
    int maxVol = std::stoi(tokens.at(0));
    int maxWeight = std::stoi(tokens.at(1));
    int cost = std::stoi(tokens.at(2));

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

std::ostream &operator<<(std::ostream &out, const Van &v) {
    if (v.getCurrentVolume())
        out << v.getCurrentVolume() << '/';

    out << v.getMaxVolume() << '\t';

    if (v.getCurrentWeight())
        out << v.getCurrentWeight() << '/';

    out << v.getMaxWeight() << '\t' << v.getCost();

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

void Van::printStatistics(std::ostream &out) const {

    out << "Van with id=" << this->id << ": \n";

    out << "\tVolume: " << this->getMaxVolume()
        << "\n\tWeight: " << this->getMaxWeight() << "\n\n";

    int totalWeight = std::accumulate(
        this->orders.begin(), this->orders.end(),
        static_cast<int>(0), // to ensure result is an integer value
        [](int accum, const Order &order) -> int {
            return accum + order.getWeight();
        });
    int totalVolume = std::accumulate(
        this->orders.begin(), this->orders.end(),
        static_cast<int>(0), // to ensure result is an integer value
        [](int accum, const Order &order) -> int {
            return accum + order.getVolume();
        });
    int totalReward = std::accumulate(
        this->orders.begin(), this->orders.end(),
        static_cast<int>(0), // to ensure result is an integer value
        [](int accum, const Order &order) -> int {
            return accum + order.getReward();
        });

    out << "\t- Carries " << this->orders.size() << " orders, totaling:"
        << "\n";
    out << "\t\t- Volume: " << totalVolume << ", volume efficiency: "
        << (totalVolume * 100.0f / this->getMaxVolume()) << "%\n";
    out << "\t\t- Weight: " << totalWeight << ", weight efficiency: "
        << (totalWeight * 100.0f / this->getMaxWeight()) << "%\n";
    out << "\t\t- Total order reward: " << totalReward
        << ", transportation cost: " << this->getCost()
        << ", profit: " << (totalReward - this->getCost()) << '\n';

    out << '\n';
};

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

bool Van::compareByCostDivision(const Van &v1, const Van &v2) {
    return ((v1.getMaxVolume() * v1.getMaxVolume()) / v1.getCost()) >
           ((v2.getMaxVolume() * v2.getMaxWeight()) / v2.getCost());
}

bool Van::compareByCostMult(const Van &v1, const Van &v2) {
    return v1.getMaxWeight() * v1.getMaxVolume() * v1.getCost() <
           v2.getMaxVolume() * v2.getMaxWeight() * v2.getCost();
}
