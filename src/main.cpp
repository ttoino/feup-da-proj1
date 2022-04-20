#include <filesystem>
#include <iostream>
#include <map>

#include "../includes/constants.hpp"
#include "../includes/dataset.hpp"
#include "../includes/ui.hpp"
#include "../includes/utils.hpp"

int main() {
    UserInterface ui{};

    std::map<std::string, Dataset> datasets{};

    for (auto &p : std::filesystem::directory_iterator(DATASETS_PATH))
        if (p.is_directory())
            datasets[p.path().filename()] = Dataset::load(p.path());

    try {
        while (true)
            ui.show(datasets);
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}
