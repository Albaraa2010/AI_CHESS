//
//  Knight.cpp
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include <cmath>
#include "Knight.h"

Knight* Knight::clone(){
  return new Knight (*this);
}

void Knight::getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
  PieceMove newMove;
  newMove.movingPiece = this;
  
  //Loops through and checks all possible L shaped moves for the knight (8 possibilities).
  for(int i = -2; i <= 2; i++){
    for(int j = -2; j <= 2; j++){
      if(abs(i) != abs(j) && i != 0 && j != 0 && this->rank() + i <= 8 && this->rank() + i > 0 && this->file() + j <= 8 && this->file() + j > 0
         && (chessBoard[this->rank() + i][this->file() + j] == NULL || chessBoard[this->rank() + i][this->file() + j]->owner() != this->owner())){
        
        newMove.fromRank = this->rank();
        newMove.fromFile = this->file();
        newMove.rank = this->rank() + i;
        newMove.file = this->file() + j;
        newMove.promotion = 0;
        
        if(isKingInCheck(chessBoard, newMove, *this) == false){
          allPossibleMoves.push_back(newMove);
        }
      }
    }
  }
  
  
  return;
};