#ifndef DA_PROJ1_2021_DELIVERY_H
#define DA_PROJ1_2021_DELIVERY_H

#include <vector>
#include <string>

/**
 * @brief Object representatioion for a delivery in the context of the application.
 * 
 */
class Delivery {

    int volume, weight, reward, duration;
public:

    /**
     * @brief Construct a new Delivery object
     * 
     * @param vol the volume of this delivery
     * @param weight the weight of this delivery
     * @param reward the reward for this delivery
     * @param duration the duration of this delivery
     */
    Delivery(int vol, int weight, int reward, int duration);

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
     * @brief Creates a Delivery object from a set of tokens;
     * 
     * @return the corresponding Delivery object
     */
    static Delivery from(const std::vector<std::string>&);
};

#endif