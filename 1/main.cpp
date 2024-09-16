#include <iostream>
#include <limits>
#include <string.h>

#include "detail.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define PROMPT "(d) - decode\n(e) - encode\n"

string get_str(const char*);

template <typename T>
T get_num(const char*, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max());

void decode(Detail_info&);
void encode(Detail_info&);

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