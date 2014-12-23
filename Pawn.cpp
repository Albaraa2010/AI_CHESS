//
//  Pawn.cpp
//  Chess
//
//  Created by Albaraa on 3/6/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include "Pawn.h"

Pawn* Pawn::clone(){
  return new Pawn (*this);
}

void Pawn::getValidMove(Piece* (&chessBoard)[9][9], std::vector<PieceMove> &allPossibleMoves, PieceMove & lastMove){
  PieceMove newMove;
  newMove.movingPiece = this;
  
  //If pawn has not yet moved, the pawn is able to go forward twice.
  if(this->hasMoved() == 0){
    //Check if owner of current pawn is black and if the two spots in front if the pawn are empty.
    if(this->owner() == 1 && chessBoard[this->rank() - 2][this->file()] == NULL && chessBoard[this->rank() - 1][this->file()] == NULL){
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() - 2;
      newMove.file = this->file();
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
      
    //Check if owner of current pawn is white and if the two spots in front if the pawn are empty.
    }else if(this->owner() == 0 && chessBoard[this->rank() + 2][this->file()] == NULL && chessBoard[this->rank() + 1][this->file()] == NULL){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 2;
      newMove.file = this->file();
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
  }
  
  //Normal pawn moving forward one block
  if(this->owner() == 1 && this->rank() <= 8 && this->rank() > 0 && chessBoard[this->rank() - 1][this->file()] == NULL){
    //Check if king is in check
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() - 1;
    newMove.file = this->file();
    newMove.promotion = 0;
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }else if(this->owner() == 0 && this->rank() <= 8 && this->rank() > 0 && chessBoard[this->rank() + 1][this->file()] == NULL){
    //Check if king is in check
    
    newMove.fromRank = this->rank();
    newMove.fromFile = this->file();
    newMove.rank = this->rank() + 1;
    newMove.file = this->file();
    newMove.promotion = 0;
    if(isKingInCheck(chessBoard, newMove, *this) == false){
      allPossibleMoves.push_back(newMove);
    }
  }
  
  //Pawn moving to the location of another piece of the different owner diagonally (if black [+1][+1] or [+1][-1], if white [-1][+1] or [-1][-1]) taking the piece out.
  for(int j = - 1; j <= 1; j++){
    if(this->owner() == 1 && this->rank() - 1 <= 8 && j != 0 && this->file() + j <= 8 && this->file() + j > 0 && chessBoard[this->rank() - 1][this->file() + j] != NULL
       && chessBoard[this->rank() - 1][this->file() + j]->owner() != this->owner()){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() - 1;
      newMove.file = this->file() + j;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }else if(this->owner() == 0 && this->rank() + 1 > 0 && j != 0 && this->file() + j <= 8 && this->file() + j > 0 && chessBoard[this->rank() + 1][this->file() + j] != NULL
             && chessBoard[this->rank() + 1][this->file() + j]->owner() != this->owner()){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 1;
      newMove.file = this->file() + j;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
  }
  
  //En Passant if owner is black
  if(this->owner() == 1 && this->rank() == 4){
    if(this->file() + 1 <= 8 && chessBoard[this->rank()][this->file() + 1] != NULL && chessBoard[this->rank()][this->file() + 1]->owner() != this->owner()
       && chessBoard[this->rank()][this->file() + 1]->type() == this->type() && lastMove.fromRank == 2 && lastMove.rank == 4 && lastMove.file == this->file() + 1){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 1;
      newMove.file = this->file() + 1;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
    
    if(this->file() - 1 > 0 && chessBoard[this->rank()][this->file() - 1] != NULL && chessBoard[this->rank()][this->file() - 1]->owner() != this->owner()
       && chessBoard[this->rank()][this->file() - 1]->type() == this->type() && lastMove.fromRank == 2 && lastMove.rank == 4 && lastMove.file == this->file() - 1){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 1;
      newMove.file = this->file() - 1;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
    
  //En Passant if owner is white
  } else if(this->owner() == 0 && this->rank() == 5){
    if(this->file() + 1 <= 8 && chessBoard[this->rank()][this->file() + 1] != NULL && chessBoard[this->rank()][this->file() + 1]->owner() != this->owner()
       && chessBoard[this->rank()][this->file() + 1]->type() == this->type() && lastMove.fromRank == 7 && lastMove.rank == 5 && lastMove.file == this->file() + 1){
      //Check if king is in check
      
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 1;
      newMove.file = this->file() + 1;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
    
    if(this->file() - 1 > 0 && chessBoard[this->rank()][this->file() - 1] != NULL &&  chessBoard[this->rank()][this->file() - 1]->owner() != this->owner()
       && chessBoard[this->rank()][this->file() - 1]->type() == this->type() && lastMove.fromRank == 7 && lastMove.rank == 5 && lastMove.file == this->file() - 1){
      //Check if king is in check
     
      newMove.fromRank = this->rank();
      newMove.fromFile = this->file();
      newMove.rank = this->rank() + 1;
      newMove.file = this->file() - 1;
      newMove.promotion = 0;
      if(isKingInCheck(chessBoard, newMove, *this) == false){
        allPossibleMoves.push_back(newMove);
      }
    }
    
  }
  
  return;
};

