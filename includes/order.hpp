#ifndef DA_PROJ1_DELIVERY_H
#define DA_PROJ1_DELIVERY_H

class Order;

#include "dataset.hpp"
#include "van.hpp"

#include <string>
#include <vector>

/**
 * @brief Object representation for a delivery in the context of the
 * application.
 */
class Order {

    static int GLOBAL_ID;

    int volume, weight, reward, duration, id;

public:
    /**
     * @brief Construct a new Order object
     *
     * @param vol the volume of this delivery
     * @param weight the weight of this delivery
     * @param reward the reward for this delivery
     * @param duration the duration of this delivery
     */
    Order(int vol, int weight, int reward, int duration);

    /**
     * @brief Get the volume of this delivery
     *
     * @return the volume of this delivery
     */
    int getVolume() const;

    /**
     * @brief Get the weight of this delivery
     *
     * @return the weight of this delivery
     */
    int getWeight() const;

    /**
     * @brief Get the reward for this delivery
     *
     * @return the reward for this delivery
     */
    int getReward() const;

    /**
     * @brief Get the duration of this delivery
     *
     * @return the duration of this delivery
     */
    int getDuration() const;

    /**
     * @brief Creates a Order object from a set of tokens;
     *
     * @return the corresponding Order object
     */
    static Order from(const std::vector<std::string> &);

    /**
     * @brief Processes the dataset for vans and returns a collection of Van
     * objects parsed from that dataset.
     *
     * @return a collection of Van objects
     */
    static std::vector<Order> processDataset(const std::string &path);

    static std::vector<Order>
    generateDataset(const std::string &name,
                    const DatasetGenerationParams &params);

    friend std::ostream &operator<<(std::ostream &, const Order &);

    // Scenario 1 & 2
    static bool compareByVolumeAsc(const Order &o1, const Order &o2);
    static bool compareByVolumeDesc(const Order &o1, const Order &o2);
    static bool compareByWeightAsc(const Order &o1, const Order &o2);
    static bool compareByWeightDesc(const Order &o1, const Order &o2);
    static bool compareByAreaAsc(const Order &o1, const Order &o2);
    static bool compareByAreaDesc(const Order &o1, const Order &o2);

    // Scenario 2
    // static bool compareByRewardDivision(const Order &o1, const Order &o2);
    // static bool compareByRewardMult(const Order &o1, const Order &o2);

    // Scenario 3
    static bool compareByDuration(const Order &o1, const Order &o2);
};

#endif
