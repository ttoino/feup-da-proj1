#ifndef DA_PROJ1_SCENARIOS_HPP
#define DA_PROJ1_SCENARIOS_HPP

#include <functional>
#include <utility>
#include <vector>

#include "dataset.hpp"
#include "order.hpp"
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

    SimulationResult(const std::vector<Order> &rorders,
                     const std::vector<Van> &vans);
};

using VanOrdering = std::function<bool(const Van &, const Van &)>;
using OrderOrdering = std::function<bool(const Order &, const Order &)>;

enum class Scenario1Strategy {
    VOLUME_ASC,
    VOLUME_DESC,
    WEIGHT_ASC,
    WEIGHT_DESC,
    AREA_ASC,
    AREA_DESC,
};

const SimulationResult scenario1(const Dataset &dataset,
                                 Scenario1Strategy strat);

enum class Scenario2Strategy {
    DIVIDE,
    MULTIPLY,
};

const SimulationResult scenario2(const Dataset &dataset,
                                 Scenario2Strategy strat);

const SimulationResult scenario3(const Dataset &dataset);

#endif
