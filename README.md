# Calculation Engines

A program that performs calculations on a series of integers.

## Usage

```
calc engine-name arg...
```

If any of the `args` contain a non-numeric character, it is assumed that all of the given arguments
represent files containing the integer series. Filenames have an implicit `.txt` extension, which is
appended to the input name.

If the `args` are all numeric, they are treated as the integer series.

Depending upon the engine, only one or the other means of specifying arguments may be supported.

## Input File Format

Input files contain one or more lines of integers, each separated by whitespace.