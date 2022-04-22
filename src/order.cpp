#include <fstream>
#include <random>

#include "../includes/constants.hpp"
#include "../includes/order.hpp"
#include "../includes/utils.hpp"

unsigned int Order::GLOBAL_ID = 1;

Order::Order(unsigned int vol, unsigned int weight, unsigned int reward,
             unsigned int duration)
    : volume(vol), weight(weight), reward(reward), duration(duration),
      id(GLOBAL_ID++){};

unsigned int Order::getVolume() const { return this->volume; }
unsigned int Order::getWeight() const { return this->weight; }
unsigned int Order::getReward() const { return this->reward; }
unsigned int Order::getDuration() const { return this->duration; }

Order Order::from(const std::vector<std::string> &tokens) {
    unsigned int vol = std::stoul(tokens.at(0));
    unsigned int weight = std::stoul(tokens.at(1));
    unsigned int reward = std::stoul(tokens.at(2));
    unsigned int duration = std::stoul(tokens.at(3));

    return Order{vol, weight, reward, duration};
}

std::vector<Order> Order::processDataset(const std::string &path) {
    GLOBAL_ID = 1;

    std::ifstream dataset_file{DATASETS_PATH + path + ORDERS_FILE};

    if (!dataset_file.is_open())
        return {};

    std::string line;
    std::vector<Order> result;

    std::getline(dataset_file, line); // ignore dataset header

    while (std::getline(dataset_file, line))
        result.push_back(Order::from(split(line, ' ')));

    return result;
}

std::vector<Order>
Order::generateDataset(const std::string &name,
                       const DatasetGenerationParams &params) {
    std::vector<Order> orders{params.numberOfOrders, {0, 0, 0, 0}};

    GLOBAL_ID = 1;

    std::ofstream dataset_file{DATASETS_PATH + name + ORDERS_FILE};

    if (!dataset_file.is_open())
        return {};

    dataset_file << ORDERS_HEADER;

    // Setup random generators
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Generate orders
    std::uniform_int_distribution orderWeightDist{params.minOrderWeight,
                                                  params.maxOrderWeight},
        orderVolumeDist{params.minOrderVolume, params.maxOrderVolume},
        orderRewardDist{params.minOrderReward, params.maxOrderReward},
        orderDurationDist{params.minOrderDuration, params.maxOrderDuration};

    for (Order &o : orders) {
        o = {
            orderVolumeDist(gen),
            orderWeightDist(gen),
            orderRewardDist(gen),
            orderDurationDist(gen),
        };

        dataset_file << o.volume << ' ' << o.weight << ' ' << o.reward << ' '
                     << o.duration << '\n';
    }

    return orders;
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
