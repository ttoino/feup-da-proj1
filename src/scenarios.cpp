#include <algorithm>
#include <limits>
#include <list>

#include "../includes/scenarios.hpp"

SimulationResult::SimulationResult(const std::vector<Order> &rorders,
                                   const std::vector<Van> &vans,
                                   const std::chrono::microseconds &runtime)
    : remainingOrders(rorders), vans(vans), runtime(runtime) {
    for (const Van &v : vans) {
        ordersDispatched += v.getOrders().size();
        cost += v.getCost();

        for (const Order &o : v.getOrders()) {
            deliveryTime += o.getDuration();
            reward += o.getReward();
        }
    }
    profit = reward - cost;

    efficiency =
        (double)ordersDispatched / (ordersDispatched + remainingOrders.size());
}

SimulationResult _firstFitBinPacking(std::vector<Order> o,
                                     std::vector<Van> vans,
                                     const VanOrdering &vanOrdering,
                                     const OrderOrdering &orderOrdering) {
    auto tstart = std::chrono::high_resolution_clock::now();

    std::sort(o.begin(), o.end(), orderOrdering);
    std::sort(vans.begin(), vans.end(), vanOrdering);

    std::list<Order> orders{o.begin(), o.end()};
    auto oi = orders.begin(), oend = orders.end();

    std::vector<Van> result;

    for (auto vi = vans.begin(), vend = vans.end();
         vi != vend && !orders.empty(); ++vi) {
        for (oi = orders.begin(); oi != oend;) {
            if (vi->canFit(*oi)) {
                vi->addOrder(*oi);
                oi = orders.erase(oi);
            } else {
                ++oi;
            }
        }

        result.push_back(*vi);
    }

    auto tend = std::chrono::high_resolution_clock::now();

    return {
        {orders.begin(), oend},
        result,
        std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart),
    };
}

const SimulationResult scenario1(const Dataset &dataset,
                                 Scenario1Strategy strat) {
    OrderOrdering orderOrdering;
    VanOrdering vanOrdering;

    switch (strat) {
    case Scenario1Strategy::VOLUME_ASC:
        orderOrdering = Order::compareByVolumeAsc;
        vanOrdering = Van::compareByVolume;
        break;
    case Scenario1Strategy::VOLUME_DESC:
        orderOrdering = Order::compareByVolumeDesc;
        vanOrdering = Van::compareByVolume;
        break;
    case Scenario1Strategy::WEIGHT_ASC:
        orderOrdering = Order::compareByWeightAsc;
        vanOrdering = Van::compareByWeight;
        break;
    case Scenario1Strategy::WEIGHT_DESC:
        orderOrdering = Order::compareByWeightDesc;
        vanOrdering = Van::compareByWeight;
        break;
    case Scenario1Strategy::AREA_ASC:
        orderOrdering = Order::compareByAreaAsc;
        vanOrdering = Van::compareByArea;
        break;
    case Scenario1Strategy::AREA_DESC:
        orderOrdering = Order::compareByAreaDesc;
        vanOrdering = Van::compareByArea;
        break;
    }

    return _firstFitBinPacking(dataset.getOrders(), dataset.getVans(),
                               vanOrdering, orderOrdering);
}

const SimulationResult scenario2(const Dataset &dataset,
                                 Scenario2Strategy strat) {
    OrderOrdering orderOrdering;
    VanOrdering vanOrdering;

    switch (strat) {
    case Scenario2Strategy::VOLUME_ASC:
        orderOrdering = Order::compareByVolumeAsc;
        vanOrdering = Van::compareByVolumeOverCost;
        break;
    case Scenario2Strategy::VOLUME_DESC:
        orderOrdering = Order::compareByVolumeDesc;
        vanOrdering = Van::compareByVolumeOverCost;
        break;
    case Scenario2Strategy::WEIGHT_ASC:
        orderOrdering = Order::compareByWeightAsc;
        vanOrdering = Van::compareByWeightOverCost;
        break;
    case Scenario2Strategy::WEIGHT_DESC:
        orderOrdering = Order::compareByWeightDesc;
        vanOrdering = Van::compareByWeightOverCost;
        break;
    case Scenario2Strategy::AREA_ASC:
        orderOrdering = Order::compareByAreaAsc;
        vanOrdering = Van::compareByAreaOverCost;
        break;
    case Scenario2Strategy::AREA_DESC:
        orderOrdering = Order::compareByAreaDesc;
        vanOrdering = Van::compareByAreaOverCost;
        break;
    }

    return _firstFitBinPacking(dataset.getOrders(), dataset.getVans(),
                               vanOrdering, orderOrdering);
}

const SimulationResult scenario3(const Dataset &dataset) {
    auto tstart = std::chrono::high_resolution_clock::now();

    std::vector<Order> orders = dataset.getOrders();
    std::sort(orders.begin(), orders.end(), Order::compareByDuration);
    Van van{std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
            0};

    double time = 0, max_time = 8 * 3600;

    auto i = orders.begin(), end = orders.end();
    for (; i != end && time + i->getDuration() <= max_time; ++i) {
        van.addOrder(*i);
        time += i->getDuration();
    }

    auto tend = std::chrono::high_resolution_clock::now();

    return {
        {i, end},
        {van},
        std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart),
    };
}
