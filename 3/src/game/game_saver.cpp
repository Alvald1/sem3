#include "game_saver.hpp"
#include "schools/builders/director.hpp"

GameSaver* GameSaver::instance_ = nullptr;

void
GameSaver::serialize_entity(const Entity* entity, rapidjson::Value& value,
                            rapidjson::Document::AllocatorType& allocator) const {
    value.SetObject();
    value.AddMember("id", rapidjson::Value(entity->get_id()), allocator);
    value.AddMember("name", rapidjson::Value(entity->get_name().c_str(), allocator), allocator);
    value.AddMember("hp", rapidjson::Value(entity->get_hp()), allocator);
    value.AddMember("initiative", rapidjson::Value(entity->get_initiative()), allocator);

    if (auto summoner = dynamic_cast<const Summoner*>(entity)) {
        value.AddMember("type", rapidjson::Value("summoner", allocator), allocator);
        value.AddMember("energy", rapidjson::Value(summoner->get_energy()), allocator);
        value.AddMember("experience", rapidjson::Value(summoner->get_experience()), allocator);
        value.AddMember("accum_index", rapidjson::Value(summoner->get_accum_index()), allocator);

        // Serialize levels map
        rapidjson::Value levels(rapidjson::kObjectType);
        for (const auto& [id, level] : summoner->get_levels()) {
            levels.AddMember(rapidjson::Value(std::to_string(id).c_str(), allocator), rapidjson::Value(level),
                             allocator);
        }
        value.AddMember("levels", levels, allocator);

        // Serialize ownerships array
        rapidjson::Value ownerships(rapidjson::kArrayType);
        for (const auto& id : summoner->get_ownerships()) {
            ownerships.PushBack(rapidjson::Value(id), allocator);
        }
        value.AddMember("ownerships", ownerships, allocator);
    } else if (auto troop = dynamic_cast<const BaseTroop*>(entity)) {
        // Сохраняем общие характеристики войск
        value.AddMember("damage", rapidjson::Value(troop->get_damage()), allocator);
        value.AddMember("speed", rapidjson::Value(troop->get_speed()), allocator);
        value.AddMember("range", rapidjson::Value(troop->get_range()), allocator);
        value.AddMember("type_id", rapidjson::Value(troop->get_type()), allocator);
        value.AddMember("experience_troop", rapidjson::Value(troop->get_experience()), allocator);

        if (auto moral_troop = dynamic_cast<const MoralTroop*>(troop)) {
            value.AddMember("type", rapidjson::Value("moral_troop", allocator), allocator);
            value.AddMember("moral", rapidjson::Value(moral_troop->get_moral()), allocator);
            value.AddMember("id_summoner", rapidjson::Value(moral_troop->get_id_summoner()), allocator);
        } else if (auto amoral_troop = dynamic_cast<const AmoralTroop*>(troop)) {
            value.AddMember("type", rapidjson::Value("amoral_troop", allocator), allocator);
            value.AddMember("id_summoner", rapidjson::Value(amoral_troop->get_id_summoner()), allocator);
        }
    }
}

void
GameSaver::serialize_cell(const std::shared_ptr<Cell>& cell, rapidjson::Value& value,
                          rapidjson::Document::AllocatorType& allocator) const {
    value.SetObject();
    value.AddMember("passable", rapidjson::Value(cell->get_passability()), allocator);
    value.AddMember("id_entity", rapidjson::Value(cell->get_id_entity()), allocator);
    value.AddMember("busy", rapidjson::Value(cell->get_busy()), allocator);

    if (auto speed_cell = std::dynamic_pointer_cast<EffectCellSpeed>(cell)) {
        value.AddMember("type", rapidjson::Value("speed", allocator), allocator);
        value.AddMember("effect_value", rapidjson::Value(speed_cell->give_effect()), allocator);
        value.AddMember("duration", rapidjson::Value(speed_cell->get_time()), allocator);
    } else if (auto range_cell = std::dynamic_pointer_cast<EffectCellRange>(cell)) {
        value.AddMember("type", rapidjson::Value("range", allocator), allocator);
        value.AddMember("effect_value", rapidjson::Value(range_cell->give_effect()), allocator);
        value.AddMember("duration", rapidjson::Value(range_cell->get_time()), allocator);
    } else if (auto hp_cell = std::dynamic_pointer_cast<EffectCellHP>(cell)) {
        value.AddMember("type", rapidjson::Value("hp", allocator), allocator);
        value.AddMember("effect_value", rapidjson::Value(hp_cell->give_effect()), allocator);
        value.AddMember("duration", rapidjson::Value(hp_cell->get_time()), allocator);
    } else if (auto damage_cell = std::dynamic_pointer_cast<EffectCellDamage>(cell)) {
        value.AddMember("type", rapidjson::Value("damage", allocator), allocator);
        value.AddMember("effect_value", rapidjson::Value(damage_cell->give_effect()), allocator);
        value.AddMember("duration", rapidjson::Value(damage_cell->get_time()), allocator);
    } else {
        value.AddMember("type", rapidjson::Value("basic", allocator), allocator);
    }
}

