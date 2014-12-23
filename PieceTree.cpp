//
//  PieceTree.cpp
//  Chess
//
//  Created by Albaraa on 3/21/14.
//  Copyright (c) 2014 Albaraa. All rights reserved.
//

#include "PieceTree.h"

PieceTree::PieceTree(){
}

PieceTree::PieceTree(Piece* (&chessBoard)[9][9], PieceMove lastMove){
  this->root = PieceNode(chessBoard, NULL, lastMove, NULL);
}

PieceNode* PieceTree::getRoot(){
  return &this->root;
}

PieceTree::~PieceTree(){
}

PieceNode* PieceTree::insert(Piece* (&chessBoard)[9][9], PieceNode* parent, PieceMove currentMove, int totalPoints){
  PieceNode* resultPuzzle = new PieceNode(chessBoard, parent, currentMove, totalPoints);
  parent->children.push_back(resultPuzzle);
  
  return resultPuzzle;
}