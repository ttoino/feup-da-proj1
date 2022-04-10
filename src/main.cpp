#include <iostream>

#include "../includes/van.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

int main() {
    UserInterface ui{};

    auto vans = Van::processDataset();

    for (const auto& van : vans)
        std::cout << van << std::endl;

    try {
        while (true)
            ui.show();
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}