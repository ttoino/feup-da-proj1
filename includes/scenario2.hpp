#ifndef DA_PROJ1_SCENARIO2_HPP
#define DA_PROJ1_SCENARIO2_HPP

#include "simulation.hpp"
#include "dataset.hpp"
#include <iostream>

class Simulation2 : public Simulation {
public:
    enum SimulationOptions { DIVIDE, MULTIPLY };

private:
    SimulationOptions option;

public:
    Simulation2(SimulationOptions option) : option(option) {};

    /**
     * @brief the number of vans is minimized and the number of orders delivered
     * is maximized
     *
     * @param option how to sort the vans and orders
     *
     * @details option must be "volume" or "weight"
     *
     * @note the vans are sorted by <option> in descending order
     * @note the orders are sorted by <option> in ascending order
     */
    SimulationResult run();

    SimulationResult run2DVSBPP();
};


#endif //DA_PROJ1_SCENARIO2_HPP