void
GameSaver::save_game(const std::string& filename) const {
    rapidjson::Document doc;
    doc.SetObject();
    auto& allocator = doc.GetAllocator();

    auto& map_manager = MapManager::getInstance();
    auto& entity_manager = EntityManager::getInstance();

    // Save map size
    rapidjson::Value size_array(rapidjson::kArrayType);
    size_array.PushBack(rapidjson::Value(map_manager.get_size().first), allocator);
    size_array.PushBack(rapidjson::Value(map_manager.get_size().second), allocator);
    doc.AddMember("map_size", size_array, allocator);

    // Save cells
    rapidjson::Value cells_array(rapidjson::kArrayType);
    auto& matrix = map_manager.get_matrix();
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
            rapidjson::Value cell_value;
            serialize_cell(matrix(i, j), cell_value, allocator); // Changed from matrix(i, j) to matrix(i, j)
            cells_array.PushBack(cell_value, allocator);
        }
    }
    doc.AddMember("cells", cells_array, allocator);

    // Save entities
    rapidjson::Value entities_array(rapidjson::kArrayType);
    auto entities = entity_manager.get_queue_entities();

    // Sort entities by ID
    std::vector<Entity*> sorted_entities;
    for (auto* entity : entities) {
        if (entity) {
            sorted_entities.push_back(entity);
        }
    }
    std::sort(sorted_entities.begin(), sorted_entities.end(),
              [](const Entity* a, const Entity* b) { return a->get_id() < b->get_id(); });

    // Serialize sorted entities
    for (auto* entity : sorted_entities) {
        rapidjson::Value entity_value;
        serialize_entity(entity, entity_value, allocator);
        entities_array.PushBack(entity_value, allocator);
    }
    doc.AddMember("entities", entities_array, allocator);

    // Save positions
    rapidjson::Value positions(rapidjson::kObjectType);
    const auto& entity_list = map_manager.get_entities().get_id_to_cell();
    for (const auto& [id, cell] : entity_list) {
        rapidjson::Value pos_array(rapidjson::kArrayType);
        const auto& pos = cell->get_position();
        pos_array.PushBack(rapidjson::Value(pos.get_y()), allocator);
        pos_array.PushBack(rapidjson::Value(pos.get_x()), allocator);
        positions.AddMember(rapidjson::Value(std::to_string(id).c_str(), allocator), pos_array, allocator);
    }
    doc.AddMember("positions", positions, allocator);

    // Save current entity id
    if (auto current_entity = entity_manager.get_current_entity()) {
        doc.AddMember("current_entity_id", rapidjson::Value(current_entity->get_id()), allocator);
    }

    // Write to file
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void
GameSaver::load_game(const std::string& filename) {
    std::ifstream ifs(filename);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    auto& map_manager = MapManager::getInstance();
    auto& entity_manager = EntityManager::getInstance();

    // Clear current game state
    entity_manager.clear();

    // Load map
    auto size = std::make_pair(doc["map_size"][0].GetUint64(), doc["map_size"][1].GetUint64());
    map_manager.make_map(size);

    // Load cells
    auto& matrix = map_manager.get_matrix();
    size_t idx = 0;
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
            matrix(i, j) =
                deserialize_cell(doc["cells"][idx++], Position(i, j)); // Changed from matrix(i, j) to matrix(i, j)
        }
    }

    // Sort entities by ID before loading
    std::vector<const rapidjson::Value*> summoners;
    std::vector<const rapidjson::Value*> troops;

    for (const auto& entity_value : doc["entities"].GetArray()) {
        if (entity_value["type"].GetString() == std::string("summoner")) {
            summoners.push_back(&entity_value);
        } else {
            troops.push_back(&entity_value);
        }
    }

    // Sort both vectors by ID
    auto sort_by_id = [](const rapidjson::Value* a, const rapidjson::Value* b) {
        return a->FindMember("id")->value.GetUint64() < b->FindMember("id")->value.GetUint64();
    };

    std::sort(summoners.begin(), summoners.end(), sort_by_id);
    std::sort(troops.begin(), troops.end(), sort_by_id);

    // Load summoners first
    for (const auto* value : summoners) {
        if (auto entity = deserialize_entity(*value)) {
            entity_manager.add_entity(std::move(entity));
        }
    }

    // Then load troops
    for (const auto* value : troops) {
        if (auto entity = deserialize_entity(*value)) {
            entity_manager.add_entity(std::move(entity));
        }
    }

    // Load positions
    for (auto it = doc["positions"].MemberBegin(); it != doc["positions"].MemberEnd(); ++it) {
        size_t id = std::stoull(it->name.GetString());
        const auto& pos_array = it->value.GetArray();
        Position pos{static_cast<int>(pos_array[0].GetUint64()), static_cast<int>(pos_array[1].GetUint64())};
        map_manager.add_entity(id, pos); // Using existing public method
    }

    // Get current entity id
    if (doc.HasMember("current_entity_id")) {
        size_t target_id = doc["current_entity_id"].GetUint64();

        // Rotate queue until we find the target entity
        while (auto current = entity_manager.get_current_entity()) {
            if (current->get_id() == target_id) {
                break;
            }
            entity_manager.next_turn();
        }
    }
}

