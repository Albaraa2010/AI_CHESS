//
//  Queen.cpp
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include "Queen.h"

Queen* Queen::clone(){
  return new Queen (*this);
}

void Queen::getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
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
  
  //Checks all 4 diagonal line moves for Queen.
  
  //Used to get out of loops when necessary
  int breakFlag = 0;
  //Rank counter used to determine if current check is on diagonal line with the Queen piece.
  int rankCounter = 0;
  //File counter used to determine if current check is on diagonal line with the Queen piece.
  int fileCounter;
  for(int i = this->rank() + 1; i <= 8; i++){
    fileCounter = 0;
    for(int j = this->file() + 1; j <= 8; j++){
      if(rankCounter == fileCounter){
        if(chessBoard[i][j] != NULL && chessBoard[i][j]->owner() == this->owner()){
          breakFlag = 1;
          break;
        }
        newMove.fromRank = this->rank();
        newMove.fromFile = this->file();
        newMove.rank = i;
        newMove.file = j;
        newMove.promotion = 0;
        
        if(isKingInCheck(chessBoard, newMove, *this) == false){
          allPossibleMoves.push_back(newMove);
        }
        
        if(chessBoard[i][j] != NULL){
          breakFlag = 1;
          break;
        }
        
      }
      fileCounter++;
    }
    if(breakFlag == 1){
      break;
    }
    rankCounter++;
  }
  
  breakFlag = 0;
  rankCounter = 0;
  for(int i = this->rank() - 1; i > 0; i--){
    fileCounter = 0;
    for(int j = this->file() + 1; j <= 8; j++){
      if(rankCounter == fileCounter){
        if(chessBoard[i][j] != NULL && chessBoard[i][j]->owner() == this->owner()){
          breakFlag = 1;
          break;
        }
        newMove.fromRank = this->rank();
        newMove.fromFile = this->file();
        newMove.rank = i;
        newMove.file = j;
        newMove.promotion = 0;
        
        if(isKingInCheck(chessBoard, newMove, *this) == false){
          allPossibleMoves.push_back(newMove);
        }
        
        if(chessBoard[i][j] != NULL){
          breakFlag = 1;
          break;
        }
        
      }
      fileCounter++;
    }
    if(breakFlag == 1){
      break;
    }
    rankCounter++;
  }
  
  breakFlag = 0;
  rankCounter = 0;
  for(int i = this->rank() + 1; i <= 8; i++){
    fileCounter = 0;
    for(int j = this->file() - 1; j > 0; j--){
      if(rankCounter == fileCounter){
        if(chessBoard[i][j] != NULL && chessBoard[i][j]->owner() == this->owner()){
          breakFlag = 1;
          break;
        }
        newMove.fromRank = this->rank();
        newMove.fromFile = this->file();
        newMove.rank = i;
        newMove.file = j;
        newMove.promotion = 0;
        
        if(isKingInCheck(chessBoard, newMove, *this) == false){
          allPossibleMoves.push_back(newMove);
        }
        
        if(chessBoard[i][j] != NULL){
          breakFlag = 1;
          break;
        }
        
      }
      fileCounter++;
    }
    if(breakFlag == 1){
      break;
    }
    rankCounter++;
  }
  
  breakFlag = 0;
  rankCounter = 0;
  for(int i = this->rank() - 1; i > 0; i--){
    fileCounter = 0;
    for(int j = this->file() - 1; j > 0; j--){
      if(rankCounter == fileCounter){
        if(chessBoard[i][j] != NULL && chessBoard[i][j]->owner() == this->owner()){
          breakFlag = 1;
          break;
        }
        newMove.fromRank = this->rank();
        newMove.fromFile = this->file();
        newMove.rank = i;
        newMove.file = j;
        newMove.promotion = 0;
        
        if(isKingInCheck(chessBoard, newMove, *this) == false){
          allPossibleMoves.push_back(newMove);
        }
        
        if(chessBoard[i][j] != NULL){
          breakFlag = 1;
          break;
        }
        
      }
      fileCounter++;
    }
    if(breakFlag == 1){
      break;
    }
    rankCounter++;
  }
  
  return;
};