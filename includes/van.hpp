#ifndef DA_PROJ1_VAN_H
#define DA_PROJ1_VAN_H

class Van;

#include "dataset.hpp"
#include "order.hpp"

#include <string>
#include <vector>

/**
 * @brief Object representation for a van in the context of the application.
 */
class Van {

    static int GLOBAL_ID;

    int maxVolume, maxWeight, cost, currentVolume, currentWeight, id;
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

    // TODO: Documentation
    std::vector<Order> getOrders() const;

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
    static std::vector<Van> processDataset(const std::string &path);

    static std::vector<Van>
    generateDataset(const std::string &name,
                    const DatasetGenerationParams &params);

    /**
     * @brief assigns an order to a van
     *
     * @param order the order to be assigned
     *
     * @return true if successfully, false otherwise
     */
    bool addOrder(const Order &order);

    /**
     * @brief Checks if an order can fit in this van.
     *
     * @return if the order can fit in this van
     */
    bool canFit(const Order &order) const;

    /**
     * @brief Prints statistics about this van.
     *
     * @param out the output stream to write the statistics to
     */
    void printStatistics(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &, const Van &);

    // Scenario 1
    static bool compareByVolume(const Van &v1, const Van &v2);
    static bool compareByWeight(const Van &v1, const Van &v2);
    static bool compareByArea(const Van &v1, const Van &v2);

    // Scenario 2
    static bool compareByVolumeOverCost(const Van &v1, const Van &v2);
    static bool compareByWeightOverCost(const Van &v1, const Van &v2);
    static bool compareByAreaOverCost(const Van &v1, const Van &v2);
};

#endif
