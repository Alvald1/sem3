/**
 * @file detail.cpp
 * @brief Implementation of the Detail_info class and its associated methods.
 */

#include "detail.hpp"
#include <format>
#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Initializes a Detail_info object with the given values.
 * @param id The ID of the detail.
 * @param name The name of the detail.
 * @param count The count of the detail.
 */
void
Detail_info::init(const string& id, const string& name, std::size_t count) {
    this->id = id;
    this->name = name;
    this->count = count;
}

/**
 * @brief Encodes the detail information into a JSON-like string.
 * @return A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
 */
string
Detail_info::encode() {
    return std::format("{{'id':'{}','name':'{}','count':{}}}", this->id, this->name, this->count);
}

/**
 * @brief Encodes the provided detail information into a JSON-like string.
 * @param id The ID of the detail.
 * @param name The name of the detail.
 * @param count The count of the detail.
 * @return A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
 */
string
Detail_info::encode(const string& id, const string& name, std::size_t count) {
    this->init(id, name, count);
    return this->encode();
}

/**
 * @brief Decodes a JSON-like string and extracts the detail information.
 * @param str A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
 * @throws errors::BAD_JSON if the string is not in the expected format.
 */
void
Detail_info::decode(const string& str) {
    std::regex pattern(
        R"(\s*\{\s*'id'\s*:\s*'([^']*)'\s*,\s*'name'\s*:\s*'([^']*)'\s*,\s*'count'\s*:\s*(\d+)\s*\}\s*)");
    std::smatch matches;
    if (std::regex_search(str, matches, pattern)) {
        string id = matches[1];
        string name = matches[2];
        std::size_t count = stoi(matches[3]);
        this->init(id, name, count);
    } else {
        throw BAD_JSON;
    }
}

/**
 * @brief Decodes a C-style string and extracts the detail information.
 * @param str A C-style string containing the detail information.
 */
void
Detail_info::decode(const char* str) {
    return this->decode(string(str));
}

/**
 * @brief Decodes a C-style string of specified size and extracts the detail information.
 * @param str A C-style string containing the detail information.
 * @param size The size of the string.
 */
void
Detail_info::decode(const char* str, std::size_t size) {
    return this->decode(string(str, size));
}

/**
 * @brief Prints the detail information to the standard output.
 */
void
Detail_info::print() {
    cout << "id: " << this->id << endl;
    cout << "name: " << this->name << endl;
    cout << "count: " << this->count << endl;
}

/**
 * @brief Constructs a Detail_info object with the provided values.
 * @param id The ID of the detail.
 * @param name The name of the detail.
 * @param count The count of the detail.
 */
Detail_info::Detail_info(const string& id, const string& name, std::size_t count) { this->init(id, name, count); }

/**
 * @brief Constructs a Detail_info object by decoding the provided string.
 * @param str A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
 */
Detail_info::Detail_info(const string& str) { this->decode(str); }

/**
 * @brief Default constructor for Detail_info. Initializes with empty values.
 */
Detail_info::Detail_info() { this->init("", "", 0); }
