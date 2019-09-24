// non_copyable.h
// A base class intended to make all derived classes non-copyable.
//
// Usage:
//   class MyClass : private NonCopyable { ... };

#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

#endif // NON_COPYABLE_H
