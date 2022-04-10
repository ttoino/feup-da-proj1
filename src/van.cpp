#include "../includes/van.hpp"

Van::Van(int maxVol, int maxWeight, int cost) : maxVolume(maxVol), maxWeight(maxWeight), cost(cost) {};

int Van::getMaxVolume() const { return this->maxVolume; };
int Van::getMaxWeight() const { return this->maxWeight; };
int Van::getCost() const { return this->cost; };

Van Van::from(const std::vector<std::string> &tokens) {
    
    int maxVol = std::stoi(tokens.at(0));
    int maxWeigth = std::stoi(tokens.at(1));
    int cost = std::stoi(tokens.at(2));

    return Van{maxVol, maxWeigth, cost};
}