#include <fstream>
#include <gtest/gtest.h>
#include <sstream>
#include "../src/game/json_parser.hpp"

class JsonParserTest : public ::testing::Test {
  protected:
    JsonParser parser;

    void
    SetUp() override {
        // Clear singleton instances before each test
        Schools::getInstance().destroyInstance();
    }

    void
    TearDown() override {
        // Clear singleton instances after each test
        View::getInstance().cleanup();

        // Cleanup test files
        std::remove("test_schools.json");
        std::remove("invalid_schools.json");
    }

    void
    createTestJsonFile(const std::string& content, const std::string& filename) {
        std::ofstream file(filename);
        file << content;
        file.close();
    }
};

TEST_F(JsonParserTest, ValidSchoolParsing) {
    const std::string validJson = R"({
        "schools": [{
            "name": "TestSchool",
            "abilities": [{
                "name": "TestAbility",
                "level": 1,
                "energy": 10,
                "experience": 100,
                "hp": 50,
                "creature": {
                    "name": "TestCreature",
                    "speed": 5,
                    "damage": 10,
                    "range": 2,
                    "type": 1,
                    "initiative": 3,
                    "icon": "test_icon"
                }
            }]
        }]
    })";

    createTestJsonFile(validJson, "test_schools.json");

    ASSERT_NO_THROW(parser.parse_schools("test_schools.json"));

    auto& schools = Schools::getInstance();
    ASSERT_EQ(schools.get_schools().size(), 1);
    ASSERT_EQ(schools.get_schools()[0].get_name(), "TestSchool");
}

TEST_F(JsonParserTest, MissingSchoolsArray) {
    const std::string invalidJson = R"({
        "wrong_key": []
    })";

    createTestJsonFile(invalidJson, "invalid_schools.json");

    ASSERT_THROW(parser.parse_schools("invalid_schools.json"), std::runtime_error);
}

TEST_F(JsonParserTest, MissingAbilities) {
    const std::string invalidJson = R"({
        "schools": [{
            "name": "TestSchool"
        }]
    })";

    createTestJsonFile(invalidJson, "invalid_schools.json");

    ASSERT_THROW(parser.parse_schools("invalid_schools.json"), std::runtime_error);
}

TEST_F(JsonParserTest, InvalidAbilityFormat) {
    const std::string invalidJson = R"({
        "schools": [{
            "name": "TestSchool",
            "abilities": [{
                "name": "TestAbility"
            }]
        }]
    })";

    createTestJsonFile(invalidJson, "invalid_schools.json");

    ASSERT_THROW(parser.parse_schools("invalid_schools.json"), std::runtime_error);
}

TEST_F(JsonParserTest, NonexistentFile) { ASSERT_THROW(parser.parse_schools("nonexistent.json"), std::runtime_error); }

TEST_F(JsonParserTest, EmptySchools) {
    const std::string validJson = R"({
        "schools": []
    })";

    createTestJsonFile(validJson, "test_schools.json");

    ASSERT_NO_THROW(parser.parse_schools("test_schools.json"));
    auto& schools = Schools::getInstance();
    ASSERT_EQ(schools.get_schools().size(), 0);
}
