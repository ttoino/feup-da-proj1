#include "../includes/van.hpp"

Van::Van(int maxVol, int maxWeight, int cost) : maxVolume(maxVol), maxWeight(maxWeight), cost(cost) {};

int Van::getMaxVolume() const { return this->maxVolume; };
int Van::getMaxWeight() const { return this->maxWeight; };
int Van::getCost() const { return this->cost; };