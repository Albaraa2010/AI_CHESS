//
//  Rook.h
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#ifndef __Chess__Rook__
#define __Chess__Rook__

#include <iostream>
#include "Piece.h"

class Rook: public Piece{
  
public:
  
  Rook(Piece & piece):Piece(static_cast<_Piece*>(piece.ptr)){};
  
  Rook* clone();
  
  //Adds all valid moves to allPossibleMoves vector that is being sent in by reference.
  void getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove);
  
};

#endif /* defined(__Chess__Rook__) */
