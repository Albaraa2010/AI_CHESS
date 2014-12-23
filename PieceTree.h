//
//  PieceTree.h
//  Chess
//
//  Created by Albaraa on 3/21/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#ifndef __Chess__PieceTree__
#define __Chess__PieceTree__


#include "Piece.h"
#include <iostream>

struct PieceNode{
  PieceMove currentMove;
  Piece* chessBoard[9][9];
  std::vector<PieceNode*> children;
  PieceNode* parent;
  int nodeDepth;
  int currentOwner;
  int totalPoints;
  
  PieceNode(){};
  
  PieceNode(Piece* (&chessBoard)[9][9], PieceNode* parent, PieceMove currentMove, int totalPoints){
    for (size_t rank=8; rank>0; rank--){
      for (size_t file=1; file<=8; file++){
        if(chessBoard[rank][file] != NULL){
          this->chessBoard[rank][file] = chessBoard[rank][file]->clone();
        } else {
          this->chessBoard[rank][file] = NULL;
        }
      }
    }
    this->parent = parent;
    this->currentMove = currentMove;
    this->children = std::vector<PieceNode*>();
    this->totalPoints = totalPoints;
    if(parent != NULL){
      this->nodeDepth = parent->nodeDepth + 1;
    } else {
      this->nodeDepth = 0;
    }
  }
  
  ~PieceNode(){};
};

class PieceTree{
private:
  PieceNode root;
  
public:
  PieceTree();
  PieceTree(Piece* (&chessBoard)[9][9], PieceMove lastMove);
  PieceNode* getRoot();
  PieceNode* insert(Piece* (&chessBoard)[9][9], PieceNode* parent, PieceMove currentMove, int totalPoints);
  ~PieceTree();
};

#endif /* defined(__Chess__PieceTree__) */
