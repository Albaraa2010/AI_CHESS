//
//  Rook.cpp
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include "Rook.h"

using namespace std;

Rook* Rook::clone(){
  return new Rook (*this);
}

void Rook::getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
  PieceMove newMove;
  newMove.movingPiece = this;
  
  //Checks straight line moves for Queen (Up, Down, Right, Left).
  for(int i = this->rank() + 1; i <= 8; i++){
    if(chessBoard[i][this->file()] != NULL && chessBoard[i][this->file()]->owner() == this->owner()){
      break;
    }
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = i;
    newMove.file = this->file();
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
    
    if(chessBoard[i][this->file()] != NULL){
      break;
    }
  }
  
  for(int i = this->file() + 1; i <= 8; i++){
    if(chessBoard[this->rank()][i] != NULL && chessBoard[this->rank()][i]->owner() == this->owner()){
      break;
    }
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = i;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
    
    if(chessBoard[this->rank()][i] != NULL){
      break;
    }
  }
  
  for(int i = this->rank() - 1; i > 0; i--){
    if(chessBoard[i][this->file()] != NULL && chessBoard[i][this->file()]->owner() == this->owner()){
      break;
    }
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = i;
    newMove.file = this->file();
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
    
    if(chessBoard[i][this->file()] != NULL){
      break;
    }
  }
  
  for(int i = this->file() - 1; i > 0; i--){
    if(chessBoard[this->rank()][i] != NULL && chessBoard[this->rank()][i]->owner() == this->owner()){
      break;
    }
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank();
    newMove.file = i;
    newMove.promotion = 0;
    
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
    
    if(chessBoard[this->rank()][i] != NULL){
      break;
    }
  }
  return;
};