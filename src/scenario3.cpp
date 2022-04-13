#include "../includes/scenario3.hpp"

SimulationResult Simulation3::run() {
    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};
    std::vector<Van> vans = dataset.getVans(), resultVans = {};

    int ordersForTheDay = orders.size();
    int vansForTheDay = vans.size();

    int vansUsed = 0, ordersDispatched = 0;
    double deliveryTime = 0.0;

    std::sort(orders.begin(), orders.end(), [] (const Order &o1, const Order &o2) {
        return o1.getDuration() < o2.getDuration();
    });

    if(this->option == Simulation3::SimulationOptions::VOLUME) {
        std::sort(vans.begin(), vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxVolume() == v2.getMaxVolume()) {
                return v1.getMaxWeight() > v2.getMaxWeight();
            }
            return v1.getMaxVolume() > v2.getMaxVolume();
        });
    } else if (this->option == Simulation3::SimulationOptions::WEIGHT) {
        std::sort(vans.begin(), vans.end(), [] (const Van &v1, const Van &v2) {
            if(v1.getMaxWeight() == v2.getMaxWeight()) {
                return v1.getMaxVolume() > v2.getMaxVolume();
            }
            return v1.getMaxWeight() > v2.getMaxWeight();
        });
    } else {
        std::cerr << "Invalid option\n";
        return {};
    }

    auto orderIterator = orders.begin();
    auto vanIterator = vans.begin();

    while(
            vanIterator != vans.end() &&
            orderIterator != orders.end()
    ) {
        if(!vanIterator->canFit(*orderIterator)) {
            resultVans.push_back(*vanIterator);
            vanIterator++;
            vansUsed++;
        }

        if(vanIterator != vans.end()) {
            if(vanIterator->addOrder(*orderIterator)) {
                ordersDispatched++;
                deliveryTime += orderIterator->getDuration();
                orderIterator++;
            }

        }
    }

    remainingOrders.assign(orderIterator, orders.end());

    return {
        remainingOrders,    resultVans,    vansUsed,
        ordersDispatched,   ordersForTheDay,    vansForTheDay, deliveryTime
    };
}