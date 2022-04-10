#ifndef DA_PROJ1_2021_VAN_H
#define DA_PROJ1_2021_VAN_H

#include <vector>
#include <string>

/**
 * @brief Object representatioion for a van in the context of the application.
 * 
 */
class Van {

    int maxVolume, maxWeight, cost;
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
     * @brief Constructs a Van object from a collection of tokens. 
     * 
     * @return the corresponding Van object 
     */
    static Van from(const std::vector<std::string>&);

    /**
     * @brief Processes the dataset for vans and returns a collection of Van objects parsed from that dataset.
     * 
     * @return a collection of Van objects
     */
    static std::vector<Van> processDataset();

    friend std::ostream& operator<<(std::ostream&, const Van&); 
};

#endif