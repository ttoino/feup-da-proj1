#ifndef DA_PROJ1_VAN_H
#define DA_PROJ1_VAN_H

class Order;

#include <string>
#include <vector>
#include "order.hpp"

/**
 * @brief Object representation for a van in the context of the application.
 */
class Van {

    int maxVolume, maxWeight, cost, currentVolume, currentWeight;
    std::vector<Order> orders;

public:
    /**
     * @brief Construct a new Van object
     *
     * @param maxVol the maximum volume this Van can hold
     * @param maxWeight the maximum weight this Van can hold
     * @param cost the cost of moving cargo using this Van
     */
    Van(int maxVol, int maxWeight, int cost);

    /**
     * @brief Get this Van's maximum volume.
     *
     * @return this Van's maximum volume
     */
    int getMaxVolume() const;

    /**
     * @brief Get this Van's maximum weight.'
     *
     * @return this Van's maximum weight'
     */
    int getMaxWeight() const;

    /**
     * @brief Get the cost for using this Van.
     *
     * @return the cost of moving cargo using this Van
     */
    int getCost() const;

    /**
     * @brief Get the current volume allocated for this van.
     * 
     * @return the current volume allocated for this Van
     */
    int getCurrentVolume() const;

    /**
     * @brief Get the current weight allocated for this van.
     * 
     * @return the current weight allocated for this van
     */
    int getCurrentWeight() const;

    /**
     * @brief Constructs a Van object from a collection of tokens.
     *
     * @return the corresponding Van object
     */
    static Van from(const std::vector<std::string> &);

    /**
     * @brief Processes the dataset for vans and returns a collection of Van
     * objects parsed from that dataset.
     *
     * @return a collection of Van objects
     */
    static std::vector<Van> processDataset();

    /**
     * @brief assigns an order to a van
     *
     * @param order the order to be assigned
     */
    void addOrder(const Order &order);

    friend std::ostream &operator<<(std::ostream &, const Van &);
};

#endif
