#include <iostream>

#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

int main() {
    UserInterface ui{};

    try {
        while (true)
            ui.show();
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}