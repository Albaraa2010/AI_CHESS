#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "PieceTree.h"
#include <time.h>
#include <vector>
#include <typeinfo>
#include <stack>
#include <iostream>
#include <cstdlib>
using namespace std;

struct BestMove{
  int value;
  PieceMove* move;
};

///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();
  BestMove maxValue(PieceTree & resultTree, PieceNode currentNode, int currentDepthLimit);
  BestMove minValue(PieceTree & resultTree, PieceNode currentNode, int currentDepthLimit);
  BestMove iterativelyDeepeningDepthLimitedMiniMax(Piece* (&chessBoard)[9][9], PieceMove* lastMove, int playerIDNum, std::vector<Move> & moves);
};

#endif
