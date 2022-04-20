#ifndef DA_PROJ1_SCENARIO3_HPP
#define DA_PROJ1_SCENARIO3_HPP

#include "dataset.hpp"
#include "simulation.hpp"

#include <algorithm>
#include <iostream>

class Simulation3 : public Simulation {
public:
    enum SimulationOptions { WEIGHT, VOLUME };

private:
    SimulationOptions option;

public:
    Simulation3(SimulationOptions option) : option(option){};

    SimulationResult run(const Dataset &dataset);
};

#endif // DA_PROJ1_SCENARIO3_HPP
