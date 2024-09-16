#include <iostream>
#include <string>

#include "detail.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define PROMPT "(d) - decode\n(e) - encode\n"

template <typename T>
void read(const char*, T&);

int
main() {
    char state;
    Detail_info detail;
    cout << PROMPT;
    while (cin >> state) {
        switch (state) {
            case 'd': {
                string str;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "json: ";
                std::getline(cin, str);
                if (detail.decode(str) == 0) {
                    detail.print();
                } else {
                    cout << "error" << endl;
                }
                break;
            }
            case 'e': {
                string id, name;
                std::size_t count;
                read("id: ", id);
                read("name: ", name);
                read("count: ", count);
                string result = detail.encode(id, name, count);
                cout << result << endl;
                break;
            }
            default: {
                cout << "error" << endl;
                break;
            }
        }
        cout << PROMPT;
    }
    return 0;
}

template <typename T>
void
read(const char* prompt, T& var) {
    cout << prompt;
    cin >> var;
}