# Signal Processing Library

## Overview

This project implements a library for working with digital signals, including basic signal processing capabilities and complex signal composition. The library provides classes for creating, manipulating, and visualizing digital signals.

## Components

The project consists of three main components:

### Signal

The `Signal` class represents a basic digital signal with two parameters:
- **level** (0 or 1): Represents the signal's state
- **duration**: Represents the length of the signal

Key features:
- Signal creation from binary strings
- Signal inversion
- Manipulation of signal duration
- Signal visualization

### Complex Signal

The `Complex_Signal` class represents a sequence of signals with different levels. It provides:
- Construction from binary strings
- Signal composition through concatenation
- Signal insertion at specific positions 
- Signal inversion
- Signal multiplication
- Signal visualization

### Allocator

The `Allocator` class provides memory management for signal storage, featuring:
- Dynamic memory allocation
- Memory reallocation when needed
- Support for copy and move operations

## Building the Project

The project uses CMake for building. To build the project:

```bash
# Create a build directory
mkdir -p build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .
```

## Special Build Targets

The project includes several specialized build targets:

- **debug**: Builds with debugging symbols
  ```bash
  cmake --build . --target debug
  ```

- **asan**: Builds with AddressSanitizer for memory error detection
  ```bash
  cmake --build . --target asan
  ```

- **msan**: Builds with MemorySanitizer for uninitialized memory detection
  ```bash
  cmake --build . --target msan
  ```

- **valgrind**: Runs the program with Valgrind for memory leak detection
  ```bash
  cmake --build . --target valgrind
  ```

- **static**: Runs static analysis on the code
  ```bash
  cmake --build . --target static
  ```

- **cov**: Runs tests and generates coverage reports
  ```bash
  cmake --build . --target cov
  ```

## Testing

The project includes unit tests using Google Test. To run the tests:

```bash
cmake --build . --target test_target
./lab2_test
```

## Documentation

The project uses Doxygen for documentation. To generate the documentation:

```bash
cmake --build . --target doc
```

The documentation will be generated in the `build/html` directory.
