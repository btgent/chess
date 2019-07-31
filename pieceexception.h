#ifndef PIECEEXCEPTION_H
#define PIECEEXCEPTION_H

#include <stdexcept>

// Thrown when a piece doesn't exist at the location specified,
// is the wrong colour, cannot be placed there or piece doesn't exist
// at that number in listPieces
class PieceException : public std::runtime_error {
public:
  PieceException(const char* m) : std::runtime_error(m) { }
};

#endif
