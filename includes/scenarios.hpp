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
 * @brief Represents the results of a scenario.
 */
struct ScenarioResult {
    /** @brief The orders that were not delivered. */
    std::vector<Order> remainingOrders{};
    /** @brief The vans that were used. */
    std::vector<Van> vans{};
    /** @brief How many orders that were delivered. */
    int ordersDispatched{0};
    /** @brief How much time the orders took to be delivered. */
    double deliveryTime{0};
    /**
     * @brief How efficient the delivery was.
     *
     * @details The ratio between the amount orders that were delivered and the
     *          total amount of orders. A number between 0 and 1.
     */
    double efficiency{0};
    /** @brief How much the vans cost to operate. */
    int cost{0};
    /** @brief How much reward was gotten from the deliveries. */
    int reward{0};
    /** @brief Total profit (#reward - #cost). */
    int profit{0};
    /** @brief How much time the algorithm took to run. */
    std::chrono::microseconds runtime{0};

    /**
     * @brief Creates a scenario result from the given params.
     *
     * @param remainingOrders The orders that were not delivered.
     * @param vans The vans that were used.
     * @param runtime How much time the algorithm took to run.
     */
    ScenarioResult(const std::vector<Order> &remainingOrders,
                   const std::vector<Van> &vans,
                   const std::chrono::microseconds &runtime);

    /**
     * @brief Converts this object to a csv representation.
     *
     * @return A csv representation of this object.
     */
    std::string toCSV() const;
};

/**
 * @brief Function to be used in std::sort() to sort orders.
 */
using OrderOrdering = std::function<bool(const Order &, const Order &)>;
/**
 * @brief Function to be used in std::sort() to sort vans.
 */
using VanOrdering = std::function<bool(const Van &, const Van &)>;

/**
 * @brief Holds the possible strategies for scenario1().
 */
ENUM(
    Scenario1Strategy,
    /**
       @brief Sort orders by ascending Order#volume and vans by descending
              Van#maxVolume.
     */
    VOLUME_ASC,
    /**
       @brief Sort orders by descending Order#volume and vans by descending
              Van#maxVolume.
     */
    VOLUME_DESC,
    /**
       @brief Sort orders by ascending Order#weight and vans by descending
              Van#maxWeight.
     */
    WEIGHT_ASC,
    /**
       @brief Sort orders by ascending Order#weight and vans by descending
              Van#maxWeight.
     */
    WEIGHT_DESC,
    /**
       @brief Sort orders by ascending "area" (Order#volume × Order#weight) and
              vans by descending "max area" (Van#maxVolume × Van#maxWeight).
     */
    AREA_ASC,
    /**
       @brief Sort orders by descending "area" (Order#volume × Order#weight)
              and vans by descending "max area" (Van#maxVolume × Van#maxWeight).
     */
    AREA_DESC);

/**
 * @brief Tries to maximize the amount of orders delivered and to minimize the
 *        amount of vans used.
 *
 * Uses an implementation of First Fit Decreasing Bin-Packing.
 *
 * Overall performance is
 * \f$ T(o, v) = \mathcal{O}(o \log o + v \log v + o \cdot v) \f$ and
 * \f$ S(o, v) = \mathcal{O}(o + v) \f$,
 * where \f$o\f$ is the number of orders and \f$v\f$ the number of vans.
 *
 * @param dataset The dataset to use.
 * @param strat What strategy to implement.
 *
 * @return The result of the algorithm.
 */
const ScenarioResult scenario1(const Dataset &dataset, Scenario1Strategy strat);

/**
 * @brief Holds the possible strategies for scenario2().
 */
ENUM(Scenario2Strategy,
     /**
       @brief Sort orders by ascending Order#volume and vans by descending
              Van#maxVolume divided by Van#cost.
     */
     VOLUME_ASC,
     /**
        @brief Sort orders by descending Order#volume and vans by descending
               Van#maxVolume divided by Van#cost.
      */
     VOLUME_DESC,
     /**
        @brief Sort orders by ascending Order#weight and vans by descending
               Van#maxWeight divided by Van#cost.
      */
     WEIGHT_ASC,
     /**
        @brief Sort orders by ascending Order#weight and vans by descending
               Van#maxWeight divided by Van#cost.
      */
     WEIGHT_DESC,
     /**
        @brief Sort orders by ascending "area" (Order#volume × Order#weight) and
               vans by descending "max area" (Van#maxVolume × Van#maxWeight)
               divided by Van#cost.
      */
     AREA_ASC,
     /**
        @brief Sort orders by descending "area" (Order#volume × Order#weight)
               and vans by descending "max area" (Van#maxVolume × Van#maxWeight)
               divided by Van#cost.
      */
     AREA_DESC);

/**
 * @brief Tries to maximize the amount of orders delivered and the overall
 *        profit.
 *
 * Uses an implementation of First Fit Decreasing Bin-Packing.
 *
 * Overall performance is
 * \f$ T(o, v) = \mathcal{O}(o \log o + v \log v + o \cdot v) \f$ and
 * \f$ S(o, v) = \mathcal{O}(o + v) \f$,
 * where \f$o\f$ is the number of orders and \f$v\f$ the number of vans.
 *
 * @param dataset The dataset to use.
 * @param strat What strategy to implement.
 *
 * @return The result of the algorithm.
 */
const ScenarioResult scenario2(const Dataset &dataset, Scenario2Strategy strat);

/**
 * @brief Tries to maximize the amount of orders delivered by a single van in a
 *        work day and to minimize the average delivery time.
 *
 * Uses a greedy algorithm that selects the quickest orders first.
 *
 * Overall performance is
 * \f$ T(o) = \mathcal{O}(o \log o) \f$ and
 * \f$ S(o) = \mathcal{O}(o) \f$,
 * where \f$o\f$ is the number of orders.
 *
 * @param dataset The dataset to use.
 *
 * @return The result of the algorithm.
 */
const ScenarioResult scenario3(const Dataset &dataset);

/**
 * @brief Runs every scenario for every dataset with all possible strategies and
 *        outputs the results to ::OUTPUT_FILE.
 */
void runAllScenarios();

#endif
