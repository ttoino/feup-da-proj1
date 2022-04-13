#ifndef DA_PROJ1_SIMULATION_HPP
#define DA_PROJ1_SIMULATION_HPP

#include <vector>

#include "order.hpp"
#include "van.hpp"

/**
 * @brief Struct packing the results of a given simulation
 * 
 */
struct SimulationResult {
    std::vector<Order> remainingOrders;
    std::vector<Van> vans;
    int vansUsed = 0;
    int ordersDispatched = 0;
    int ordersForTheDay;
    int vansForTheDay;
    double deliveryTime;
};

/**
 * @brief Represents a simulation to be performed by the application
 * 
 */
class Simulation {

public:

    /**
     * @brief Runs this specified simulation and returns the simulation's results.
     * 
     * @return the simulation's results
     */
    virtual SimulationResult run() = 0;
};

#endif