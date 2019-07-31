#ifndef PIECEEXCEPTION_H
#define PIECEEXCEPTION_H

#include <stdexcept>
#include <string>

// Thrown when a piece doesn't exist at the location specified,
// is the wrong colour, cannot be placed there or there is no piece
// in listPieces at the given index
class PieceException : public std::runtime_error {
public:
  PieceException(const char* m) : std::runtime_error(m) { }
  PieceException(const std::string m) : std::runtime_error(m) { }
};

#endif
