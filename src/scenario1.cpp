#include "../includes/scenario1.hpp"
#include "../includes/dataset.hpp"
#include "../includes/order.hpp"
#include "../includes/van.hpp"

#include <vector>
#include <algorithm>

void scenario1() {
    Dataset dataset;
    std::vector<Order> orders = dataset.getOrders();
    std::vector<Van> vans = dataset.getVans();

    std::sort(vans.begin(), vans.end(), [] (const Van &v1, const Van &v2) {
        if(v1.getMaxVolume() == v2.getMaxWeight()) {
            return v1.getMaxWeight() > v2.getMaxWeight();
        }
        return v1.getMaxVolume() > v2.getMaxVolume();
    });

    std::sort(orders.begin(), orders.end(), [] (const Order &order1, const Order &order2) {
        if(order1.getVolume() == order2.getVolume()) {
            return order1.getWeight() < order2.getWeight();
        }
        return order1.getVolume() < order2.getVolume();
    });

}