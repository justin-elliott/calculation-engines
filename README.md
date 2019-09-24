# Calculation Engines

A program that performs calculations on a series of integers.

## Building the Calculation Engine

```
make        -- Build the calculation engine.
make all    -- Synonymous with make.
make clean  -- Delete all binaries and object files.
make test   -- Build and run unit tests.
```

## Usage

```
./build/calc engine_name files...
./build/calc engine_name integers...
```

## Input File Format

Input files contain one or more lines of integers, each separated by whitespace.

## Implementing New Engines

The abstract class `Engine` represents a stateful computation engine. Each engine in the project
must derive from this, and implement the two member functions.

Engines follow a function-object style, for easy interoperability with the standard algorithms
library.

`void operator()(Integer value)`

Update the current state of the engine with the given value.

`Integer value()`

Return the current state of the engine. If the engine has not been updated through `operator()`,
this should return a sensible default value.
