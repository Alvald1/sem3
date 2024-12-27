#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

// Base game exception
class GameException : public std::runtime_error {
  protected:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

// Logic exceptions
class GameLogicException : public GameException {
  public: // Change from protected to public
    explicit GameLogicException(const std::string& message) : GameException(message) {}
};

class InvalidPositionException : public GameLogicException {
  public:
    InvalidPositionException() : GameLogicException("Invalid summon position - too far from summoner") {}
};

class InvalidTroopTypeException : public GameLogicException {
  public:
    InvalidTroopTypeException() : GameLogicException("Invalid troop type for summoning") {}
};

class SchoolNotFoundException : public GameLogicException {
  public:
    explicit SchoolNotFoundException(size_t id = 0)
        : GameLogicException("School not found" + (id ? ": ID " + std::to_string(id) : "")) {}
};

class AbilityNotFoundException : public GameLogicException {
  public:
    explicit AbilityNotFoundException(size_t id = 0)
        : GameLogicException("Selected ability not found" + (id ? ": ID " + std::to_string(id) : "")) {}
};

class NotEnoughMovementException : public GameLogicException {
  public:
    NotEnoughMovementException(size_t have, size_t need)
        : GameLogicException("Not enough movement points: have " + std::to_string(have) + ", need "
                             + std::to_string(need)) {}
};

class OutOfRangeException : public GameLogicException {
  public:
    OutOfRangeException() : GameLogicException("Target is out of attack range") {}
};

// Resource exceptions
class ResourceException : public GameException {
  protected:
    explicit ResourceException(const std::string& message) : GameException(message) {}
};

class NoAvailableAbilitiesException : public ResourceException {
  public:
    NoAvailableAbilitiesException() : ResourceException("No abilities available for summoning") {}
};

class NoUpgradableAbilitiesException : public ResourceException {
  public:
    NoUpgradableAbilitiesException() : ResourceException("No abilities available for upgrade") {}
};

class NotEnoughResourceException : public ResourceException {
  protected:
    NotEnoughResourceException(const std::string& resource, size_t have, size_t need)
        : ResourceException("Not enough " + resource + ": have " + std::to_string(have) + ", need "
                            + std::to_string(need)) {}
};

class NotEnoughEnergyException : public NotEnoughResourceException {
  public:
    NotEnoughEnergyException(size_t have, size_t need) : NotEnoughResourceException("energy", have, need) {}
};

class NotEnoughExperienceException : public NotEnoughResourceException {
  public:
    NotEnoughExperienceException(size_t have, size_t need) : NotEnoughResourceException("experience", have, need) {}
};

class EntityNotFoundException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Entity not found";
    }
};

class OutOfBoundsException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Position is out of bounds";
    }
};

class CellNotPassableException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Cell is not passable";
    }
};

class CellOccupiedException : public std::exception {
  public:
    [[nodiscard]] const char*
    what() const noexcept override {
        return "Cell is already occupied";
    }
};

class EffectExpiredException : public GameLogicException {
  public:
    EffectExpiredException() : GameLogicException("Effect time has expired") {}
};

class NoEffectAvailableException : public GameLogicException {
  public:
    NoEffectAvailableException() : GameLogicException("This troop has no effects available") {}
};

class FriendlyFireException : public GameLogicException {
  public:
    FriendlyFireException() : GameLogicException("Cannot attack friendly units") {}
};

#endif // EXCEPTIONS_HPP
