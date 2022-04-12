#include <iostream>
#include <string>
#include <vector>

#include "../includes/constants.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

void UserInterface::optionsMenu(
    const std::vector<std::pair<const std::string, Menu>> &options) {
    for (int i{1}; i < options.size(); ++i) {
        std::cout << "(" << i << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.front().first << "\n\n";

    unsigned option = getUnsignedInput("Please insert option: ");

    if (option < options.size())
        currentMenu = options.at(option).second;
    else
        errorMessage = "Invalid option!\n";
}

unsigned long UserInterface::getUnsignedInput(const std::string &prompt,
                                              unsigned long min,
                                              unsigned long max) {
    std::string input;
    unsigned long number;
    bool done = false;

    do {
        input = getStringInput(prompt);

        try {
            number = stoul(input);
            done = true;
        } catch (std::invalid_argument) {
            errorMessage = "Invalid input!\n";
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

double UserInterface::getDoubleInput(const std::string &prompt, double min,
                                     double max) {
    std::string input;
    double number;
    bool done = false;

    do {
        input = getStringInput(prompt);

        try {
            number = stod(input);
            done = true;
        } catch (std::invalid_argument) {
            errorMessage = "Invalid input!\n";
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

std::string UserInterface::getStringInput(const std::string &prompt) {
    std::cout << RED_TEXT << errorMessage << RESET_FORMATTING << prompt;
    errorMessage = "";

    std::string input{};

    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        exit();

    return input;
}

bool UserInterface::inRange(unsigned long n, unsigned long min,
                            unsigned long max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        errorMessage = "Value outside allowed range!\n";

    return b;
}

bool UserInterface::inRange(double n, double min, double max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        errorMessage = "Value outside allowed range!\n";

    return b;
}

void UserInterface::show(Dataset &dataset) {
    std::cout << CLEAR_SCREEN << PROGRAM_NAME << '\n' << std::endl;

    switch (currentMenu) {
    case MAIN:
        mainMenu();
        break;
    case SHOW_ORDERS:
        showOrdersMenu(dataset);
        break;
    case SHOW_VANS:
        showVansMenu(dataset);
        break;
    case CHOOSE_SCENARIO:
        chooseScenarioMenu();
        break;

    case SCENARIO_ONE:
        // TODO: Process data and get results for scenario 1
        currentMenu = RESULTS;
        break;
    case SCENARIO_TWO:
        // TODO: Process data and get results for scenario 2
        currentMenu = RESULTS;
        break;
    case SCENARIO_THREE:
        // TODO: Process data and get results for scenario 3
        currentMenu = RESULTS;
        break;

    case RESULTS:
        resultsMenu(dataset);
        break;
    case EXIT:
    default:
        throw Exit();
        break;
    }
}

void UserInterface::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::cout << "Shutting down..." << std::endl;
}

void UserInterface::mainMenu() {
    optionsMenu({
        {"Exit", EXIT},
        {"Orders", SHOW_ORDERS},
        {"Vans", SHOW_VANS},
        {"Choose scenario", CHOOSE_SCENARIO},
    });
}

void UserInterface::showOrdersMenu(Dataset &dataset) {
    for (const auto &order : dataset.getOrders())
        std::cout << order << std::endl;

    getStringInput("Press enter to continue ");
    currentMenu = MAIN;
}

void UserInterface::showVansMenu(Dataset &dataset) {
    for (const auto &van : dataset.getVans())
        std::cout << van << std::endl;

    getStringInput("Press enter to continue ");
    currentMenu = MAIN;
}

void UserInterface::chooseScenarioMenu() {
    optionsMenu({
        {"Go back", MAIN},
        {"Scenario 1 - Minimize used vans", SCENARIO_ONE},
        {"Scenario 2 - Maximize profit", SCENARIO_TWO},
        {"Scenario 3 - Maximize express deliveries", SCENARIO_THREE},
    });
}

void UserInterface::resultsMenu(Dataset &dataset) {
    getStringInput("Press enter to continue ");
    currentMenu = MAIN;
}
