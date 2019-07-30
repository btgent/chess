#ifndef SETUPEXCEPTION_H
#define SETUPEXCEPTION_H

#include <stdexcept>

// Thrown when a setup function is called in non-setup mode or
// when a non-setup function is called in setup mode (referring to class Board)
class SetupException : public std::runtime_error {
public:
  SetupException(const char* m) : std::runtime_error(m) { }
};

#endif
