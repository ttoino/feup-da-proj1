#ifndef DA_PROJ1_DATASET_H
#define DA_PROJ1_DATASET_H

struct DatasetGenerationParams;
class Dataset;

#include <string>
#include <vector>

#include "order.hpp"
#include "van.hpp"

struct DatasetGenerationParams {
    // Order params
    int numberOfOrders{100};

    int minOrderWeight{0};
    int maxOrderWeight{100};

    int minOrderVolume{0};
    int maxOrderVolume{100};

    int minOrderReward{0};
    int maxOrderReward{100};

    int minOrderDuration{0};
    int maxOrderDuration{1000};

    // Van params
    int numberOfVans{5};

    int minVanWeight{0};
    int maxVanWeight{1000};

    int minVanVolume{0};
    int maxVanVolume{1000};

    int minVanCost{0};
    int maxVanCost{1000};
};

class Dataset {
    std::vector<Van> vans;
    std::vector<Order> orders;

    Dataset(const std::vector<Order> &orders, const std::vector<Van> &vans);

public:
    const std::vector<Van> &getVans() const { return vans; };
    const std::vector<Order> &getOrders() const { return orders; };

    static Dataset load(const std::string &path);
    static Dataset generate(const std::string &name,
                            const DatasetGenerationParams &params);
};

#endif
