#include <filesystem>

#include "../includes/constants.hpp"
#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/van.hpp"

Dataset::Dataset(const std::vector<Order> &orders, const std::vector<Van> &vans)
    : orders(orders), vans(vans) {}

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
