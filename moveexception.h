#ifndef MOVEEXCEPTION_H
#define MOVEEXCEPTION_H

#include <stdexcept>

// Thrown when a move causes the king with the same colour to be in check
// or there is no move on stackMove to undo
class MoveException : public std::runtime_error {
public:
  MoveException(const char* m) : std::runtime_error(m) { }
};

#endif
