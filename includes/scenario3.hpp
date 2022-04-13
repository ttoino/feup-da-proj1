#ifndef DA_PROJ1_SCENARIO3_HPP
#define DA_PROJ1_SCENARIO3_HPP

#include "simulation.hpp"
#include "dataset.hpp"

#include <iostream>
#include <algorithm>

class Simulation3 : public Simulation {
public:
    enum SimulationOptions { WEIGHT, VOLUME };

private:
    SimulationOptions option;

public:
    Simulation3(SimulationOptions option) : option(option) {};

    SimulationResult run();
};


#endif //DA_PROJ1_SCENARIO3_HPP
