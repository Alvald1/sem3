#include "detail.hpp"

#include <format>
#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::string;

void
Detail_info::init(const string& id, const string& name, std::size_t count) {
    this->id = id;
    this->name = name;
    this->count = count;
}

string
Detail_info::encode() {
    return std::format("{{'id':'{}','name':'{}','count':{}}}", this->id, this->name, this->count);
}

string
Detail_info::encode(const string& id, const string& name, std::size_t count) {
    this->init(id, name, count);
    return this->encode();
}

bool
Detail_info::decode(const string& str) {
    std::regex pattern(R"(\{'id':'([^']*)','name':'([^']*)','count':(\d+)\})");
    std::smatch matches;
    if (std::regex_search(str, matches, pattern)) {
        string id = matches[1];
        string name = matches[2];
        std::size_t count = stoi(matches[3]);

        this->init(id, name, count);
    } else {
        return 1;
    }
    return 0;
}

void
Detail_info::print() {
    cout << "id: " << this->id << endl;
    cout << "name: " << this->name << endl;
    cout << "count: " << this->count << endl;
}

Detail_info::Detail_info(const string& id, const string& name, std::size_t count) { this->init(id, name, count); }

Detail_info::Detail_info(const string& str) { this->decode(str); }

Detail_info::Detail_info() { this->init("", "", 0); }
