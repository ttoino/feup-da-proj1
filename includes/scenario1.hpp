#ifndef DA_PROJ1_SCENARIO1_HPP
#define DA_PROJ1_SCENARIO1_HPP

#include <iostream>
#include <string>

#include "dataset.hpp"
#include "simulation.hpp"
#include "van.hpp"
#include "order.hpp"

class Simulation1 : public Simulation {
public:

    enum SimulationOptions {
        WEIGHT,
        VOLUME
    };

private:
    
    SimulationOptions option;

public:

    Simulation1(SimulationOptions option);
    
    /**
     * @brief the number of vans is minimized and the number of orders delivered is maximized
     *
     * @param option how to sort the vans and orders
     *
     * @details option must be "volume" or "weight"
     *
     * @note the vans are sorted by <option> in descending order
     * @note the orders are sorted by <option> in ascending order
     */
    SimulationResult run();
};

#endif //DA_PROJ1_SCENARIO1_HPP
