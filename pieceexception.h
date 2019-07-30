#ifndef PIECEEXCEPTION_H
#define PIECEEXCEPTION_H

#include <stdexcept>

// Thrown when a piece doesn't exist at the location specified or
// is the wrong colour or cannot be placed there
class PieceException : public std::runtime_error {
public:
  PieceException(const char* m) : std::runtime_error(m) { }
};

#endif
