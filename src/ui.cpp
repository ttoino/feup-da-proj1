#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../includes/constants.hpp"
#include "../includes/scenario1.hpp"
#include "../includes/simulation.hpp"
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
        scenarioOneMenu();
        break;
    case SCENARIO_ONE_VOLUME: {
        Simulation1 sim(Simulation1::VOLUME);
        result = sim.run();
        currentMenu = RESULTS;
        break;
    }
    case SCENARIO_ONE_WEIGHT: {
        Simulation1 sim(Simulation1::WEIGHT);
        result = sim.run();
        currentMenu = RESULTS;
        break;
    }

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

template <class T>
void UserInterface::paginatedMenu(const std::vector<T> &items) {
    static unsigned int page{0};

    unsigned int pages = ceil((float)items.size() / ITEMS_PER_PAGE);

    for (auto i{items.begin() + page * ITEMS_PER_PAGE},
         end{page == pages - 1 ? items.end()
                               : items.begin() + (page + 1) * ITEMS_PER_PAGE};
         i < end; ++i)
        std::cout << *i << std::endl;

    std::cout << "\nPage " << page + 1 << " of " << pages;
    getStringInput("\nPress enter for next page ");

    if (++page == pages) {
        currentMenu = MAIN;
        page = 0;
    }
}

void UserInterface::showOrdersMenu(Dataset &dataset) {
    std::cout << "Volume\tWeight\tReward\tDuration\n";
    paginatedMenu(dataset.getOrders());
}

void UserInterface::showVansMenu(Dataset &dataset) {
    std::cout << "Volume\tWeight\tCost\n" << std::left;
    paginatedMenu(dataset.getVans());
}

void UserInterface::chooseScenarioMenu() {
    optionsMenu({
        {"Go back", MAIN},
        {"Scenario 1 - Minimize used vans", SCENARIO_ONE},
        {"Scenario 2 - Maximize profit", SCENARIO_TWO},
        {"Scenario 3 - Maximize express deliveries", SCENARIO_THREE},
    });
}

void UserInterface::scenarioOneMenu() {
    optionsMenu({
        {"Go back", CHOOSE_SCENARIO},
        {"Optimize using volume", SCENARIO_ONE_VOLUME},
        {"Optimize using weight", SCENARIO_ONE_WEIGHT},
    });
}

void UserInterface::resultsMenu(Dataset &dataset) {
    std::cout << result.remainingOrders.size() << " remaining orders\n"
              << result.vans.size() << " vans\nUsed " << result.vansUsed
              << " vans\nDispatched " << result.ordersDispatched << " orders\n"
              << result.ordersForTheDay << " orders for the day\n"
              << result.vansForTheDay << " vans for the day\n\n";

    getStringInput("Press enter to continue ");
    currentMenu = MAIN;
}
