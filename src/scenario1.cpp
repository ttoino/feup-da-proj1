#include "../includes/scenario1.hpp"

#include <algorithm>
#include <vector>

SimulationResult Simulation1::run() {

    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};
    std::vector<Van> vans = dataset.getVans(), resultVans = {};

    int ordersForTheDay = orders.size();
    int vansForTheDay = vans.size();

    int vansUsed = 0, ordersDispatched = 0;
    double deliveryTime = 0.0;

    if (this->option == Simulation1::SimulationOptions::VOLUME) {
        std::sort(vans.begin(), vans.end(), [](const Van &v1, const Van &v2) {
            if (v1.getMaxWeight() == v2.getMaxWeight()) {
                return v1.getMaxWeight() > v2.getMaxWeight();
            }
            return v1.getMaxVolume() > v2.getMaxVolume();
        });

        std::sort(orders.begin(), orders.end(),
                  [](const Order &order1, const Order &order2) {
                      if (order1.getVolume() == order2.getVolume()) {
                          return order1.getWeight() < order2.getWeight();
                      }
                      return order1.getVolume() < order2.getVolume();
                  });
    } else if (this->option == Simulation1::SimulationOptions::WEIGHT) {
        std::sort(vans.begin(), vans.end(), [](const Van &v1, const Van &v2) {
            if (v1.getMaxVolume() == v2.getMaxVolume()) {
                return v1.getMaxVolume() > v2.getMaxVolume();
            }
            return v1.getMaxWeight() > v2.getMaxWeight();
        });

        std::sort(orders.begin(), orders.end(),
                  [](const Order &order1, const Order &order2) {
                      if (order1.getWeight() == order2.getWeight()) {
                          return order1.getVolume() < order2.getVolume();
                      }
                      return order1.getWeight() < order2.getWeight();
                  });
    } else if (this->option == Simulation1::SimulationOptions::AREA) {
        std::sort(vans.begin(), vans.end(), [](const Van &v1, const Van &v2) {

            return v1.getMaxVolume()*v1.getMaxWeight() > v2.getMaxVolume()*v2.getMaxWeight();
        });

        std::sort(orders.begin(), orders.end(),
                    [](const Order &order1, const Order &order2) {
                        return order1.getVolume()*order1.getWeight() < order2.getVolume()*order2.getWeight();
                    });
    } else {
        std::cerr << "Invalid option\n";
        return {};
    }

    auto vanIterator = vans.begin();
    auto orderIterator = orders.begin();

    while (
        vanIterator != vans.end() && // while we still have vans to carry orders
        orderIterator != orders.end() // while we still have orders to process
    ) {
        if (!vanIterator->canFit(*orderIterator)) {
            // we have exhausted the current van, move to the next one
            resultVans.push_back(*vanIterator);
            vanIterator++;
            vansUsed++;
        }

        if (vanIterator != vans.end()) {
            deliveryTime += orderIterator->getDuration();
            vanIterator->addOrder(*orderIterator++);
            ordersDispatched++;
        }
    }

    remainingOrders.assign(orderIterator, orders.end());

    return {
        remainingOrders,  resultVans,      vansUsed,
        ordersDispatched, ordersForTheDay, vansForTheDay, deliveryTime
    };
}
