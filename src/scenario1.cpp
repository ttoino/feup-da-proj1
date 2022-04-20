#include "../includes/scenario1.hpp"

#include <algorithm>
#include <vector>

SimulationResult Simulation1::run(const Dataset &dataset) {
    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};
    std::vector<Van> vans = dataset.getVans(), resultVans = {};

    int ordersForTheDay = orders.size();
    int vansForTheDay = vans.size();

    int vansUsed = 0, ordersDispatched = 0;
    double deliveryTime = 0.0;

    if (this->option == Simulation1::SimulationOptions::VOLUME) {
        std::sort(vans.begin(), vans.end(), compareVanByVolume);
        std::sort(orders.begin(), orders.end(), compareOrderByVolume);
    } else if (this->option == Simulation1::SimulationOptions::WEIGHT) {
        std::sort(vans.begin(), vans.end(), compareVanByWeight);
        std::sort(orders.begin(), orders.end(), compareOrderByWeight);
    } else if (this->option == Simulation1::SimulationOptions::AREA) {
        std::sort(vans.begin(), vans.end(), compareVanByArea);
        std::sort(orders.begin(), orders.end(), compareOrderByArea);
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

    return {remainingOrders, resultVans,    vansUsed,    ordersDispatched,
            ordersForTheDay, vansForTheDay, deliveryTime};
}
