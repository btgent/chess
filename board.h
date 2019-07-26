#ifndef BOARD_H
#define BOARD_H

#include "move.h"   // Should rename to PastMove.h
#include <vector>

class Piece;
class FutureMove;    // Need to add
class Colour;
class Coord;
class Type;

// In the future, Board would be an abstract class,
// this would be StdBoard class, and there would be
// ExtraBoard class with additional functionality
// like nogo spaces and support for multiple colours.
// There could also be a ExtremeBoard with extra
// functions like placing pieces during the game
// and being able to perform multiple moves in the
// same turn

// If ExtraBoard were to inherit from the same class,
// then kingBlack... would need to be a map, there'd be
// a const int numColours, nextColour(), and a map isAlive
// from Colour to bool
// Or Controller can deal with it, though it breaks
// invariants a bit (Move doesn't know which colour moved)
// ((Though Move.colour is necessary to display moves properly
//   in 4-hand chess))
class Board {
  std::vector<Piece*> listPieces;
  std::vector<Move> stackMove;
  Piece *kingWhite;
  Piece *kingBlack;
  const int size;
  // I think Board should handle who's turn it is

  void forceMove(Coord, Coord);
  void (int, int, int, int);
  int index(Coord);
  int index(int, int);

 public:
  Board(std::vector<Piece*>, int size=8);
  //Board(const Board &b);
  //Board &operator=(const Board &b);
  ~Board();

  void undo();
  void move(FutureMove, Colour);
  void move(Coord, Coord, Colour, Type);
  void move(int, int, int, int, Colour, Type);
  void move(Coord, Coord, Colour);
  void move(int, int, int, int, Colour);
  bool check(Colour);
  bool checkmate(Colour);
  bool pieceAt(Coord);
  bool pieceAt(int, int);
  bool outOfBounds(Coord);
  bool outOfBounds(Coord);
  //vector<Move> allMoves(Colour);
  //int numAllMoves(Colour);
};

#endif
