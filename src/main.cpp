#include <filesystem>
#include <iostream>
#include <set>

#include "../includes/constants.hpp"
#include "../includes/dataset.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

int main() {
    UserInterface ui{};

    Dataset dataset = Dataset::load("default");

    try {
        while (true)
            ui.show(dataset);
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}
