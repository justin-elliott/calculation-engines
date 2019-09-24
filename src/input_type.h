// input_type.h
// A type representing allowable inputs on the command line: files, integers, or either.

#ifndef INPUT_TYPE_H
#define INPUT_TYPE_H

enum class InputType : unsigned
{
    None        = 0x00,
    Files       = 0x01,
    Integers    = 0x02,
    Any         = Files | Integers
};

inline InputType operator&(InputType lhs, InputType rhs) {
    return static_cast<InputType>(
        static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

inline InputType operator|(InputType lhs, InputType rhs) {
    return static_cast<InputType>(
        static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

#endif // INPUT_TYPE_H
