#ifndef SETUPEXCEPTION_H
#define SETUPEXCEPTION_H

#include <stdexcept>

class SetupException : public std::runtime_error {
public:
  SetupException(const char* m) : std::runtime_error(m) { }
};

#endif
