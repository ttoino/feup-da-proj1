#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/van.hpp"

Dataset Dataset::load() {
    Dataset dataset;

    dataset.orders = Order::processDataset();
    dataset.vans = Van::processDataset();

    return dataset;
}
