# Detail Info Library

This project implements a C++ library for handling detail information with JSON-like encoding and decoding capabilities.

## Overview

The `Detail_info` class provides functionality to store, encode, and decode information about parts/details, including:
- ID (string)
- Name (string)
- Count (numeric)

## Project Structure

```
.
├── detail.cpp       # Implementation of Detail_info class
├── detail.hpp       # Header defining Detail_info class
├── main.cpp         # CLI application for using Detail_info
├── main.hpp         # Header for utility functions
├── CMakeLists.txt   # Main build configuration
└── test/            # Test directory
    ├── unit_tests.cpp  # Google Test unit tests
    └── CMakeLists.txt  # Test build configuration
```

## Features

- Encode detail information to JSON-like string format
- Decode JSON-like strings to extract detail information
- Command-line interface for interactive use
- Comprehensive unit testing with Google Test
- Code coverage analysis

## Build Instructions

This project uses CMake for building. First, create a build directory:

```bash
mkdir build && cd build
```

Then configure and build the project:

```bash
cmake ..
make
```

## Available Build Targets

- `lab1` - Main application binary
- `debug` - Debug build with debugging symbols
- `asan` - Build with AddressSanitizer for memory error detection
- `msan` - Build with MemorySanitizer
- `valgrind` - Runs the application with Valgrind for memory leak detection
- `static` - Performs static code analysis
- `test_target` - Runs unit tests
- `cov` - Generates code coverage reports

## Testing

Run the tests with:

```bash
cd build
make test
```

To generate a code coverage report:

```bash
cd build
make cov
```

The coverage report will be available in HTML format in the `report_coverage` directory.

## Usage

The main application provides a command-line interface with two primary functions:

1. **Encode**: Convert detail information (ID, name, count) to a JSON-like string
   - Command: `e`
   
2. **Decode**: Parse a JSON-like string to extract detail information
   - Command: `d`

### Example

```
(d) - decode
(e) - encode
e
id: 001
name: Bolt
count: 50
{'id':'001','name':'Bolt','count':50}
```

## JSON Format

The JSON-like format used for encoding/decoding is:

```
{'id':'<id>','name':'<name>','count':<count>}
```

## Requirements

- C++23 compatible compiler (clang++ recommended)
- CMake 3.10+
- Google Test framework
