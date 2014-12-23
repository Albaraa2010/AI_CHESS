//
//  King.cpp
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include "King.h"

King* King::clone(){
  return new King (*this);
}

void King::getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
  PieceMove newMove;
  newMove.movingPiece = this;
  
  //Checks all possible moves for King (Up, Down, Left, Right, and 4 Diagonals of only 1 cell move)
  if(this->rank() + 1 <= 8 && (chessBoard[this->rank() + 1][this->file()] == NULL || chessBoard[this->rank() + 1][this->file()]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() + 1;
    newMove.file = this->file();
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->file() + 1 <= 8 && (chessBoard[this->rank()][this->file() + 1] == NULL || chessBoard[this->rank()][this->file() + 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = this->file() + 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->rank() - 1 > 0 && (chessBoard[this->rank() - 1][this->file()] == NULL || chessBoard[this->rank() - 1][this->file()]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() - 1;
    newMove.file = this->file();
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->file() - 1 > 0 && (chessBoard[this->rank()][this->file() - 1] == NULL || chessBoard[this->rank()][this->file() - 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = this->file() - 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->rank() + 1 <= 8 && this->file() + 1 <= 8 && (chessBoard[this->rank() + 1][this->file() + 1] == NULL
     || chessBoard[this->rank() + 1][this->file() + 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() + 1;
    newMove.file = this->file() + 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->rank() + 1 <= 8 && this->file() - 1 > 0 && (chessBoard[this->rank() + 1][this->file() - 1] == NULL
     || chessBoard[this->rank() + 1][this->file() - 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() + 1;
    newMove.file = this->file() - 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->rank() - 1 > 0 && this->file() + 1 <= 8 && (chessBoard[this->rank() - 1][this->file() + 1] == NULL
     || chessBoard[this->rank() - 1][this->file() + 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() - 1;
    newMove.file = this->file() + 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  if(this->rank() - 1 > 0 && this->file() - 1 > 0 && (chessBoard[this->rank() - 1][this->file() - 1] == NULL
     || chessBoard[this->rank() - 1][this->file() - 1]->owner() != this->owner())){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() - 1;
    newMove.file = this->file() - 1;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  //Castling if black with rook (8, 1)
  if(chessBoard[8][1] != NULL && chessBoard[8][1]->type() == 'R' && this->hasMoved() == 0 && this->owner() == 1 && chessBoard[8][1]->hasMoved() == 0 && chessBoard[8][2] == NULL && chessBoard[8][3] == NULL && chessBoard[8][4] == NULL){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = 3;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  //Castling if black with rook (8, 8)
  if(chessBoard[8][8] != NULL && chessBoard[8][8]->type() == 'R' && this->hasMoved() == 0 && this->owner() == 1 && chessBoard[8][8]->hasMoved() == 0 && chessBoard[8][7] == NULL && chessBoard[8][6] == NULL){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = 7;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  //Castling if white with rook (1, 1)
  if(chessBoard[1][1] != NULL && chessBoard[1][1]->type() == 'R' && this->hasMoved() == 0 && this->owner() == 0 && chessBoard[1][1]->hasMoved() == 0 && chessBoard[1][2] == NULL && chessBoard[1][3] == NULL && chessBoard[1][4] == NULL){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = 3;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  //Castling if white for rook (1, 8)
  if(chessBoard[1][8] != NULL && chessBoard[1][8]->type() == 'R' && this->hasMoved() == 0 && this->owner() == 0 && chessBoard[1][8]->hasMoved() == 0 && chessBoard[1][7] == NULL && chessBoard[1][6] == NULL){
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = 7;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  return;
};

