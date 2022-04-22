#include <cmath>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../includes/constants.hpp"
#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/scenarios.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"
#include "../includes/van.hpp"

template <class T>
std::optional<T> UserInterface::optionsMenu(const Options<T> &options) {
    for (int i{1}; i < options.size(); ++i) {
        std::cout << "(" << i << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.front().first << "\n\n";

    unsigned option = getUnsignedInput("Please insert option: ");

    if (option < options.size())
        return options.at(option).second;

    errorMessage = "Invalid option!\n";
    return {};
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

void UserInterface::show(Dataset &dataset) {
    std::cout << CLEAR_SCREEN << PROGRAM_NAME << '\n' << std::endl;

    switch (currentMenu) {
    case Menu::MAIN:
        mainMenu();
        break;
    case Menu::SHOW_ORDERS:
        showOrdersMenu(dataset);
        break;
    case Menu::SHOW_VANS:
        showVansMenu(dataset);
        break;
    case Menu::CHOOSE_SCENARIO:
        chooseScenarioMenu();
        break;
    case Menu::CHOOSE_DATASET:
        chooseDatasetMenu(dataset);
        break;
    case Menu::GENERATE_DATASET:
        generateDatasetMenu(dataset);
        break;

    case Menu::SCENARIO_ONE:
        scenarioOneMenu(dataset);
        break;
    case Menu::SCENARIO_TWO:
        scenarioTwoMenu(dataset);
        break;
    case Menu::SCENARIO_THREE:
        scenarioThreeMenu(dataset);
        break;
    case Menu::ALL_SCENARIOS:
        allScenariosMenu();
        break;

    case Menu::RESULTS:
        resultsMenu();
        break;
    case Menu::RESULTS_VANS:
        resultsVansMenu();
        break;

    case Menu::EXIT:
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
    auto menu = optionsMenu<Menu>({
        {"Exit", Menu::EXIT},
        {"Orders", Menu::SHOW_ORDERS},
        {"Vans", Menu::SHOW_VANS},
        {"Choose dataset", Menu::CHOOSE_DATASET},
        {"Choose scenario", Menu::CHOOSE_SCENARIO},
        {"Generate dataset", Menu::GENERATE_DATASET},
    });
    currentMenu = menu.value_or(currentMenu);
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
    auto option =
        getStringInput("\nPress enter for next page, or 'q' to exit ");

    if ((option == "q" || option == "Q") || (++page == pages)) {
        currentMenu = Menu::MAIN;
        page = 0;
    }
}

void UserInterface::showOrdersMenu(Dataset &dataset) {
    std::cout << "ID\tVolume\tWeight\tReward\tDuration\n";
    paginatedMenu(dataset.getOrders());
}

void UserInterface::showVansMenu(Dataset &dataset) {
    std::cout << "ID\tVolume\tWeight\tCost\n" << std::left;
    paginatedMenu(dataset.getVans());
}

void UserInterface::chooseScenarioMenu() {
    auto menu = optionsMenu<Menu>({
        {"Go back", Menu::MAIN},
        {"Scenario 1 - Minimize used vans", Menu::SCENARIO_ONE},
        {"Scenario 2 - Maximize profit", Menu::SCENARIO_TWO},
        {"Scenario 3 - Maximize express deliveries", Menu::SCENARIO_THREE},
        {"Run all scenarios (with every dataset)", Menu::ALL_SCENARIOS},
    });
    currentMenu = menu.value_or(currentMenu);
}

void UserInterface::chooseDatasetMenu(Dataset &dataset) {
    Options<std::string> options{{"Go back", ""}};

    auto datasets = Dataset::getAvailableDatasets();
    std::transform(
        datasets.begin(), datasets.end(), std::back_inserter(options),
        [](const std::string &n) -> Options<std::string>::value_type {
            return {n, n};
        });

    const auto selection = optionsMenu(options);

    if (!selection.has_value())
        return;

    currentMenu = Menu::MAIN;

    if (selection == "")
        return;

    dataset = Dataset::load(selection.value());
}

void UserInterface::generateDatasetMenu(Dataset &dataset) {
    DatasetGenerationParams params;
    std::string name;
    while (true) {
        name = getStringInput("Dataset name: ");

        if (name == "")
            errorMessage = "Empty name not allowed!\n";
        else if (name.find('/') != std::string::npos)
            errorMessage = "Slashes are not allowed!\n";
        else
            break;
    }

    params.numberOfOrders =
        getUnsignedInput("Number of orders to generate: ", 1);
    params.minOrderVolume = getUnsignedInput("Minimum volume for orders: ", 1);
    params.maxOrderVolume =
        getUnsignedInput("Maximum volume for orders: ", params.minOrderVolume);
    params.minOrderWeight = getUnsignedInput("Minimum weight for orders: ", 1);
    params.maxOrderWeight =
        getUnsignedInput("Maximum weight for orders: ", params.minOrderWeight);
    params.minOrderReward = getUnsignedInput("Minimum reward for orders: ", 1);
    params.maxOrderReward =
        getUnsignedInput("Maximum reward for orders: ", params.minOrderReward);
    params.minOrderDuration =
        getUnsignedInput("Minimum duration for orders: ", 1);
    params.maxOrderDuration = getUnsignedInput("Maximum duration for orders: ",
                                               params.minOrderDuration);

    params.numberOfVans = getUnsignedInput("Number of vans to generate: ", 1);
    params.minVanVolume = getUnsignedInput("Minimum volume for vans: ", 1);
    params.maxVanVolume =
        getUnsignedInput("Maximum volume for vans: ", params.minVanVolume);
    params.minVanWeight = getUnsignedInput("Minimum weight for vans: ", 1);
    params.maxVanWeight =
        getUnsignedInput("Maximum weight for vans: ", params.minVanWeight);
    params.minVanCost = getUnsignedInput("Minimum cost for vans: ", 1);
    params.maxVanCost =
        getUnsignedInput("Maximum cost for vans: ", params.minVanCost);

    currentMenu = Menu::MAIN;
    dataset = Dataset::generate(name, params);
}

void UserInterface::scenarioOneMenu(Dataset &dataset) {
    auto selection = optionsMenu<std::optional<Scenario1Strategy>>({
        {"Go back", {}},
        {"Optimize using volume - ascending", Scenario1Strategy::VOLUME_ASC},
        {"Optimize using volume - descending", Scenario1Strategy::VOLUME_DESC},
        {"Optimize using weight - ascending", Scenario1Strategy::WEIGHT_ASC},
        {"Optimize using weight - descending", Scenario1Strategy::WEIGHT_DESC},
        {"Optimize using area   - ascending", Scenario1Strategy::AREA_ASC},
        {"Optimize using area   - descending", Scenario1Strategy::AREA_DESC},
    });

    if (!selection.has_value()) // Error while getting option
        return;

    if (!selection.value().has_value()) { // User wants to go back
        currentMenu = Menu::CHOOSE_SCENARIO;
        return;
    }

    result = scenario1(dataset, selection.value().value());
    currentMenu = Menu::RESULTS;
}

void UserInterface::scenarioTwoMenu(Dataset &dataset) {
    auto selection = optionsMenu<std::optional<Scenario2Strategy>>({
        {"Go back", {}},
        {"Optimize using volume - ascending", Scenario2Strategy::VOLUME_ASC},
        {"Optimize using volume - descending", Scenario2Strategy::VOLUME_DESC},
        {"Optimize using weight - ascending", Scenario2Strategy::WEIGHT_ASC},
        {"Optimize using weight - descending", Scenario2Strategy::WEIGHT_DESC},
        {"Optimize using area   - ascending", Scenario2Strategy::AREA_ASC},
        {"Optimize using area   - descending", Scenario2Strategy::AREA_DESC},
    });

    if (!selection.has_value()) // Error while getting option
        return;

    if (!selection.value().has_value()) { // User wants to go back
        currentMenu = Menu::CHOOSE_SCENARIO;
        return;
    }

    result = scenario2(dataset, selection.value().value());
    currentMenu = Menu::RESULTS;
}

void UserInterface::scenarioThreeMenu(Dataset &dataset) {
    result = scenario3(dataset);
    currentMenu = Menu::RESULTS;
}

void UserInterface::allScenariosMenu() {
    runAllScenarios();

    getStringInput("Press enter to continue ");
    currentMenu = Menu::MAIN;
}

void UserInterface::resultsMenu() {
    std::cout << "Used " << result.vans.size() << " vans\n"
              << "Dispatched " << result.ordersDispatched << " orders, "
              << result.remainingOrders.size() << " remain\n"
              << "Delivery efficiency: " << (result.efficiency * 100) << "%\n"
              << "Average delivery time: "
              << ((double)result.deliveryTime / result.ordersDispatched)
              << "s\n"
              << "Spent " << result.cost << "€ on vans\n"
              << "Received " << result.reward << "€ from orders\n"
              << "Total profit: " << result.profit << "€\n"
              << "Took " << result.runtime.count() << "µs\n\n";

    auto menu = optionsMenu<Menu>({
        {"Continue", Menu::MAIN},
        {"See vans", Menu::RESULTS_VANS},
    });
    currentMenu = menu.value_or(currentMenu);
}

void UserInterface::resultsVansMenu() {
    std::cout << "ID\tVolume\tWeight\tCost\tOrders\n" << std::left;
    paginatedMenu(result.vans);
}
