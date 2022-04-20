#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../includes/constants.hpp"
#include "../includes/scenario1.hpp"
#include "../includes/scenario2.hpp"
#include "../includes/scenario3.hpp"
#include "../includes/simulation.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

void UserInterface::optionsMenu(const options_t &options) {
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
        throw Exit();

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

void UserInterface::show(std::map<std::string, Dataset> &datasets) {
    std::cout << CLEAR_SCREEN << PROGRAM_NAME << '\n' << std::endl;

    switch (currentMenu) {
    case MAIN:
        mainMenu();
        break;
    case SHOW_ORDERS:
        showOrdersMenu(datasets);
        break;
    case SHOW_VANS:
        showVansMenu(datasets);
        break;
    case CHOOSE_SCENARIO:
        chooseScenarioMenu();
        break;
    case CHOOSE_DATASET:
        chooseDatasetMenu(datasets);
        break;

    case SCENARIO_ONE:
        scenarioOneMenu();
        break;
    case SCENARIO_ONE_VOLUME: {
        Simulation1 sim(Simulation1::VOLUME);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }
    case SCENARIO_ONE_WEIGHT: {
        Simulation1 sim(Simulation1::WEIGHT);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }
    case SCENARIO_ONE_AREA: {
        Simulation1 sim(Simulation1::AREA);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }

    case SCENARIO_TWO: {
        scenarioTwoMenu();
        break;
    }

    case SCENARIO_TWO_MULTIPLY: {
        Simulation2 sim(Simulation2::MULTIPLY);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }

    case SCENARIO_TWO_DIVIDE: {
        Simulation2 sim(Simulation2::DIVIDE);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }

    case SCENARIO_THREE:
        scenarioThreeMenu();
        break;
    case SCENARIO_THREE_VOLUME: {
        Simulation3 sim(Simulation3::VOLUME);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }
    case SCENARIO_THREE_WEIGHT: {
        Simulation3 sim(Simulation3::WEIGHT);
        result = sim.run(datasets.at(dataset));
        currentMenu = RESULTS;
        break;
    }

    case RESULTS:
        resultsMenu(datasets);
        break;
    case RESULTS_VANS:
        resultsVansMenu();
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
        {"Choose dataset", CHOOSE_DATASET},
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
    auto option = getStringInput(
        "\nPress enter for next page, or 'q' to exit paginated view");

    if ((option.size() == 1 && tolower(option.at(0)) == 'q') ||
        (++page == pages)) {
        currentMenu = MAIN;
        page = 0;
    }
}

void UserInterface::showOrdersMenu(std::map<std::string, Dataset> &datasets) {
    std::cout << "Volume\tWeight\tReward\tDuration\n";
    paginatedMenu(datasets.at(dataset).getOrders());
}

void UserInterface::showVansMenu(std::map<std::string, Dataset> &datasets) {
    std::cout << "Volume\tWeight\tCost\n" << std::left;
    paginatedMenu(datasets.at(dataset).getVans());
}

void UserInterface::chooseScenarioMenu() {
    optionsMenu({
        {"Go back", MAIN},
        {"Scenario 1 - Minimize used vans", SCENARIO_ONE},
        {"Scenario 2 - Maximize profit", SCENARIO_TWO},
        {"Scenario 3 - Maximize express deliveries", SCENARIO_THREE},
    });
}

void UserInterface::chooseDatasetMenu(
    std::map<std::string, Dataset> &datasets) {
    std::cout << "Choose dataset:\n\n";

    int i = 1;
    for (const auto &p : datasets) {
        std::cout << "  - " << p.first << " (" << p.second.getVans().size()
                  << " vans and " << p.second.getOrders().size()
                  << " orders)\n";
    }

    const std::string option =
        getStringInput("\nPlease insert option (enter to go back): ");

    if (option == "") {
        currentMenu = MAIN;
        return;
    }

    if (datasets.contains(option)) {
        dataset = option;
        currentMenu = MAIN;
    } else
        errorMessage = "Invalid option!\n";
}

void UserInterface::scenarioOneMenu() {
    optionsMenu({
        {"Go back", CHOOSE_SCENARIO},
        {"Optimize using volume", SCENARIO_ONE_VOLUME},
        {"Optimize using weight", SCENARIO_ONE_WEIGHT},
        {"Optimize using area", SCENARIO_ONE_AREA},
    });
}

void UserInterface::scenarioTwoMenu() {
    optionsMenu({
        {"Go back", CHOOSE_SCENARIO},
        {"Optimize using division", SCENARIO_TWO_DIVIDE},
        {"Optimize using multiplication", SCENARIO_TWO_MULTIPLY},
    });
}

void UserInterface::scenarioThreeMenu() {
    optionsMenu({
        {"Go back", CHOOSE_SCENARIO},
        {"Optimize using volume", SCENARIO_THREE_VOLUME},
        {"Optimize using weight", SCENARIO_THREE_WEIGHT},
    });
}

void UserInterface::resultsMenu(std::map<std::string, Dataset> &datasets) {
    std::cout << result.remainingOrders.size() << " remaining orders\n"
              << "Used " << result.vansUsed << " vans\n"
              << "Dispatched " << result.ordersDispatched << " orders\n"
              << result.ordersForTheDay << " orders for the day\n"
              << result.vansForTheDay << " vans for the day\n"
              << "Delivery efficiency: " << std::setprecision(3)
              << ((result.ordersDispatched && result.ordersForTheDay)
                      ? (result.ordersDispatched * 100 / result.ordersForTheDay)
                      : 0)
              << "%\n"
              << "Average delivery time : " << std::setprecision(3)
              << ((result.deliveryTime && result.ordersDispatched)
                      ? (result.deliveryTime / result.ordersDispatched)
                      : -1)
              << "\n"
              << "Profit : "
              << ((result.cost && result.reward) ? (result.reward - result.cost)
                                                 : -1)
              << "\n\n";

    if (result.vans.size())
        for (auto &van : result.vans)
            van.printStatistics(std::cout);

    getStringInput("Press enter to continue ");
    currentMenu = MAIN;
    // optionsMenu({
    //     {"Continue", MAIN},
    //     {"See vans", RESULTS_VANS},
    // });
}

void UserInterface::resultsVansMenu() {
    std::cout << "Volume\tWeight\tCost\n" << std::left;
    paginatedMenu(result.vans);
}
