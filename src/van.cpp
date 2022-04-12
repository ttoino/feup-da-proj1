#include <fstream>

#include "../includes/constants.hpp"
#include "../includes/utils.hpp"
#include "../includes/van.hpp"

Van::Van(int maxVol, int maxWeight, int cost)
    : maxVolume(maxVol), maxWeight(maxWeight), cost(cost){};

int Van::getMaxVolume() const { return this->maxVolume; };
int Van::getMaxWeight() const { return this->maxWeight; };
int Van::getCost() const { return this->cost; };

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
