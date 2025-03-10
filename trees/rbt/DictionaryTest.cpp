/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file DictionaryTest.cpp
 * @brief Main testing file for Dictionary ADT.
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Dictionary.h"

// Constants
constexpr char NEWLINE = '\n';
constexpr bool SHOW_TEST_LOGS = true;

// ANSI Color Codes
constexpr const char *RST = "\x1B[0m";
constexpr const char *RED = "\x1B[31m";
constexpr const char *GRN = "\x1B[32m";
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
 * @brief Logs a test success message.
 * @param test_name The name of the test.
 */
void logSuccess(const std::string &test_name) {
  std::cout << test_name << ": " << formatMessage(GRN, "PASSED") << NEWLINE;
}

/**
 * @brief Handles test failures by throwing an exception.
 * @param message The error message.
 * @note [[noreturn]] ensures function never returns.
 */
[[noreturn]] void handleClientFailure(const std::string &message) {
  std::cerr << "Dictionary Test: " << formatMessage(RED, message) << NEWLINE;
  throw std::runtime_error(message);
}

/**
 * @brief Runs a test and throws an exception on failure.
 * @param res The result of the test (0 for success, nonzero for failure).
 * @param test_name The name of the test.
 */
void runTest(int res, const std::string &test_name) {
  if (res != 0)
    throw std::runtime_error(test_name + " Failure: " + std::to_string(res));
}

/**
 * @brief Tests the insertion of key-value pairs.
 * @param control The expected key-value map.
 * @param D The Dictionary being tested.
 * @param key The key to insert.
 * @param value The value to insert.
 * @return 0 on success, nonzero on failure.
 */
int insertTest(std::map<std::string, int> &control, Dictionary &D,
               const std::string &key, int value) {
  control[key] = value;
  D.setValue(key, value);
  if (!D.contains(key)) return 1;
  if (D.getValue(key) != value || control[key] != D.getValue(key)) return 2;
  if (static_cast<int>(control.size()) != D.size()) return 3;
  return 0;
}

/**
 * @brief Tests dictionary iteration and manipulation operations.
 * @param control The expected key-value map.
 * @param D The Dictionary being tested.
 * @return 0 on success, nonzero on failure.
 */
int manipulationTest(std::map<std::string, int> &control, Dictionary &D) {
  logInfo("Running manipulationTest()");

  // Test end()
  D.end();
  if (control.rbegin()->first != D.currentKey()) return 1;
  logInfo("Passed end()");

  // Test begin()
  D.begin();
  if (control.begin()->first != D.currentKey()) return 2;
  logInfo("Passed begin()");

  std::vector<std::string> keys;

  // Test next()
  for (auto it = control.begin(); it != control.end(); ++it) {
    if (it->first != D.currentKey()) return 3;
    if (it->second % 2 == 0) keys.push_back(D.currentKey());
    D.next();
  }
  logInfo("Passed next()");

  // Test remove()
  for (const std::string &str : keys) {
    D.remove(str);
    control.erase(str);
    if (D.size() != static_cast<int>(control.size())) return 5;
  }
  logInfo("Passed remove()");

  // Test clear()
  control.clear();
  D.clear();
  if (D.size() != static_cast<int>(control.size())) return 6;
  logInfo("Passed clear()");
  if (D.hasCurrent()) return 7;
  logInfo("Passed hasCurrent()");

  return 0;
}

/**
 * @brief Tests dictionary access operations.
 * @param control The expected key-value map.
 * @param D The Dictionary being tested.
 * @return 0 on success, nonzero on failure.
 */
int accessTest(std::map<std::string, int> &control, Dictionary &D) {
  if (D.size() != static_cast<int>(control.size())) return 1;

  std::vector<std::string> keys;
  for (const auto &[key, value] : control) keys.push_back(key);

  for (const std::string &key : keys) {
    if (!D.contains(key)) return 2;
    if (D.getValue(key) != control.at(key)) return 3;
  }

  Dictionary A, B = D;

  // Test iteration
  D.begin();
  for (const auto &[key, value] : control) {
    if (!D.hasCurrent()) return 4;
    if (D.currentKey() != key) return 5;
    if (D.currentVal() != value) return 6;
    A.setValue(D.currentKey(), D.currentVal());
    D.next();
  }

  // Validate dictionary equality
  if (!(A == D)) return 7;
  if (!A.equals(D)) return 8;
  if (!(B == D)) return 9;
  if (!B.equals(D)) return 10;
  if (!((B == D) && (A == B) && (A == D))) return 11;

  return 0;
}

int removeValueTest() {
  // string ideal1 = "d\nb\nc\nf\ne\ng\n";
  // string ideal2 = "e\nb\nc\nf\ng\n";
  // string ideal3 = "e\nb\nc\nf\n";
  Dictionary A;
  std::string ideal1 = "d\nb\nc (RED)\nf\ne (RED)\ng (RED)\n";
  std::string ideal2 = "e\nb\nc (RED)\nf\ng (RED)\n";
  std::string ideal3 = "e\nb\nc (RED)\nf\n";
  // string ideal2 = "c\nb\nf\ne (RED)\ng (RED)\n";
  // string ideal3 = "c\nb\nf\ne (RED)\n";
  A.setValue("d", 1);
  A.setValue("b", 5);
  A.setValue("a", 10);
  A.setValue("c", 15);
  A.setValue("f", 20);
  A.setValue("e", 25);
  A.setValue("g", 30);
  A.begin();
  A.remove("a");
  std::cout << A << '\n';
  if (A.hasCurrent())
    return 1;
  if (A.pre_string() != ideal1)
    return 12;
  A.end();
  A.remove("d");
  if (A.currentKey() != "g" || A.currentVal() != 30)
    return 2;
  if (A.pre_string() != ideal2)
    return 22;
  A.remove("g");
  if (A.hasCurrent())
    return 3;
  if (A.pre_string() != ideal3)
    return 32;
  return 0;
}

/**
 * @brief Main function to execute Dictionary ADT tests.
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @return EXIT_SUCCESS if all tests pass, otherwise EXIT_FAILURE.
 */
int main(int argc, char **argv) {
  try {
    if (argc != 2) handleClientFailure("Wrong number of arguments.");

    std::ifstream file(argv[1]);
    if (!file) handleClientFailure("Cannot read file: " + std::string(argv[1]));

    std::map<std::string, int> control;
    Dictionary D;
    std::string key;
    int index{};

    // Run insert tests
    while (file >> key) {
      runTest(insertTest(control, D, key, ++index), "Insert");
    }
    logSuccess("Insert Test");

    // // Run access tests
    // runTest(accessTest(control, D), "Access");
    // logSuccess("Access Test");

    // // Run manipulation tests
    // runTest(manipulationTest(control, D), "Manipulation");
    // logSuccess("Manipulation Test");

    // Run specific tests
    runTest(removeValueTest(), "Remove Value");
    logSuccess("Remove Value Test");

    return EXIT_SUCCESS;

  } catch (const std::exception &e) {
    // Handle failure
    std::cerr << "Dictionary Test: " << formatMessage(RED, e.what()) << NEWLINE;
    return EXIT_FAILURE;
  }
}
