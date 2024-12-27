#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

/**
 * @brief Base exception class for all game-related errors
 */
class GameException : public std::runtime_error {
  protected:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

/**
 * @brief Base class for game logic related exceptions
 */
class GameLogicException : public GameException {
  public:
    explicit GameLogicException(const std::string& message) : GameException(message) {}
};

/**
 * @brief Exception thrown when position is invalid for summoning
 */
class InvalidPositionException : public GameLogicException {
  public:
    InvalidPositionException() : GameLogicException("Invalid summon position - too far from summoner") {}
};

/**
 * @brief Exception thrown when troop type is invalid
 */
class InvalidTroopTypeException : public GameLogicException {
  public:
    InvalidTroopTypeException() : GameLogicException("Invalid troop type for summoning") {}
};

/**
 * @brief Exception thrown when a school is not found
 */
class SchoolNotFoundException : public GameLogicException {
  public:
    explicit SchoolNotFoundException(size_t id = 0)
        : GameLogicException("School not found" + (id ? ": ID " + std::to_string(id) : "")) {}
};

/**
 * @brief Exception thrown when an ability is not found
 */
class AbilityNotFoundException : public GameLogicException {
  public:
    explicit AbilityNotFoundException(size_t id = 0)
        : GameLogicException("Selected ability not found" + (id ? ": ID " + std::to_string(id) : "")) {}
};

/**
 * @brief Exception thrown when there are not enough movement points
 */
class NotEnoughMovementException : public GameLogicException {
  public:
    NotEnoughMovementException(size_t have, size_t need)
        : GameLogicException("Not enough movement points: have " + std::to_string(have) + ", need "
                             + std::to_string(need)) {}
};

/**
 * @brief Exception thrown when a target is out of attack range
 */
class OutOfRangeException : public GameLogicException {
  public:
    OutOfRangeException() : GameLogicException("Target is out of attack range") {}
};

/**
 * @brief Base class for resource-related exceptions
 */
class ResourceException : public GameException {
  protected:
    explicit ResourceException(const std::string& message) : GameException(message) {}
};

/**
 * @brief Exception thrown when no abilities are available for summoning
 */
class NoAvailableAbilitiesException : public ResourceException {
  public:
    NoAvailableAbilitiesException() : ResourceException("No abilities available for summoning") {}
};

/**
 * @brief Exception thrown when no abilities are available for upgrade
 */
class NoUpgradableAbilitiesException : public ResourceException {
  public:
    NoUpgradableAbilitiesException() : ResourceException("No abilities available for upgrade") {}
};

/**
 * @brief Base class for exceptions related to insufficient resources
 */
class NotEnoughResourceException : public ResourceException {
  protected:
    NotEnoughResourceException(const std::string& resource, size_t have, size_t need)
        : ResourceException("Not enough " + resource + ": have " + std::to_string(have) + ", need "
                            + std::to_string(need)) {}
};

/**
 * @brief Exception thrown when there is not enough energy
 */
class NotEnoughEnergyException : public NotEnoughResourceException {
  public:
    NotEnoughEnergyException(size_t have, size_t need) : NotEnoughResourceException("energy", have, need) {}
};

/**
 * @brief Exception thrown when there is not enough experience
 */
class NotEnoughExperienceException : public NotEnoughResourceException {
  public:
    NotEnoughExperienceException(size_t have, size_t need) : NotEnoughResourceException("experience", have, need) {}
};

/**
 * @brief Exception thrown when an entity is not found
 */
class EntityNotFoundException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Entity not found";
    }
};

/**
 * @brief Exception thrown when a position is out of bounds
 */
class OutOfBoundsException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Position is out of bounds";
    }
};

/**
 * @brief Exception thrown when a cell is not passable
 */
class CellNotPassableException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Cell is not passable";
    }
};

/**
 * @brief Exception thrown when a cell is already occupied
 */
class CellOccupiedException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Cell is already occupied";
    }
};

/**
 * @brief Exception thrown when an effect has expired
 */
class EffectExpiredException : public GameLogicException {
  public:
    EffectExpiredException() : GameLogicException("Effect time has expired") {}
};

/**
 * @brief Exception thrown when a troop has no effects available
 */
class NoEffectAvailableException : public GameLogicException {
  public:
    NoEffectAvailableException() : GameLogicException("This troop has no effects available") {}
};

/**
 * @brief Exception thrown when attempting to attack friendly units
 */
class FriendlyFireException : public GameLogicException {
  public:
    FriendlyFireException() : GameLogicException("Cannot attack friendly units") {}
};

#endif // EXCEPTIONS_HPP
