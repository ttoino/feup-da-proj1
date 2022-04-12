#include "../includes/scenario1.hpp"

#include <vector>
#include <algorithm>

Data scenario1(std::string &option) {
    Data data;
    Dataset dataset = Dataset::load();
    data.orders = dataset.getOrders();
    data.vans = dataset.getVans();

    if(option == "volume") {
        std::sort(data.vans.begin(), data.vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxWeight() == v2.getMaxWeight()) {
                return v1.getMaxWeight() > v2.getMaxWeight();
            }
            return v1.getMaxVolume() > v2.getMaxVolume();
        });

        std::sort(data.orders.begin(), data.orders.end(), [] (const Order &order1, const Order &order2) {
            if(order1.getVolume() == order2.getVolume()) {
                return order1.getWeight() < order2.getWeight();
            }
            return order1.getVolume() < order2.getVolume();
        });
    } else if (option == "weight") {
        std::sort(data.vans.begin(), data.vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxVolume() == v2.getMaxVolume()) {
                return v1.getMaxVolume() > v2.getMaxVolume();
            }
            return v1.getMaxWeight() > v2.getMaxWeight();
        });

        std::sort(data.orders.begin(), data.orders.end(), [] (const Order &order1, const Order &order2) {
            if(order1.getWeight() == order2.getWeight()) {
                return order1.getVolume() < order2.getVolume();
            }
            return order1.getWeight() < order2.getWeight();
        });
    } else {
        std::cerr << "Invalid option\n";
    }

    auto vanIterator = data.vans.begin();
    auto orderIterator = data.orders.begin();

    while (
        vanIterator != data.vans.end() && // while we still have vans to carry orders
        orderIterator != data.orders.end() // while we still have orders to process
    ) {
        if (!orderIterator->fitsIn(*vanIterator)){ // we have exhausted the current van, move to the next one
            vanIterator++;
            data.vansUsed++;
        }

        if (vanIterator != data.vans.end()) {
            vanIterator->addOrder(*orderIterator++);
            data.ordersDispatched++;
        }
    }

    return data;
}