std::shared_ptr<Cell>
GameSaver::deserialize_cell(const rapidjson::Value& value, Position pos) const {
    bool passability = value["passable"].GetBool();

    std::string type = value["type"].GetString();
    if (type != "basic") {

        if (type == "speed") {
            return std::make_shared<Cell>(CellDirector::createBasicCell(pos, passability));
        } else if (type == "range") {
            return std::make_shared<Cell>(CellDirector::createBasicCell(pos, passability));
        } else if (type == "hp") {
            return std::make_shared<Cell>(CellDirector::createBasicCell(pos, passability));
        } else if (type == "damage") {
            return std::make_shared<Cell>(CellDirector::createBasicCell(pos, passability));
        }
    }

    return std::make_shared<Cell>(CellDirector::createBasicCell(pos, passability));
}

std::unique_ptr<Entity>
GameSaver::deserialize_entity(const rapidjson::Value& value) const {
    std::string type = value["type"].GetString();
    std::string name = value["name"].GetString();
    size_t hp = value["hp"].GetUint64();
    size_t initiative = value["initiative"].GetUint64();

    if (type == "summoner") {
        // Для призывателя создаем существо и умение с сохраненными параметрами
        auto creature = Director::buildCreature(name, 1, 1, 1, 0, initiative);
        auto ability = Director::buildAbility(name, creature, 1, 1, 1, hp);

        size_t energy = value["energy"].GetUint64();
        size_t accum_index = value["accum_index"].GetUint64();
        auto summoner = std::make_unique<Summoner>(EntityDirector::createSummoner(ability, energy, accum_index));

        // Restore summoner specific state
        summoner->add_experience(value["experience"].GetUint64());
        // Add energy restoration

        // Restore levels
        const auto& levels = value["levels"].GetObject();
        for (auto it = levels.MemberBegin(); it != levels.MemberEnd(); ++it) {
            size_t school_id = std::stoull(it->name.GetString());
            size_t level = it->value.GetUint64();
            summoner->get_levels_mutable()[school_id] = level; // Use the new non-const getter
        }

        // Restore ownerships
        for (const auto& id : value["ownerships"].GetArray()) {
            summoner->add_ownership(id.GetUint64());
        }

        return summoner;
    } else if (type == "moral_troop" || type == "amoral_troop") {
        // Для войск создаем базовое умение
        auto creature = Director::buildCreature(name, value["damage"].GetUint64(), value["speed"].GetUint64(),
                                                value["range"].GetUint64(), value["type_id"].GetUint64(), initiative);

        auto ability = Director::buildAbility(name, creature, 1, 0, value["experience_troop"].GetUint64(), hp);

        if (type == "moral_troop") {
            return std::make_unique<MoralTroop>(
                EntityDirector::createMoralTroop(ability, value["moral"].GetInt(), value["id_summoner"].GetUint64()));
        } else {
            return std::make_unique<AmoralTroop>(
                EntityDirector::createAmoralTroop(ability, value["id_summoner"].GetUint64()));
        }
    }

    return nullptr;
}
