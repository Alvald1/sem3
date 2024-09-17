/**
 * @file detail.hpp
 * @brief Header file for the Detail_info class and associated functions.
 */

#ifndef LAB1_DETAIL_HPP
#define LAB1_DETAIL_HPP

#include <string>

/**
 * @brief Error codes for Detail_info.
 */
typedef enum _errors {
    BAD_JSON ///< Error thrown when decoding a malformed JSON string.
} errors;

using std::string;

/**
 * @class Detail_info
 * @brief Class representing detailed information with encoding and decoding capabilities.
 */
class Detail_info {
  private:
    string id;         ///< ID of the detail.
    string name;       ///< Name of the detail.
    std::size_t count; ///< Count of the detail.

    /**
     * @brief Initializes the detail with the given values.
     * @param id The ID of the detail.
     * @param name The name of the detail.
     * @param count The count of the detail.
     */
    void init(const string& id, const string& name, std::size_t count);

  public:
    /**
     * @brief Encodes the detail into a JSON-like string.
     * @return A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
     */
    string encode();

    /**
     * @brief Encodes the provided detail information into a JSON-like string.
     * @param id The ID of the detail.
     * @param name The name of the detail.
     * @param count The count of the detail.
     * @return A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
     */
    string encode(const string& id, const string& name, std::size_t count);

    /**
     * @brief Decodes a JSON-like string and extracts the detail information.
     * @param str A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
     * @throws errors::BAD_JSON if the string is not in the expected format.
     */
    void decode(const string& str);

    /**
     * @brief Decodes a C-style string and extracts the detail information.
     * @param str A C-style string containing the detail information.
     */
    void decode(const char* str);

    /**
     * @brief Decodes a C-style string of specified size and extracts the detail information.
     * @param str A C-style string containing the detail information.
     * @param size The size of the string.
     */
    void decode(const char* str, std::size_t size);

    /**
     * @brief Prints the detail information to the standard output.
     */
    void print();

    /**
     * @brief Constructs a Detail_info object with the provided values.
     * @param id The ID of the detail.
     * @param name The name of the detail.
     * @param count The count of the detail.
     */
    Detail_info(const string& id, const string& name, std::size_t count);

    /**
     * @brief Constructs a Detail_info object by decoding the provided string.
     * @param str A string in the format {'id':'<id>', 'name':'<name>', 'count':<count>}.
     */
    Detail_info(const string& str);

    /**
     * @brief Default constructor for Detail_info. Initializes with empty values.
     */
    Detail_info();
};

#endif // LAB1_DETAIL_HPP
