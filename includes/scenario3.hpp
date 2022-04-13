#ifndef DA_PROJ1_SCENARIO3_HPP
#define DA_PROJ1_SCENARIO3_HPP

#include "simulation.hpp"
#include "dataset.hpp"
#include <algorithm>

class Simulation3 : public Simulation {
public:
    enum SimulationOptions { WEIGHT, VOLUME };

private:
    SimulationOptions option;

public:
    Simulation3() {};

    SimulationResult run();
};


#endif //DA_PROJ1_SCENARIO3_HPP
