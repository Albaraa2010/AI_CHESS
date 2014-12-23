//
//  Bishop.h
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#ifndef __Chess__Bishop__
#define __Chess__Bishop__

#include <iostream>
#include "Piece.h"

class Bishop: public Piece{
  
public:
  
  Bishop(const Piece & piece):Piece(static_cast<_Piece*>(piece.ptr)){};
  
  Bishop* clone();
  
  //Adds all valid moves to allPossibleMoves vector that is being sent in by reference.
  void getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove);
  
};

#endif /* defined(__Chess__Bishop__) */
