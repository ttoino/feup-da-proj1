#include "../includes/scenario3.hpp"

SimulationResult Simulation3::run() {
    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};

    double time = 0, max_time = 8 * 3600;

    std::sort(orders.begin(), orders.end(), compareOrderByDuration);

    auto i = orders.begin();
    for (; i != orders.end() && time + i->getDuration() <= max_time; ++i)
        time += time + i->getDuration();

    remainingOrders.assign(i, orders.end());

    int ordersDispatched = orders.size() - remainingOrders.size();
    return {
        remainingOrders,         {}, 1, ordersDispatched, orders.size(), 1,
        time / ordersDispatched,
    };
}