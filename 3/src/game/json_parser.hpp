#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "schools/builders/director.hpp"
#include "schools/schools.hpp"
#include "ui/view.hpp"

class JsonParser {
  public:
    void
    parse_schools(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        rapidjson::IStreamWrapper isw(ifs);
        rapidjson::Document doc;

        if (doc.ParseStream(isw).HasParseError()) {
            throw std::runtime_error("JSON parse error");
        }

        if (!doc.HasMember("schools") || !doc["schools"].IsArray()) {
            throw std::runtime_error("Invalid JSON format: missing schools array");
        }

        auto& schools = Schools::getInstance();
        auto& view = View::getInstance();

        for (auto& schoolJSON : doc["schools"].GetArray()) {
            if (!schoolJSON.HasMember("name") || !schoolJSON["name"].IsString()) {
                throw std::runtime_error("School missing name field");
            }

            auto schoolName = schoolJSON["name"].GetString();
            SchoolBuilder sb(schoolName);

            if (!schoolJSON.HasMember("abilities") || !schoolJSON["abilities"].IsArray()) {
                throw std::runtime_error("School " + std::string(schoolName) + " missing abilities");
            }

            for (auto& abilityJSON : schoolJSON["abilities"].GetArray()) {
                // Validate required fields
                if (!abilityJSON.HasMember("name") || !abilityJSON.HasMember("level")
                    || !abilityJSON.HasMember("energy") || !abilityJSON.HasMember("experience")
                    || !abilityJSON.HasMember("creature") || !abilityJSON.HasMember("hp")) {
                    throw std::runtime_error("Invalid ability format in school " + std::string(schoolName));
                }

                // Extract fields
                auto abName = abilityJSON["name"].GetString();
                auto level = abilityJSON["level"].GetUint64();
                auto energy = abilityJSON["energy"].GetUint64();
                auto experience = abilityJSON["experience"].GetUint64();
                auto hp = abilityJSON["hp"].GetUint64();

                // Creature block
                auto& creatureJSON = abilityJSON["creature"];
                auto crName = creatureJSON["name"].GetString();
                auto speed = creatureJSON["speed"].GetUint64();
                auto damage = creatureJSON["damage"].GetUint64();
                auto range = creatureJSON["range"].GetUint64();
                auto type = creatureJSON["type"].GetUint64();
                auto initiative = creatureJSON["initiative"].GetUint64();

                Creature creature = Director::buildCreature(crName, speed, damage, range, type, initiative);

                // Get icon from creature
                std::string icon;
                if (creatureJSON.HasMember("icon")) {
                    icon = creatureJSON["icon"].GetString();
                }

                // Build ability
                Ability ability = Director::buildAbility(abName, creature, level, energy, experience, hp);

                // Store icon
                view.add_ability_icon(ability.get_id(), std::move(icon));

                sb.add_ability(ability);
            }
            schools.add_school(sb.build());
        }
    }
};

#endif // JSON_PARSER_HPP
