#ifndef LAB1_DETAIL_HPP
#define LAB1_DETAIL_HPP

#include <string>

typedef enum _errors { BAD_JSON } errors;

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

    void decode(const string& str);
    void decode(const char* str);
    void decode(const char* str, std::size_t size);

    void print();

    Detail_info(const string& id, const string& name, std::size_t count);

    Detail_info(const string& str);

    Detail_info();
};

#endif