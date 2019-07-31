#ifndef MOVEEXCEPTION_H
#define MOVEEXCEPTION_H

#include <stdexcept>

// Thrown when a move is invalid, there is no move on stackMove to undo,
// or there is no move in stackMove at the given index
class MoveException : public std::runtime_error {
public:
  MoveException(const char* m) : std::runtime_error(m) { }
};

#endif
