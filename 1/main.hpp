/**
 * @file main.hpp
 * @brief Header file for the main application functions.
 */

#ifndef LAB1_MAIN_HPP
#define LAB1_MAIN_HPP

#include <string.h>
#include "detail.hpp"

/**
 * @brief Prompts the user to input a string value.
 * @param prompt The prompt to be displayed to the user.
 * @return The user input as a string.
 * @throws std::runtime_error if the input fails (EOF or error).
 */
string get_str(const char* prompt);

/**
 * @brief Prompts the user to input a numeric value within a specified range.
 * @tparam T The type of the numeric value (e.g., int, float, std::size_t).
 * @param prompt The prompt to be displayed to the user.
 * @param min The minimum acceptable value (default is lowest possible value).
 * @param max The maximum acceptable value (default is highest possible value).
 * @return The user input as a numeric value of type T.
 * @throws std::runtime_error if the input fails or the value is out of range.
 */
template <typename T>
T get_num(const char* prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max());

/**
 * @brief Decodes the input string into a Detail_info object and prints the result.
 * @param detail A reference to the Detail_info object to be populated.
 * @throws std::runtime_error if input fails or decoding is unsuccessful.
 */
void decode(Detail_info& detail);

/**
 * @brief Encodes user input into a JSON-like string and prints it.
 * @param detail A reference to the Detail_info object to be encoded.
 * @throws std::runtime_error if input fails or encoding is unsuccessful.
 */
void encode(Detail_info& detail);

#endif // LAB1_MAIN_HPP
