#include <fstream>

#include "../includes/constants.hpp"
#include "../includes/utils.hpp"
#include "../includes/van.hpp"

Van::Van(int maxVol, int maxWeight, int cost)
    : maxVolume(maxVol), currentVolume(0), maxWeight(maxWeight),
      currentWeight(0), cost(cost){};

int Van::getMaxVolume() const { return this->maxVolume; };
int Van::getMaxWeight() const { return this->maxWeight; };
int Van::getCost() const { return this->cost; };
int Van::getCurrentVolume() const { return this->currentVolume; };
int Van::getCurrentWeight() const { return this->currentWeight; };

Van Van::from(const std::vector<std::string> &tokens) {
    int maxVol = std::stoi(tokens.at(0));
    int maxWeight = std::stoi(tokens.at(1));
    int cost = std::stoi(tokens.at(2));

    return Van{maxVol, maxWeight, cost};
}

std::vector<Van> Van::processDataset() {

    std::ifstream dataset_file{VANS_FILE_PATH};

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
    out << v.getMaxVolume() << '\t' << v.getMaxWeight() << '\t' << v.getCost();

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

bool compareVanByVolume(const Van &v1, const Van &v2) {
    if (v1.getMaxVolume() == v2.getMaxVolume()) {
        return v1.getMaxWeight() > v2.getMaxWeight();
    }
    return v1.getMaxVolume() > v2.getMaxVolume();
}

bool compareVanByWeight(const Van &v1, const Van &v2) {
    if (v1.getMaxWeight() == v2.getMaxWeight()) {
        return v1.getMaxVolume() > v2.getMaxVolume();
    }
    return v1.getMaxWeight() > v2.getMaxWeight();
}

bool compareVanByArea(const Van &v1, const Van &v2) {
    return v1.getMaxVolume() * v1.getMaxWeight() >
           v2.getMaxVolume() * v2.getMaxWeight();
}
