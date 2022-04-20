#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/van.hpp"

Dataset Dataset::load(const std::string &path) {
    Dataset dataset;

    dataset.orders = Order::processDataset(path);
    dataset.vans = Van::processDataset(path);

    return dataset;
}
