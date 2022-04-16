#include "../includes/scenario2.hpp"

#include <vector>
#include <list>

SimulationResult Simulation2::run() {
    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders(), remainingOrders = {};
    std::vector<Van> vans = dataset.getVans(), resultVans = {};

    int ordersForTheDay = orders.size();
    int vansForTheDay = vans.size();

    int vansUsed = 0, ordersDispatched = 0;
    int cost = 0, reward = 0;
    double deliveryTime = 0.0;

    if(option == Simulation2::SimulationOptions::DIVIDE) {
        std::sort(vans.begin(), vans.end(), compareVanByCostDivision);
        std::sort(orders.begin(), orders.end(), compareOrderByRewardDivision);
    } else if (option == Simulation2::SimulationOptions::MULTIPLY) {
        std::sort(vans.begin(), vans.end(), compareVanByCostMult);
        std::sort(orders.begin(), orders.end(), compareOrderByRewardMult);
    } else {
        std::cerr << "Invalid option\n";
        return {};
    }

    auto vanIterator = vans.begin();
    auto orderIterator = orders.begin();

    while (
            vanIterator != vans.end() && // while we still have vans to carry orders
            orderIterator != orders.end() // while we still have orders to process
            ) {
        if (!vanIterator->canFit(*orderIterator)) {
            // we have exhausted the current van, move to the next one
            resultVans.push_back(*vanIterator);
            cost += vanIterator->getCost();
            vanIterator++;
            vansUsed++;
        }

        if (vanIterator != vans.end()) {
            deliveryTime += orderIterator->getDuration();
            reward += orderIterator->getReward();
            vanIterator->addOrder(*orderIterator++);
            ordersDispatched++;
        }
    }

    remainingOrders.assign(orderIterator, orders.end());

    return {remainingOrders, resultVans,    vansUsed,    ordersDispatched,
            ordersForTheDay, vansForTheDay,     deliveryTime,   cost, reward};
}

SimulationResult Simulation2::run2DVSBPP() {

    Dataset dataset = Dataset::load();

    std::vector<Order> orders = dataset.getOrders();
    std::vector<Van> vans = dataset.getVans();

    /* 
     * Check if there is an item that does not fit into any bin     
     *
     * Space complexity: O(1)
     *
     * Time complexity:
     * - Best case: O(|O|) -> if the first bin in the vector can contain every item individually
     * - Worst case: O(|O|*|V|) -> if the last bin in the vector can contain every item individually
     */
    for (const Order &order : orders) {

        bool canFit = false;

        for (const Van &van: vans)
            if (van.canFit(order)) {
                canFit = true; 
                break;
            }

        if (!canFit) { // no solution
            return {};
        }
    }

    /*
     * Eliminate dominated bins.
     * 
     * Space complexity: O(|V|) -> creation of a linked list to perform the algorithm.
     * 
     * Time complexity:
     * - Best case: O(|V|) -> if only the first bin is fit for the simulation
     * - Worst case: O(|V|²) -> if there are no dominated bins
     * 
     * Since this algorithm is being backed by a linked list, item removal is constant time, thus not introducing any overhead
     */
    std::list<Van> vanList(vans.begin(), vans.end()); // Space Complexity: O(|O|)
    auto van1 = vanList.begin(), van2 = vanList.begin();

    /* 
     * Use this here to avoid writing another loop, 
     * we can do this since the bin removal only removes lower valued bins, 
     * so the maximum values should be kept
     */
    int maxVol = INT32_MIN, maxWeight = INT32_MIN; 

    while (van1 != vanList.end()) {

        if (van1 == van2) continue;

        // These 2 lines are not related to the bin removal algorithm but can save us some iterations later on
        if (maxVol < van1->getMaxVolume()) maxVol = van1->getMaxVolume();
        if (maxWeight < van1->getMaxWeight()) maxWeight = van1->getMaxWeight();

        if (
            van2->getCost()      >= van1->getCost()      &&
            van2->getMaxWeight() <= van1->getMaxWeight() &&
            van2->getMaxWeight() <= van1->getMaxWeight()
        ) { // we can remove van2 because we know that there are optimal solutions which do not include it
            van2 = vanList.erase(van2);
        }

        if (van2 == vanList.end()) {
            van2 = vanList.begin();
            van1++;
        } else
            van2++;
    }
    vans.assign(vanList.begin(), vanList.end());

    // Decision variables

    bool left[orders.size()][orders.size()]; // Space complexity: O(|O|²)
    bool below[orders.size()][orders.size()]; // Space complexity: O(|O|²)
    bool located[orders.size()][vans.size()]; // Space complexity: O(|O|*|V'|)
    bool used[vans.size()]; // Space complexity: O(|V'|)

    return {};
}