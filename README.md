# Object-Oriented Programming Projects

This repository contains three C++ projects implementing different applications using object-oriented programming principles.

## Projects Overview

### [Detail Info Library](./1/)

A library for handling detail information with JSON-like encoding and decoding capabilities.

**Key Features:**
- Encode/decode detail information to/from JSON-like strings
- Command-line interface for interactive use
- Comprehensive unit testing with Google Test

[View Detail Info Library README](./1/README.md)

### [Signal Processing Library](./2/)

A library for working with digital signals, including basic signal processing capabilities and complex signal composition.

**Key Features:**
- Signal creation and manipulation
- Complex signal composition
- Signal visualization
- Custom memory allocation

[View Signal Processing Library README](./2/README.md)

### [Fantasy Strategy Game](./3/)

A turn-based tactical strategy game implemented in C++ using the ncurses library for the console interface.

**Key Features:**
- Grid-based movement and positioning
- Resource management (energy and experience)
- Unit summoning and combat
- School-based progression system

[View Fantasy Strategy Game README](./3/README.md)

## Object-Oriented Programming Principles

These projects demonstrate core OOP principles across different applications:

1. **Encapsulation**
   - Private data with accessor methods
   - Information hiding and data protection
   - Well-defined interfaces

2. **Inheritance**
   - Class hierarchies for specialized behavior
   - Base and derived class relationships
   - Code reuse through inheritance

3. **Polymorphism**
   - Virtual functions allowing for different behaviors
   - Runtime type determination
   - Interface-based programming

4. **Abstraction**
   - High-level interfaces hiding implementation details
   - Abstract base classes and pure virtual functions
   - Separation of concerns

## Design Patterns Used

The projects implement various design patterns including:
- Singleton Pattern
- Builder Pattern
- Factory Method Pattern
- Command Pattern
- Strategy Pattern

## Common Build Instructions

All projects use CMake for building. General build steps:

```bash
# Navigate to project directory
cd ./[project-number]

# Create build directory
mkdir -p build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .
```

## Common Build Targets

All projects include several specialized build targets:

- **debug**: Builds with debugging symbols
- **asan**: Builds with AddressSanitizer for memory error detection
- **msan**: Builds with MemorySanitizer for uninitialized memory detection
- **valgrind**: Runs the program with Valgrind for memory leak detection
- **static**: Runs static analysis on the code
- **test**: Runs unit tests
- **cov**: Runs tests and generates coverage reports

## Testing

All projects include comprehensive unit testing using Google Test framework:

```bash
# Navigate to project build directory
cd ./[project-number]/build

# Run tests
cmake --build . --target test
```

## Project-Specific Instructions

For detailed instructions on each project, see their individual README files:

- [Detail Info Library Instructions](./1/README.md)
- [Signal Processing Library Instructions](./2/README.md)
- [Fantasy Strategy Game Instructions](./3/README.md)
