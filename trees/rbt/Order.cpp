/**
 * @author Ethan Okamura
 * @file Order.cpp
 * @brief Inserts key-value pairs and displays the Dictionary ADT.
 */

#include <fstream>
#include <stdexcept>

#include "Dictionary.h"

// Constants
constexpr char NEWLINE = '\n';
constexpr bool SHOW_TEST_LOGS = true;
// ANSI Color Codes
constexpr const char *RST = "\x1B[0m";
constexpr const char *RED = "\x1B[31m";
constexpr const char *BLU = "\x1B[34m";

/**
 * @brief Formats a message with a given color.
 * @param color The ANSI color code.
 * @param message The message to format.
 * @return Formatted string.
 */
std::string formatMessage(const char *color, const std::string &message) {
  return std::string(color) + message + RST;
}

/**
 * @brief Logs an informational message if logging is enabled.
 * @param message The message to log.
 */
void logInfo(const std::string &message) {
  if (SHOW_TEST_LOGS) std::cout << formatMessage(BLU, message) << NEWLINE;
}

/**
 * @brief Formats an error message in red.
 * @param message The message to be formatted.
 * @return Formatted string.
 */
std::string formatError(const std::string &message) {
  return RED + message + RST;
}

/**
 * @brief Generic function to handle failures.
 * @param message The error message to display.
 * @note [[noreturn]] throws instead of returning.
 */
[[noreturn]] void handleClientFailure(const std::string &message) {
  std::cerr << "Order: " << formatError(message) << NEWLINE;
  throw std::runtime_error(message);
}

/**
 * @brief Inserts and displays data inside the Dictionary ADT.
 * @param argc The number of arguments.
 * @param argv The array of arguments (of type char*).
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int main(int argc, char **argv) {
  try {
    // Ensure correct number of arguments
    if (argc != 3) handleClientFailure("Usage: Order <inputFile> <outputFile>");
    // Open input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile)
      handleClientFailure("Cannot read file: " + std::string(argv[1]));

    // Open output file
    std::ofstream outputFile(argv[2]);
    if (!outputFile)
      handleClientFailure("Cannot write to file: " + std::string(argv[2]));

    // Read input file and insert into dictionary
    Dictionary dict;
    std::string key;
    int counter = 0;

    // Read from input
    while (inputFile >> key) dict.setValue(key, ++counter);

    // Write to output
    outputFile << dict << NEWLINE << dict.pre_string() << NEWLINE;

    return EXIT_SUCCESS;
  } catch (const std::exception &e) {
    // Handle failure
    std::cerr << "Order: " << formatError(e.what()) << NEWLINE;
    return EXIT_FAILURE;
  }
}
