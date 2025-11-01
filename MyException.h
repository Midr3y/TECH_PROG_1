#pragma once
#include <exception>

class MyException : public std::exception {
private:
    const char* message;
public:
    MyException(const char* msg) noexcept : message(msg) {}
    const char* what() const noexcept override { return message; }
};
