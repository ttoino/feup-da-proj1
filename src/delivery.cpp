#include "../includes/delivery.hpp"

Delivery::Delivery(int vol, int weight, int reward, int duration) : volume(vol), weight(weight), reward(reward), duration(duration) {};

int Delivery::getVolume() const { return this->volume; }
int Delivery::getWeight() const { return this->weight; }
int Delivery::getReward() const { return this->reward; }
int Delivery::getDuration() const { return this->duration; }

Delivery Delivery::from(const std::vector<std::string> &tokens) {

    int vol = std::stoi(tokens.at(0));
    int weight = std::stoi(tokens.at(1));
    int reward = std::stoi(tokens.at(2));
    int duration = std::stoi(tokens.at(3));

    return Delivery{vol, weight, reward, duration};
}