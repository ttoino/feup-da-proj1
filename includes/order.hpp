#ifndef DA_PROJ1_DELIVERY_H
#define DA_PROJ1_DELIVERY_H

class Order;

#include "dataset.hpp"
#include "van.hpp"

#include <string>
#include <vector>

/**
 * @brief Represents an order that needs to be delivered.
 */
class Order {
    /** @brief Used to generate sequential ids. */
    static unsigned int GLOBAL_ID;

    /** @brief How much volume this order takes up. */
    unsigned int volume;
    /** @brief How much this order weighs. */
    unsigned int weight;
    /** @brief How much reward this order will give. */
    unsigned int reward;
    /** @brief How long this order takes to be delivered. */
    unsigned int duration;
    /** @brief Unique number that identifies this order. */
    unsigned int id;

public:
    /**
     * @brief Creates an order from the given parameters.
     *
     * @param volume How much volume this order takes up.
     * @param weight How much this order weighs.
     * @param reward How much reward this order will give.
     * @param duration How long this order takes to be delivered.
     */
    Order(unsigned int volume, unsigned int weight, unsigned int reward,
          unsigned int duration);

    /** @return How much volume this order takes up. */
    unsigned int getVolume() const;
    /** @return How much this order weighs. */
    unsigned int getWeight() const;
    /** @return How much reward this order will give. */
    unsigned int getReward() const;
    /** @return How long this order takes to be delivered. */
    unsigned int getDuration() const;

    /**
     * @brief Creates an order from a set of tokens.
     *
     * @param tokens The parameters to create the order from. Must be four
     *               strings representing the #volume, #weight, #reward and
     *               #duration for the order.
     *
     * @return The order that was created.
     */
    static Order from(const std::vector<std::string> &tokens);

    /**
     * @brief Loads orders from the dataset at a given path.
     *
     * @note The path must be relative to ::DATASETS_PATH.
     *
     * @param path The folder where the dataset is.
     *
     * @return A vector of orders that were loaded.
     */
    static std::vector<Order> processDataset(const std::string &path);

    /**
     * @brief Generates orders for a new dataset from pseudo random data and
     *        stores them in a file.
     *
     * @param name The folder where the dataset will be stored.
     * @param params The parameters given to the random number generators.
     *
     * @return The vector of orders that were generated.
     */
    static std::vector<Order>
    generateDataset(const std::string &name,
                    const DatasetGenerationParams &params);

    /**
     * @brief Prints a representation of an Order to a stream.
     *
     * @param out The stream to print to.
     * @param order The order to print.
     *
     * @return @p out
     */
    friend std::ostream &operator<<(std::ostream &out, const Order &order);

    // Scenario 1 & 2
    /**
     * @brief Function to be used in std::sort() to sort orders by ascending
     *        #volume.
     */
    static bool compareByVolumeAsc(const Order &o1, const Order &o2);
    /**
     * @brief Function to be used in std::sort() to sort orders by descending
     *        #volume.
     */
    static bool compareByVolumeDesc(const Order &o1, const Order &o2);
    /**
     * @brief Function to be used in std::sort() to sort orders by ascending
     *        #weight.
     */
    static bool compareByWeightAsc(const Order &o1, const Order &o2);
    /**
     * @brief Function to be used in std::sort() to sort orders by descending
     *        #weight.
     */
    static bool compareByWeightDesc(const Order &o1, const Order &o2);
    /**
     * @brief Function to be used in std::sort() to sort orders by ascending
     *        "area" (#volume × #weight).
     */
    static bool compareByAreaAsc(const Order &o1, const Order &o2);
    /**
     * @brief Function to be used in std::sort() to sort orders by descending
     *        "area" (#volume × #weight).
     */
    static bool compareByAreaDesc(const Order &o1, const Order &o2);

    // Scenario 3
    /**
     * @brief Function to be used in std::sort() to sort orders by ascending
     *        #duration.
     */
    static bool compareByDuration(const Order &o1, const Order &o2);
};

#endif
