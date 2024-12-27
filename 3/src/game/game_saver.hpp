#ifndef GAME_SAVER_HPP
#define GAME_SAVER_HPP

#include <fstream>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <string>

#include "../managers/entity_manager.hpp"
#include "../managers/map_manager.hpp"
#include "../map/cell/builders/cell_director.hpp"
#include "../queue/entity/builder/entity_director.hpp"
#include "../queue/entity/summoner.hpp"
#include "../queue/entity/troop/amoral_troop.hpp"
#include "../queue/entity/troop/moral_troop.hpp"

class GameSaver {
  private:
    static GameSaver* instance_;
    GameSaver() = default;

    void serialize_entity(const Entity* entity, rapidjson::Value& value,
                          rapidjson::Document::AllocatorType& allocator) const;
    std::unique_ptr<Entity> deserialize_entity(const rapidjson::Value& value) const;

    void serialize_cell(const std::shared_ptr<Cell>& cell, rapidjson::Value& value,
                        rapidjson::Document::AllocatorType& allocator) const;
    std::shared_ptr<Cell> deserialize_cell(const rapidjson::Value& value, Position pos) const;

  public:
    static GameSaver&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new GameSaver();
        }
        return *instance_;
    }

    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    GameSaver(const GameSaver&) = delete;
    GameSaver& operator=(const GameSaver&) = delete;

    void save_game(const std::string& filename) const;
    void load_game(const std::string& filename);
};

#endif // GAME_SAVER_HPP
