#ifndef DA_PROJ1_SCENARIOS_HPP
#define DA_PROJ1_SCENARIOS_HPP

#include <chrono>
#include <functional>
#include <utility>
#include <vector>

#include "dataset.hpp"
#include "order.hpp"
#include "utils.hpp"
#include "van.hpp"

/**
 * @brief Struct packing the results of a given simulation
 *
 */
struct SimulationResult {
    std::vector<Order> remainingOrders{};
    std::vector<Van> vans{};
    int ordersDispatched{0};
    double deliveryTime{0};
    double efficiency{0};
    int cost{0};
    int reward{0};
    int profit{0};
    std::chrono::microseconds runtime{0};

    SimulationResult(const std::vector<Order> &rorders,
                     const std::vector<Van> &vans,
                     const std::chrono::microseconds &runtime);

    std::string toCSV();
};

using VanOrdering = std::function<bool(const Van &, const Van &)>;
using OrderOrdering = std::function<bool(const Order &, const Order &)>;

ENUM(Scenario1Strategy, VOLUME_ASC, VOLUME_DESC, WEIGHT_ASC, WEIGHT_DESC,
     AREA_ASC, AREA_DESC);

const SimulationResult scenario1(const Dataset &dataset,
                                 Scenario1Strategy strat);

ENUM(Scenario2Strategy, VOLUME_ASC, VOLUME_DESC, WEIGHT_ASC, WEIGHT_DESC,
     AREA_ASC, AREA_DESC);

const SimulationResult scenario2(const Dataset &dataset,
                                 Scenario2Strategy strat);

const SimulationResult scenario3(const Dataset &dataset);

void runAllScenarios();

#endif
