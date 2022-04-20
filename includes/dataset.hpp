#ifndef DA_PROJ1_DATASET_H
#define DA_PROJ1_DATASET_H

#include <string>
#include <vector>

#include "order.hpp"
#include "van.hpp"

class Dataset {
    std::vector<Van> vans;
    std::vector<Order> orders;

public:
    const std::vector<Van> &getVans() const { return vans; };
    const std::vector<Order> &getOrders() const { return orders; };

    static Dataset load(const std::string &path);
};

#endif
