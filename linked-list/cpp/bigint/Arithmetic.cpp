/**
 * @author Ethan Okamura
 * @file Arithmetic.cpp
 * @brief Perform a gauntlet of arithmetic
 *        operations on a BigInteger ADT
 */

#include <array>
#include <fstream>
#include <stdexcept>

#include "BigInteger.h"

/// @brief Test cases enum to help consistency
enum class Test {
  TEST_1,
  TEST_2,
  TEST_3,
  TEST_4,
  TEST_5,
  TEST_6,
  TEST_7,
  TEST_8,
  TEST_9,
  TEST_10
};

/**
 * @brief Generic function to handle failures.
 * @param message The error message to display.
 */
int handle_failure(std::string message) {
  std::cerr << "Arithmetic: " << message << std::endl;
  return EXIT_FAILURE;
}

/**
 * @brief Handles operations between 2 BigInts
 * @param A The first BigInt ADT.
 * @param B The second BigInt ADT.
 * @param code The operation code (from enum).
 */
BigInteger arithmetic_gauntlet(const BigInteger &A, const BigInteger &B,
                               Test code) {
  BigInteger C(1);
  BigInteger D(1);
  switch (code) {
    case Test::TEST_1:
      return A;
    case Test::TEST_2:
      return B;
    case Test::TEST_3:
      return A + B;
    case Test::TEST_4:
      return A - B;
    case Test::TEST_5:
      return A - A;
    case Test::TEST_6:
      return (3 * A) - (2 * B);
    case Test::TEST_7:
      return A * B;
    case Test::TEST_8:
      return A * A;
    case Test::TEST_9:
      return B * B;
    case Test::TEST_10:
      for (int i = 0; i < 4; i++) {
        C *= A;
      }
      for (int i = 0; i < 5; i++) {
        D *= B;
      }
      return (9 * C) + (16 * D);
    default:
      // Basic error handling
      throw std::logic_error("Arithmetic: Invalid test");
  }
}

/**
 * @brief Handles operations between 2 BigInts
 * @param argc The number of arguements
 * @param argv The array of arguements (of type char*)
 */
int main(int argc, char **argv) {
  // Ensure correct number of arguments
  if (argc != 3) {
    return handle_failure("Wrong number of arguments.");
  }

  // Init files
  std::string input_file_name{argv[1]};
  std::string output_file_name{argv[2]};

  // Open input file
  std::ifstream input_file(input_file_name);
  if (!input_file) {
    return handle_failure("Cannot read file.");
  }

  // Read input file and get BigInt strings
  std::string A_str, B_str, temp;
  if (!(std::getline(input_file, A_str) && std::getline(input_file, temp) &&
        std::getline(input_file, B_str))) {
    return handle_failure("Input file format is incorrect.");
  }

  // Initialize BigInt instances
  BigInteger A(A_str), B(B_str);

  // Define tests using std::array
  std::array<Test, 10> tests = {
      Test::TEST_1, Test::TEST_2, Test::TEST_3, Test::TEST_4, Test::TEST_5,
      Test::TEST_6, Test::TEST_7, Test::TEST_8, Test::TEST_9, Test::TEST_10,
  };

  // Open to output file
  std::ofstream output_file(output_file_name);
  if (!output_file) {
    return handle_failure("Cannot write to file.");
  }

  // Write to output file
  for (const auto &test : tests) {
    try {
      output_file << arithmetic_gauntlet(A, B, test) << "\n\n";
    } catch (std::logic_error &e) {
      return handle_failure(e.what());
    }
  }

  return EXIT_SUCCESS;
}
