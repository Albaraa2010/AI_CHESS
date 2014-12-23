//
//  King.h
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#ifndef __Chess__King__
#define __Chess__King__

#include <iostream>
#include "Piece.h"

class King: public Piece{
  
public:
  
  King(const Piece & piece):Piece(static_cast<_Piece*>(piece.ptr)){};
  
  King* clone();
  
  //Adds all valid moves to allPossibleMoves vector that is being sent in by reference.
  void getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove);
  
};

#endif /* defined(__Chess__King__) */
