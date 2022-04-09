#include "../includes/delivery.hpp"

Delivery::Delivery(int vol, int weight, int reward, int duration) : volume(vol), weight(weight), reward(reward), duration(duration) {};

int Delivery::getVolume() const { return this->volume; }
int Delivery::getWeight() const { return this->weight; }
int Delivery::getReward() const { return this->reward; }
int Delivery::getDuration() const { return this->duration; }