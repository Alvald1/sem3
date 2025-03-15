# Fantasy Strategy Game

## Overview

This is a turn-based tactical strategy game implemented in C++ using the ncurses library for the console interface. The game features summoners who can call forth troops, engage in tactical combat, and develop their abilities through a comprehensive school system.

## Game Description

Players control summoners on a grid-based battlefield, commanding troops and managing resources in a turn-based combat system. The game features:

- Grid-based movement and positioning
- Resource management (energy and experience)
- Unit summoning and combat
- Special abilities and effects
- Tactical decision-making
- School-based progression system

## Object-Oriented Design

The game extensively leverages object-oriented programming principles:

### Class Hierarchy

- **Entity System**
  - Abstract `Entity` base class
  - Specialized into `Summoner` and `BaseTroop` classes
  - Further specialization with `MoralTroop` and `AmoralTroop`

- **Cell System**
  - Base `Cell` class for map tiles
  - Effect cells (`EffectCellHP`, `EffectCellDamage`, etc.) providing special abilities

- **Position System**
  - `Position` class abstracting 2D coordinates and providing operations
  - Distance calculations and position manipulations

### Design Patterns

The codebase implements several design patterns:

1. **Singleton Pattern**
   - Applied to manager classes (`MapManager`, `EntityManager`, etc.)
   - Ensures single instance control and global access

2. **Builder Pattern**
   - Used for construction of complex objects
   - Implementations for troops, cells, abilities, etc.
   - Examples: `MoralTroopBuilder`, `CellBuilder`

3. **Factory Method Pattern**
   - `EntityDirector` and `CellDirector` for entity/cell creation
   - Encapsulates creation logic

4. **Command Pattern**
   - Action handling system for processing player commands

5. **Strategy Pattern**
   - Different troop types implement different behaviors

### Exception Handling

Robust exception hierarchy for game logic errors:
- `GameException` as the base class
- Specialized exceptions like `InvalidPositionException`, `NotEnoughEnergyException`, etc.
- Properly structured catch blocks for error handling

## Game Features

### Turn-Based Combat
- Initiative-based queue system
- Tactical positioning and movement
- Range-based attacks and effects

### Resource System
- Energy for summoning troops and using abilities
- Experience for upgrading schools
- Moral points affecting troop performance

### School System
- Different schools with unique abilities
- Ability upgrades through experience
- Specialized troops for different tactics

### Effects System
- Cells can have special effects (damage, speed, range, health)
- Effects apply to entities occupying cells
- Multithreaded effect processing for performance

### Save/Load System
- Game state serialization using JSON
- Ability to save and resume games

## Technical Implementation

The game leverages several technical aspects:

- **Multithreading** for processing cell effects
- **ncurses** library for terminal-based UI
- **JSON** configuration for game data
- **RAII** principle for resource management
- **Smart pointers** for memory management

## Controls

- **Arrow Keys**: Navigate menus and scroll map view
- **1-4**: Select actions
- **WASD**: Navigate the cursor on the grid
- **Enter**: Confirm selections
- **Escape**: Cancel or return
- **P**: Save the game
- **Q**: Quit the game

## Getting Started

1. Build the project using CMake
2. Run the executable
3. Select game options and start playing
4. Use the command keys to control your summoner and troops

## OOP Principles in Action

The game demonstrates four core OOP principles:

1. **Encapsulation**: Private data with accessor methods, protecting internal state
2. **Inheritance**: Specialized classes inheriting from base classes
3. **Polymorphism**: Virtual functions allowing for different behaviors
4. **Abstraction**: High-level interfaces hiding implementation details

## Testing

The project includes comprehensive unit tests:
- Tests for map management
- Entity behavior tests
- Game logic validation
- Exception handling tests

This project represents a comprehensive application of object-oriented design principles to create a complex, interactive console-based game with rich gameplay features.