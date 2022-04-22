#include <algorithm>
#include <filesystem>

#include "../includes/constants.hpp"
#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/van.hpp"

Dataset::Dataset(const std::vector<Order> &orders, const std::vector<Van> &vans)
    : orders(orders), vans(vans) {}

const std::vector<Van> &Dataset::getVans() const { return vans; }
const std::vector<Order> &Dataset::getOrders() const { return orders; }

Dataset Dataset::load(const std::string &path) {
    return {Order::processDataset(path), Van::processDataset(path)};
}

Dataset Dataset::generate(const std::string &name,
                          const DatasetGenerationParams &params) {
    std::filesystem::create_directory({DATASETS_PATH + name});

    return {
        Order::generateDataset(name, params),
        Van::generateDataset(name, params),
    };
}

std::vector<std::string> Dataset::getAvailableDatasets() {
    std::vector<std::string> result{};

    for (auto &p : std::filesystem::directory_iterator(DATASETS_PATH))
        if (p.is_directory())
            result.push_back(p.path().filename().string());

    return result;
}
