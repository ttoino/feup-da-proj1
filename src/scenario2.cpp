#include "../includes/scenario2.hpp"

#include <vector>

SimulationResult Simulation2::run() {
    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};
    std::vector<Van> vans = dataset.getVans(), resultVans = {};

    int ordersForTheDay = orders.size();
    int vansForTheDay = vans.size();

    int vansUsed = 0, ordersDispatched = 0;
    int cost = 0, reward = 0;
    double deliveryTime = 0.0;

    if(option == Simulation2::SimulationOptions::DIVIDE) {
        std::sort(vans.begin(), vans.end(), compareVanByCostDivision);
        std::sort(orders.begin(), orders.end(), compareOrderByRewardDivision);
    } else if (option == Simulation2::SimulationOptions::MULTIPLY) {
        std::sort(vans.begin(), vans.end(), compareVanByCostMult);
        std::sort(orders.begin(), orders.end(), compareOrderByRewardMult);
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
            cost += vanIterator->getCost();
            vanIterator++;
            vansUsed++;
        }

        if (vanIterator != vans.end()) {
            deliveryTime += orderIterator->getDuration();
            reward += orderIterator->getReward();
            vanIterator->addOrder(*orderIterator++);
            ordersDispatched++;
        }
    }

    remainingOrders.assign(orderIterator, orders.end());

    return {remainingOrders, resultVans,    vansUsed,    ordersDispatched,
            ordersForTheDay, vansForTheDay,     deliveryTime,   cost, reward};
}
