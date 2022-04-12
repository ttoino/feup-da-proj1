#include "../includes/scenario1.hpp"

#include <vector>
#include <algorithm>

Dataset scenario1(std::string &option) {
    Dataset dataset = Dataset::load();
    std::vector<Order> orders = dataset.getOrders();
    std::vector<Van> vans = dataset.getVans();

    if(option == "volume") {
        std::sort(vans.begin(), vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxWeight() == v2.getMaxWeight()) {
                return v1.getMaxWeight() > v2.getMaxWeight();
            }
            return v1.getMaxVolume() > v2.getMaxVolume();
        });

        std::sort(orders.begin(), orders.end(), [] (const Order &order1, const Order &order2) {
            if(order1.getVolume() == order2.getVolume()) {
                return order1.getWeight() < order2.getWeight();
            }
            return order1.getVolume() < order2.getVolume();
        });
    } else if (option == "weight") {
        std::sort(vans.begin(), vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxVolume() == v2.getMaxVolume()) {
                return v1.getMaxVolume() > v2.getMaxVolume();
            }
            return v1.getMaxWeight() > v2.getMaxWeight();
        });

        std::sort(orders.begin(), orders.end(), [] (const Order &order1, const Order &order2) {
            if(order1.getWeight() == order2.getWeight()) {
                return order1.getVolume() < order2.getVolume();
            }
            return order1.getWeight() < order2.getWeight();
        });
    } else {
        std::cerr << "Invalid option\n";
    }
    
    auto vanIterator = vans.begin();
    auto orderIterator = orders.begin();

    while (
        vanIterator != vans.end() && // while we still have vans to carry orders
        orderIterator != orders.end() // while we still have orders to process
    ) {
        if (!orderIterator->fitsIn(*vanIterator)) // we have exhausted the current van, move to the next one
            vanIterator++;

        if (vanIterator != vans.end())
            vanIterator->addOrder(*orderIterator++);
    }

    return dataset;
}
