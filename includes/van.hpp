#ifndef DA_PROJ1_VAN_H
#define DA_PROJ1_VAN_H

class Van;

#include "dataset.hpp"
#include "order.hpp"

#include <string>
#include <vector>

/**
 * @brief Represents a van that can deliver orders.
 */
class Van {
    /** @brief Used to generate sequential ids. */
    static unsigned int GLOBAL_ID;

    /** @brief How much volume this van can handle. */
    unsigned int maxVolume;
    /** @brief How much weight this van can handle. */
    unsigned int maxWeight;
    /** @brief How much this van costs to operate. */
    unsigned int cost;
    /** @brief How much volume this van is carrying. */
    unsigned int currentVolume;
    /** @brief How much weight this van is carrying. */
    unsigned int currentWeight;
    /** @brief Unique number that identifies this van. */
    unsigned int id;
    /** @brief The orders this van is delivering. */
    std::vector<Order> orders;

public:
    /**
     * @brief Creates a van from the given parameters
     *
     * @param maxVolume How much volume this van can handle.
     * @param maxWeight How much weight this van can handle.
     * @param cost How much this van costs to operate.
     */
    Van(unsigned int maxVolume, unsigned int maxWeight, unsigned int cost);

    /** @return How much volume this van can handle. */
    unsigned int getMaxVolume() const;
    /** @return How much weight this van can handle. */
    unsigned int getMaxWeight() const;
    /** @return How much this van costs to operate. */
    unsigned int getCost() const;
    /** @return How much volume this van is carrying. */
    unsigned int getCurrentVolume() const;
    /** @return How much weight this van is carrying. */
    unsigned int getCurrentWeight() const;
    /** @return The orders this van is delivering. */
    std::vector<Order> getOrders() const;

    /**
     * @brief Creates a van from a set of tokens.
     *
     * @param tokens The parameters to create the order from. Must be three
     *               strings representing the #maxVolume, #maxWeight and #cost
     *               for the van.
     *
     * @return The van that was created.
     */
    static Van from(const std::vector<std::string> &tokens);

    /**
     * @brief Loads vans from the dataset at a given path.
     *
     * @note The path must be relative to ::DATASETS_PATH.
     *
     * @param path The folder where the dataset is.
     *
     * @return A vector of vans that were loaded.
     */
    static std::vector<Van> processDataset(const std::string &path);

    /**
     * @brief Generates vans for a new dataset from pseudo random data and
     *        stores them in a file.
     *
     * @param name The folder where the dataset will be stored.
     * @param params The parameters given to the random number generators.
     *
     * @return The vector of vans that were generated.
     */
    static std::vector<Van>
    generateDataset(const std::string &name,
                    const DatasetGenerationParams &params);

    /**
     * @brief Adds an order to this van.
     *
     * @param order The order to be added.
     *
     * @return true if successful.
     * @return false otherwise.
     */
    bool addOrder(const Order &order);

    /**
     * @brief Checks if an order can fit in this van.
     *
     * @param order The order.
     *
     * @return Whether the order can fit in this van.
     */
    bool canFit(const Order &order) const;

    /**
     * @brief Prints a representation of a van to a stream.
     *
     * @param out The stream to print to.
     * @param van The van to print.
     *
     * @return @p out
     */
    friend std::ostream &operator<<(std::ostream &out, const Van &van);

    // Scenario 1
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        #maxVolume.
     */
    static bool compareByVolume(const Van &v1, const Van &v2);
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        #maxWeight.
     */
    static bool compareByWeight(const Van &v1, const Van &v2);
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        "max area" (#maxVolume × #maxWeight).
     */
    static bool compareByArea(const Van &v1, const Van &v2);

    // Scenario 2
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        #maxVolume divided by #cost.
     */
    static bool compareByVolumeOverCost(const Van &v1, const Van &v2);
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        #maxWeight divided by #cost.
     */
    static bool compareByWeightOverCost(const Van &v1, const Van &v2);
    /**
     * @brief Function to be used in std::sort() to sort vans by descending
     *        "max area" (#maxVolume × #maxWeight) divided by #cost.
     */
    static bool compareByAreaOverCost(const Van &v1, const Van &v2);
};

#endif
