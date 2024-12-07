/**
 * @file main.cpp
 * @brief Main entry point for the Detail_info encoding and decoding application.
 */

#include "main.hpp"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define PROMPT "(d) - decode\n(e) - encode\n"

/**
 * @brief Main function. Provides a prompt to either encode or decode a Detail_info object.
 * @return Returns 0 on success, 1 on failure.
 */
int
main() {
    char state;
    Detail_info detail;
    cout << PROMPT;
    while (cin >> state) {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try {
            switch (state) {
                case 'd': {
                    decode(detail);
                    break;
                }
                case 'e': {
                    encode(detail);
                    break;
                }
                default: {
                    cout << "error" << endl;
                    break;
                }
            }
        } catch (errors) {
            cout << "Bad json string" << endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << endl;
            return 1;
        }
        cout << PROMPT;
    }
    return 0;
}

/**
 * @brief Decodes the input string into a Detail_info object and prints the result.
 * @param detail A reference to the Detail_info object to be populated.
 * @throws std::runtime_error if input fails or decoding is unsuccessful.
 */
void
decode(Detail_info& detail) {
    string str;
    try {
        str = get_str("json: ");
        detail.decode(str);
        detail.print();
    } catch (...) {
        throw;
    }
}

/**
 * @brief Encodes user input into a JSON-like string and prints it.
 * @param detail A reference to the Detail_info object to be encoded.
 * @throws std::runtime_error if input fails or encoding is unsuccessful.
 */
void
encode(Detail_info& detail) {
    string id, name;
    std::size_t count;
    try {
        id = get_str("id: ");
        name = get_str("name: ");
        count = get_num<std::size_t>("count: ");
        string result = detail.encode(id, name, count);
        cout << result << endl;
    } catch (...) {
        throw;
    }
}

/**
 * @brief Prompts the user to input a string value.
 * @param prompt The prompt to be displayed to the user.
 * @return The user input as a string.
 * @throws std::runtime_error if the input fails (EOF or error).
 */
string
get_str(const char* prompt) {
    string var;
    cout << prompt;
    getline(cin, var);
    if (cin.eof()) {
        throw std::runtime_error("Failed to read string: EOF");
    } else if (cin.bad()) {
        throw std::runtime_error(std::string("Failed to read string: ") + strerror(errno));
    } else {
        return var;
    }
}

/**
 * @brief Prompts the user to input a numeric value within a specified range.
 * @tparam T The type of the numeric value (e.g., int, float, std::size_t).
 * @param prompt The prompt to be displayed to the user.
 * @param min The minimum acceptable value.
 * @param max The maximum acceptable value.
 * @return The user input as a numeric value of type T.
 * @throws std::runtime_error if the input fails or the value is out of range.
 */
template <typename T>
T
get_num(const char* prompt, T min, T max) {
    T a;
    while (true) {
        cout << prompt;
        cin >> a;
        if (cin.eof()) {
            throw std::runtime_error("Failed to read number: EOF");
        } else if (cin.bad()) {
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        } else if (cin.fail() || a < min || a > max) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "You are wrong; repeat please!" << endl;
        } else {
            return a;
        }
    }
}
