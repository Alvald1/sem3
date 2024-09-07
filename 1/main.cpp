#include <format>
#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Detail_info {
  private:
    string id;
    string name;
    size_t count;

    void
    init(const string& id, const string& name, size_t count) {
        this->id = id;
        this->name = name;
        this->count = count;
    }

  public:
    string
    encode() {
        return std::format("{{'id':'{}','name':'{}','count':{}}}", this->id, this->name, std::to_string(this->count));
    }

    string
    encode(const string& id, const string& name, size_t count) {
        this->init(id, name, count);
        return this->encode();
    }

    bool
    decode(const string& str) {
        std::regex pattern(R"(\{'id':'([^']*)','name':'([^']*)','count':(\d+)\})");
        std::smatch matches;
        if (std::regex_search(str, matches, pattern)) {
            string id = matches[1];
            string name = matches[2];
            size_t count = stoi(matches[3]);

            this->init(id, name, count);
        } else {
            return 1;
        }
        return 0;
    }

    void
    print() {
        cout << "id: " << this->id << endl;
        cout << "name: " << this->name << endl;
        cout << "count: " << this->count << endl;
    }

    Detail_info(const string& id, const string& name, size_t count) { this->init(id, name, count); }

    Detail_info(const string& str) { this->decode(str); }

    Detail_info() { this->init("", "", 0); }
};

int
main() {
    Detail_info a("a1", "a2", 1);
    a.print();
    cout << a.encode() << endl;
    Detail_info b("{'id':'b1','name':'b2','count':3}");
    b.print();
    return 0;
}