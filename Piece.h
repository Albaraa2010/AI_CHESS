// -*-c++-*-

#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "structures.h"
#include "Move.h"

class Piece;

struct PieceMove{
  int rank;
  int file;
  int fromRank;
  int fromFile;
  int promotion;
  Piece *movingPiece;
  
  PieceMove(){
    rank = 0;
    file = 0;
    promotion = 0;
    movingPiece = NULL;
  }
  
  PieceMove(int pieceRank, int pieceFile, int piecePromotion, Piece *pieceMoving){
    rank = pieceRank;
    file = pieceFile;
    promotion = piecePromotion;
    movingPiece = pieceMoving;
  }
};

///A chess piece
class Piece {
  public:
  void* ptr;
  Piece(_Piece* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The owner of the piece
  int owner() const;
  ///The letter this piece is at (1-8)
  int file();
  ///The number this piece is at (1-8)
  int rank();
  ///1=has moved, 0=has not moved
  int hasMoved();
  ///The letter that describes this piece's type. K=King, Q=Queen, B=Bishop, N=Knight, R=Rook, P=Pawn
  int type();

  // Actions
  ///
  int move(int file, int rank, int type);
  
  virtual Piece* clone(){
    return this;
  };
  
  //Gets all valid moves (used in sub classes of this piece class, such as Pawn, Knight, and etc classes).
  //Adds all valid moves to allPossibleMoves vector that is being sent in by reference.
  virtual void getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
    PieceMove newMove;
    return;
  }
  
  //If king is in check function (sent in the board, a move, and the piece moving)
  //returns true if king is in check.
  bool isKingInCheck(Piece* (&chessBoard)[9][9], PieceMove currentMove, Piece & currentPiece);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Piece ob);
};

#endif

