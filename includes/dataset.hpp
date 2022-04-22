#ifndef DA_PROJ1_DATASET_H
#define DA_PROJ1_DATASET_H

struct DatasetGenerationParams;
class Dataset;

#include <string>
#include <vector>

#include "order.hpp"
#include "van.hpp"

/**
 * @brief Parameters to customize how Dataset::generate() generates datasets.
 */
struct DatasetGenerationParams {
    // Order params
    /** @brief The number of orders to generate. */
    size_t numberOfOrders{100};

    /** @brief The minimum weight orders will have. */
    unsigned int minOrderWeight{0};
    /** @brief The maximum weight orders will have. */
    unsigned int maxOrderWeight{100};

    /** @brief The minimum volume orders will have. */
    unsigned int minOrderVolume{0};
    /** @brief The maximum volume orders will have. */
    unsigned int maxOrderVolume{100};

    /** @brief The minimum reward orders will give. */
    unsigned int minOrderReward{0};
    /** @brief The maximum reward orders will give. */
    unsigned int maxOrderReward{100};

    /** @brief The minimum amount of time orders will take. */
    unsigned int minOrderDuration{0};
    /** @brief The maximum amount of time orders will take. */
    unsigned int maxOrderDuration{1000};

    // Van params
    /** @brief The number of vans to generate. */
    size_t numberOfVans{5};

    /** @brief The minimum weight vans will handle. */
    unsigned int minVanWeight{0};
    /** @brief The maximum weight vans will handle. */
    unsigned int maxVanWeight{1000};

    /** @brief The minimum volume vans will handle. */
    unsigned int minVanVolume{0};
    /** @brief The maximum volume vans will handle. */
    unsigned int maxVanVolume{1000};

    /** @brief The minimum amount vans will cost. */
    unsigned int minVanCost{0};
    /** @brief The maximum amount vans will cost. */
    unsigned int maxVanCost{1000};
};

/**
 * @brief Holds data from a dataset to be used by different scenarios.
 *
 * @details Also has several static methods to make dataset management easier.
 */
class Dataset {
    /** @brief The vans associated with this dataset. */
    std::vector<Van> vans;
    /** @brief The orders associated with this dataset. */
    std::vector<Order> orders;

    /**
     * @brief Creates a new dataset from the given orders and vans.
     *
     * @param orders The orders to associate with this dataset.
     * @param vans The vans to associate with this dataset.
     */
    Dataset(const std::vector<Order> &orders, const std::vector<Van> &vans);

public:
    /** @return The vans associated with this dataset. */
    const std::vector<Van> &getVans() const;
    /** @return The orders associated with this dataset. */
    const std::vector<Order> &getOrders() const;

    /**
     * @brief Loads a dataset from the given path.
     *
     * @note The path must be relative to ::DATASETS_PATH.
     *
     * @param path The folder where the dataset is.
     *
     * @return The dataset that was loaded.
     */
    static Dataset load(const std::string &path);

    /**
     * @brief Generates a new dataset from pseudo random data and stores it in a
     *        folder.
     *
     * @param name The folder where the dataset will be stored.
     * @param params The parameters given to the random number generators.
     *
     * @return The dataset that was generated.
     */
    static Dataset generate(const std::string &name,
                            const DatasetGenerationParams &params);

    /**
     * @brief Gets all the datasets available to be loaded.
     *
     * @return A vector with the datasets in the ::DATASETS_PATH.
     */
    static std::vector<std::string> getAvailableDatasets();
};

#endif
