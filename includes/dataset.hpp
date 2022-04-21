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
    size_t numberOfOrders{100};

    unsigned int minOrderWeight{0};
    unsigned int maxOrderWeight{100};

    unsigned int minOrderVolume{0};
    unsigned int maxOrderVolume{100};

    unsigned int minOrderReward{0};
    unsigned int maxOrderReward{100};

    unsigned int minOrderDuration{0};
    unsigned int maxOrderDuration{1000};

    // Van params
    size_t numberOfVans{5};

    unsigned int minVanWeight{0};
    unsigned int maxVanWeight{1000};

    unsigned int minVanVolume{0};
    unsigned int maxVanVolume{1000};

    unsigned int minVanCost{0};
    unsigned int maxVanCost{1000};
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
    static std::vector<std::string> getAvailableDatasets();
};

#endif
