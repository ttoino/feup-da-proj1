#ifndef DA_PROJ1_2021_UI_H
#define DA_PROJ1_2021_UI_H

class UserInterface;

#include <limits>
#include <string>
#include <vector>

/**
 * @brief Holds the possible menu values.
 */
enum Menu {
    /**
     * @brief Displays an initial menu to start the program.
     */
    MAIN,
    /**
     * @brief Exits the program.
     */
    EXIT
};

/**
 * @brief Implements the terminal interface for the user to interact with the
 *        application.
 */
class UserInterface {
    /**
     * @brief Specifies which menu to show.
     */
    Menu currentMenu;

    /**
     * @brief The error message to show.
     */
    std::string errorMessage{};

    /**
     * @brief Helper method to show a menu with options.
     *
     * @details Each option string will be shown along with its index on the
     *          list. When the user inputs one of the indices of the list
     *          _currentMenu will be set to that option's Menu.
     *
     * @note The first option on the list will be shown last and is
     *       intended to be a way to go back in the navigation tree.
     *
     * @param options The list of options to show
     */
    void optionsMenu(
        const std::vector<std::pair<const std::string &, Menu>> &options);

    /**
     * @brief Tries to transform a string into an unsigned integer, displaying
     * an error message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an
     * error message if the prompt is outside of the designated limit.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @param prompt Shown to the user.
     * @param min The left bound of the limit (inclusive).
     * @param max The right bound of the limit (inclusive).
     * @return The user input, as an unsigned integer.
     */
    unsigned long getUnsignedInput(
        const std::string &prompt, unsigned long min = 0,
        unsigned long max = std::numeric_limits<unsigned long>::max());

    /**
     * @brief Tries to transform a string into a double, displaying an error
     *        message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an
     * error message if the prompt is outside of the designated limit.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @param prompt Shown to the user.
     * @param min The left bound of the limit (inclusive).
     * @param max The right bound of the limit (inclusive).
     * @return The user input, as an unsigned integer.
     */
    double getDoubleInput(const std::string &prompt,
                          double min = std::numeric_limits<double>::min(),
                          double max = std::numeric_limits<double>::max());

    /**
     * @brief Gets a line from stdin and normalizes it.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @throws Exit if the EOF bit is set.
     *
     * @param prompt Shown to the user.
     * @return The user input.
     */
    std::string getStringInput(const std::string &prompt);

    /**
     * @brief Checks if an unsigned integer n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
    bool inRange(unsigned long n, unsigned long min, unsigned long max);

    /**
     * @brief Checks if a double n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
    bool inRange(double n, double min, double max);

    /**
     * @brief Displays an initial menu to start the program.
     */
    void mainMenu();

public:
    /**
     * @brief Shows the current menu.
     *
     * @param graph The graph.
     */
    void show();
    /**
     * @brief Shows a message before the program exits.
     */
    void exit();
};

#endif // DA_PROJ1_2021_UI_H
