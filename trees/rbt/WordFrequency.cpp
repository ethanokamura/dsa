/**
 * @author Ethan Okamura
 * @file Order.cpp
 * @brief Inserts key-value pairs and displays the Dictionary ADT.
 */

#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "Dictionary.h"

// Constants
constexpr char NEWLINE = '\n';
constexpr bool SHOW_TEST_LOGS = true;
// ANSI Color Codes
constexpr const char *RST = "\x1B[0m";
constexpr const char *KRED = "\x1B[31m";
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
 * @brief Formats an error message in Kred.
 * @param message The message to be formatted.
 * @return Formatted string.
 */
std::string formatError(const std::string &message) {
  return KRED + message + RST;
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
 * @brief Inserts key into Dictionary ADT
 * @param dict A reference to the Dictionary.
 * @param key The key to be inserted.
 */
void insertDict(Dictionary& dict, std::string key) {
  if (dict.contains(key)) {
    dict.getValue(key)++;
  } else {
    dict.setValue(key, 1);
  }
}

/**
 * @brief Inserts and displays data inside the Dictionary ADT.
 * @param argc The number of arguments.
 * @param argv The array of arguments (of type char*).
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int main(int argc, char **argv) {
  try {
    const std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary dict;
    size_t begin, end, len;
    std::string line;
    std::string token;
    // Ensure correct number of arguments
    if (argc != 3) handleClientFailure("Usage: Order <input> <output>");
    // Open input file
    std::ifstream in(argv[1]);
    if (!in) handleClientFailure("Cannot read file: " + std::string(argv[1]));

    // Open output file
    std::ofstream out(argv[2]);
    if (!out)
      handleClientFailure("Cannot write to file: " + std::string(argv[2]));

    // Read input file and insert into dictionary

    logInfo("starting input");
    while (getline(in, line)) {
      // Read from input
      len = line.length();

      // get first token
      begin = std::min(line.find_first_not_of(delim, 0), len);
      end = std::min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end - begin);

      while (!token.empty()) {  // we have a token
        // to lower
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        // insert into tree
        insertDict(dict, token);
        // get next token
        begin = std::min(line.find_first_not_of(delim, end + 1), len);
        end = std::min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end - begin);
      }
    }
    logInfo("finished input");
    // Write to output
    out << dict;
    return EXIT_SUCCESS;
  } catch (const std::exception &e) {
    // Handle failure
    std::cerr << "Order: " << formatError(e.what()) << NEWLINE;
    return EXIT_FAILURE;
  }
}
