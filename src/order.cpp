#include <fstream>

#include "../includes/constants.hpp"
#include "../includes/order.hpp"
#include "../includes/utils.hpp"

int Order::GLOBAL_ID = 1;

Order::Order(int vol, int weight, int reward, int duration)
    : volume(vol), weight(weight), reward(reward), duration(duration),
      id(GLOBAL_ID++){};

int Order::getVolume() const { return this->volume; }
int Order::getWeight() const { return this->weight; }
int Order::getReward() const { return this->reward; }
int Order::getDuration() const { return this->duration; }

Order Order::from(const std::vector<std::string> &tokens) {
    int vol = std::stoi(tokens.at(0));
    int weight = std::stoi(tokens.at(1));
    int reward = std::stoi(tokens.at(2));
    int duration = std::stoi(tokens.at(3));

    return Order{vol, weight, reward, duration};
}

std::vector<Order> Order::processDataset(const std::string &path) {
    std::ifstream dataset_file{path + ORDERS_FILE};

    if (!dataset_file.is_open())
        return {};

    std::string line;
    std::vector<Order> result;

    std::getline(dataset_file, line); // ignore dataset header

    while (std::getline(dataset_file, line))
        result.push_back(Order::from(split(line, ' ')));

    return result;
}

std::ostream &operator<<(std::ostream &out, const Order &o) {
    out << o.id << ' ' << o.getVolume() << '\t' << o.getWeight() << '\t'
        << o.getReward() << '\t' << o.getDuration();

    return out;
}

bool Order::compareByVolumeAsc(const Order &o1, const Order &o2) {
    if (o1.getVolume() == o2.getVolume()) {
        return o1.getWeight() < o2.getWeight();
    }
    return o1.getVolume() < o2.getVolume();
}

bool Order::compareByVolumeDesc(const Order &o1, const Order &o2) {
    if (o1.getVolume() == o2.getVolume()) {
        return o1.getWeight() > o2.getWeight();
    }
    return o1.getVolume() > o2.getVolume();
}

bool Order::compareByWeightAsc(const Order &o1, const Order &o2) {
    if (o1.getWeight() == o2.getWeight()) {
        return o1.getVolume() < o2.getVolume();
    }
    return o1.getWeight() < o2.getWeight();
}

bool Order::compareByWeightDesc(const Order &o1, const Order &o2) {
    if (o1.getWeight() == o2.getWeight()) {
        return o1.getVolume() > o2.getVolume();
    }
    return o1.getWeight() > o2.getWeight();
}

bool Order::compareByAreaAsc(const Order &o1, const Order &o2) {
    return o1.getVolume() * o1.getWeight() < o2.getVolume() * o2.getWeight();
}

bool Order::compareByAreaDesc(const Order &o1, const Order &o2) {
    return o1.getVolume() * o1.getWeight() > o2.getVolume() * o2.getWeight();
}

bool Order::compareByDuration(const Order &o1, const Order &o2) {
    return o1.getDuration() < o2.getDuration();
}

bool Order::compareByRewardDivision(const Order &o1, const Order &o2) {
    return ((o1.getVolume() * o1.getWeight()) / o1.getReward() <
            (o2.getVolume() * o2.getWeight()) / o2.getReward());
}

bool Order::compareByRewardMult(const Order &o1, const Order &o2) {
    return o1.getWeight() * o1.getVolume() * o1.getReward() >
           o2.getVolume() * o2.getWeight() * o2.getReward();
}
