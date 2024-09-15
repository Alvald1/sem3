#ifndef LAB1_DETAIL_HPP
#define LAB1_DETAIL_HPP

#include <string>

using std::string;

class Detail_info {
  private:
    string id;
    string name;
    std::size_t count;

    void init(const string& id, const string& name, std::size_t count);

  public:
    string encode();

    string encode(const string& id, const string& name, std::size_t count);

    bool decode(const string& str);
    bool decode(const char* str);
    bool decode(const char* str, std::size_t size);

    void print();

    Detail_info(const string& id, const string& name, std::size_t count);

    Detail_info(const string& str);

    Detail_info();
};

#endif