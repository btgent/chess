#ifndef UNEXPECTEDEXCEPTION_H
#define UNEXPECTEDEXCEPTION_H

#include <stdexcept>

// Thrown when something that shouldn't be allowed to happen, happens
// eg. invariant being broken, a logical error (though to simplify things
// we put it under runtime_error)
class UnexpectedException : public std::runtime_error {
public:
  UnexpectedException(const char* m) : std::runtime_error(m) { }
  UnexpectedException(const std::string m) : std::runtime_error(m) { }
};

#endif
