#ifndef DA_PROJ1_SCENARIO1_HPP
#define DA_PROJ1_SCENARIO1_HPP

#include "dataset.hpp"
#include "van.hpp"
#include "order.hpp"

#include <iostream>
#include <string>

struct Data {
    std::vector<Order> orders;
    std::vector<Van> vans;
    int vansUsed = 0, ordersDispatched = 0;
};


/**
 * @brief the number of vans is minimized and the number of orders delivered is maximized
 *
 * @param option how to sort the vans and orders
 *
 * @details option must be "volume" or "weight"
 *
 * @note the vans are sorted by <option> in descending order
 * @note the orders are sorted by <option> in ascending order
 */
Data scenario1(std::string &option);

Data scenario2();


#endif //DA_PROJ1_SCENARIO1_HPP
