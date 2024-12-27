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

/**
 * @class GameSaver
 * @brief Singleton class responsible for saving and loading game state.
 * 
 * This class handles serialization and deserialization of the entire game state,
 * including entities, map, and game progress.
 */
class GameSaver {
  private:
    static GameSaver* instance_; ///< Singleton instance
    GameSaver() = default;

    /**
     * @brief Serializes an entity to JSON format
     * @param entity Entity to serialize
     * @param value JSON value to store serialized data
     * @param allocator JSON document allocator
     */
    void serialize_entity(const Entity* entity, rapidjson::Value& value,
                          rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief Deserializes an entity from JSON format
     * @param value JSON value containing entity data
     * @return Unique pointer to the deserialized entity
     */
    std::unique_ptr<Entity> deserialize_entity(const rapidjson::Value& value) const;

    /**
     * @brief Serializes a cell to JSON format
     * @param cell Cell to serialize
     * @param value JSON value to store serialized data
     * @param allocator JSON document allocator
     */
    void serialize_cell(const std::shared_ptr<Cell>& cell, rapidjson::Value& value,
                        rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief Deserializes a cell from JSON format
     * @param value JSON value containing cell data
     * @param pos Position of the cell
     * @return Shared pointer to the deserialized cell
     */
    std::shared_ptr<Cell> deserialize_cell(const rapidjson::Value& value, Position pos) const;

  public:
    /**
     * @brief Gets the singleton instance
     * @return Reference to the GameSaver instance
     */
    static GameSaver& getInstance();

    /**
     * @brief Destroys the singleton instance
     */
    static void destroyInstance();

    // Delete copy constructor and assignment operator
    GameSaver(const GameSaver&) = delete;
    GameSaver& operator=(const GameSaver&) = delete;

    /**
     * @brief Saves the current game state to a file
     * @param filename Path to save file
     */
    void save_game(const std::string& filename) const;

    /**
     * @brief Loads a game state from a file
     * @param filename Path to save file
     * @throws std::runtime_error If loading fails
     */
    void load_game(const std::string& filename);
};

#endif // GAME_SAVER_HPP
