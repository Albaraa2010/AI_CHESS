#include "AI.h"
#include "util.h"

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
}

//Part of the minimax algorithm: Gets the max of all minValues returns best move when reaching depth limit.
BestMove AI::maxValue(PieceTree & resultTree, PieceNode currentNode, int currentDepthLimit){
  BestMove chosenMove;
  BestMove childVal;
  chosenMove.value = -10000;
  chosenMove.move = NULL;
  if(currentNode.nodeDepth == currentDepthLimit){
    chosenMove.value = currentNode.totalPoints;
    chosenMove.move = &currentNode.currentMove;
    return chosenMove;
  } else {
    /*for(auto iter : currentNode.children){
      childVal = minValue(resultTree, *iter, currentDepthLimit);
      if( childVal.value > chosenMove.value){
        chosenMove.move = &iter->currentMove;
        chosenMove.value = childVal.value;
      }
    }*/
    for(std::vector<PieceNode*>::iterator it = currentNode.children.begin(); it != currentNode.children.end(); ++it){
      childVal = minValue(resultTree, **it, currentDepthLimit);
      if( childVal.value > chosenMove.value){
        chosenMove.move = &(*it)->currentMove;
        chosenMove.value = childVal.value;
      }
    }
    return chosenMove;
  }
}

//Part of the minimax algorithm: Gets the min of all maxValues returns best move when reaching depth limit.
BestMove AI::minValue(PieceTree & resultTree, PieceNode currentNode, int currentDepthLimit){
  BestMove chosenMove;
  BestMove childVal;
  chosenMove.value = 10000;
  chosenMove.move = NULL;
  if(currentNode.nodeDepth == currentDepthLimit){
    chosenMove.value = currentNode.totalPoints;
    chosenMove.move = &currentNode.currentMove;
    return chosenMove;
  } else {
    /*for(auto iter : currentNode.children){
      childVal = maxValue(resultTree, *iter, currentDepthLimit);
      if( childVal.value < chosenMove.value){
        chosenMove.move = &iter->currentMove;
        chosenMove.value = childVal.value;
      }
    }*/
    for(std::vector<PieceNode*>::iterator it = currentNode.children.begin(); it != currentNode.children.end(); ++it){
      childVal = maxValue(resultTree, **it, currentDepthLimit);
      if( childVal.value < chosenMove.value){
        chosenMove.move = &(*it)->currentMove;
        chosenMove.value = childVal.value;
      }
    }
    return chosenMove;
  }
}

BestMove AI::iterativelyDeepeningDepthLimitedMiniMax(Piece* (&chessBoard)[9][9], PieceMove* lastMove, int playerIDNum, std::vector<Move> & allLastMoves){
  //currentNode: used as the current node within a tree to calculate its possible moves (being the children of that current node).
  //             nodes include the parent node, new board, the move it took to get the new board, and the total point value of the new board
  PieceNode* currentNode;
  
  //maxDepthLimit: used to set the max depth allowed for the iteratively deepening depth search to create the tree to that depth.
  int maxDepthLimit = 3;
  
  //currentDepthLimit: used as the iterator to iteratively reach the max depth set within maxDepthLimit.
  int currentDepthLimit = 0;
  
  //resultTree: used as the tree that is filled up with all of the nodes created (for all of the different possible moves) of iterative depth until reaching the max depth limit.
  PieceTree resultTree;
  
  //tempPlayerID: changed throughout the creation of the tree. For every depth of the tree to player ID is changed as every depth is a different player's move.
  int tempPlayerID;
  
  //totalPoints: calculates the overall point value of the new board (used later within minimax algorithms to determine best move possible).
  int totalPoints = 0;
  
  //whitePoints: used to determine the total points.
  int whitePoints = 0;
  
  //blackPoints: used to determine the total points.
  int blackPoints = 0;
  //time_t endTime = time(NULL);
  /*for(int i = moves.size() - 1; i >= 0; i--){
    cout<<"Move: "<<i<<" "<<moves[i] <<endl;
  }*/
  
  //Starting loop which iterates through the current depth limit to eventually reach the max depth limit set.
  while(currentDepthLimit <= maxDepthLimit){
    
    //Constructing the first tree with the initial board (of the current board the game is on) and the last move of that board being sent in.
    resultTree = PieceTree(chessBoard, *lastMove);
    //current node being the first node within the tree in the beginning.
    currentNode = resultTree.getRoot();
    //currentChildrenList: a stack that keeps track of the new nodes being added to the depth of the tree so that it can be used to do an depth first search.
    std::stack<PieceNode*> currentChildrenList;

    currentChildrenList.push(currentNode);
    tempPlayerID = playerIDNum;
    currentNode->currentOwner = tempPlayerID;
    
    while(!currentChildrenList.empty()){
      //allPossibleMoves: a vector used to get all valid moves and then used to add all of these moves onto a tree with there proper values determined.
      std::vector<PieceMove> allPossibleMoves;
      
      //next node being used in the depth first creation of tree.
      currentNode = currentChildrenList.top();
      currentChildrenList.pop();

      //Determining which player moves should be made at the current depth of the tree (root and 1st depth starting at the player who is actually making a move).
      if(currentNode->nodeDepth >= 1){
        if((currentNode->nodeDepth) % 2 == 0){
          tempPlayerID = playerIDNum;
          currentNode->currentOwner = !tempPlayerID;
        } else {
          tempPlayerID = !playerIDNum;
          currentNode->currentOwner = !tempPlayerID;
        }
      }
      
      //Getting all valid moves and inputting them in allPossibleMoves array for either white or black players.
      if(tempPlayerID == 1){
        for (size_t rank=8; rank>0; rank--){
          for (size_t file=1; file<=8; file++){
            if(currentNode->chessBoard[rank][file] != NULL){
              if(currentNode->chessBoard[rank][file]->owner() == 1){
                currentNode->chessBoard[rank][file]->getValidMove(currentNode->chessBoard, allPossibleMoves, currentNode->currentMove);
              }
            }
          }
        }
      }else {
        for (size_t rank=8; rank>0; rank--){
          for (size_t file=1; file<=8; file++){
            if(currentNode->chessBoard[rank][file] != NULL){
              if(currentNode->chessBoard[rank][file]->owner() == 0){
                currentNode->chessBoard[rank][file]->getValidMove(currentNode->chessBoard, allPossibleMoves, currentNode->currentMove);
              }
            }
          }
        }
      }
      
      //Within this if statement the children of the current node are created and inserted within the tree if the depth of the current node is not the limit depth.
      if(currentNode->nodeDepth < currentDepthLimit){
        
        //Creating a copy of the current board to the new board.
        for(std::vector<PieceMove>::iterator it = allPossibleMoves.begin(); it != allPossibleMoves.end(); ++it) {
          Piece* newBoard[9][9];
          for (size_t rank=8; rank>0; rank--){
            for (size_t file=1; file<=8; file++){
              if(currentNode->chessBoard[rank][file] != NULL){
                newBoard[rank][file] = currentNode->chessBoard[rank][file]->clone();
              } else {
                newBoard[rank][file] = NULL;
              }
            }
          }
          
          //Making the new move on the new board by moving the piece at the current iteration of allPossibleMoves array which include all moves of the current node.
          newBoard[it->rank][it->file] = newBoard[it->fromRank][it->fromFile];
          newBoard[it->fromRank][it->fromFile] = NULL;
          
          //This gives -250 points to a move that is a repeated move to account for stalemates not occurring within the game.
          for(int i = moves.size() - 1; i >= 0; i--){
            if(it->rank == allLastMoves[i].fromRank() && it->file == allLastMoves[i].fromFile() && it->fromRank == allLastMoves[i].toRank() && it->fromFile == allLastMoves[i].toFile()){
              if(playerIDNum == 1){
                blackPoints = blackPoints - 250;
              } else {
                whitePoints = whitePoints - 250;
              }
            }
          }
          
          //Goes through the new board to add up the piece point values to eventually get the total point value of the current node to determine the best move within minimax algorithm.
          for (size_t rank=8; rank>0; rank--){
            for (size_t file=1; file<=8; file++){
              if(newBoard[rank][file] != NULL){
                if(newBoard[rank][file]->owner() == 1){
                  
                  //The King recieves a point value of 1000 to account for checkmate of an enemy piece being the best move or a move that makes the current player's piece not in check/checkmate.
                  if(newBoard[rank][file]->type() == 'K'){
                    blackPoints = blackPoints + 1000;
                  } else if(newBoard[rank][file]->type() == 'Q'){
                    blackPoints = blackPoints + 9;
                  } else if(newBoard[rank][file]->type() == 'R'){
                    blackPoints = blackPoints + 5;
                  } else if(newBoard[rank][file]->type() == 'B'){
                    blackPoints = blackPoints + 3;
                  } else if(newBoard[rank][file]->type() == 'N'){
                    blackPoints = blackPoints + 3;
                  } else if(newBoard[rank][file]->type() == 'P'){
                    blackPoints = blackPoints + 1;
                  }
                } else {
                  if(newBoard[rank][file]->type() == 'K'){
                    whitePoints = whitePoints + 1000;
                  } else if(newBoard[rank][file]->type() == 'Q'){
                    whitePoints = whitePoints + 9;
                  } else if(newBoard[rank][file]->type() == 'R'){
                    whitePoints = whitePoints + 5;
                  } else if(newBoard[rank][file]->type() == 'B'){
                    whitePoints = whitePoints + 3;
                  } else if(newBoard[rank][file]->type() == 'N'){
                    whitePoints = whitePoints + 3;
                  } else if(newBoard[rank][file]->type() == 'P'){
                    whitePoints = whitePoints + 1;
                  }
                }
              }
            }
          }
          
          //Depending on the player that will end up making the move the total points are calculated current player moving's points - enemy player points on the new board.
          if(playerIDNum == 1){
            totalPoints = blackPoints - whitePoints;
          } else {
            totalPoints = whitePoints - blackPoints;
          }
          
          //Inserting the new board (that includes the new move), the new board's point value, the parent node, and the move that was made to achieve the new board.
          PieceNode* temp = resultTree.insert(newBoard, currentNode, *it, totalPoints);
          
          //Pushing nodes onto the top of the children's stack.
          currentChildrenList.push(temp);
          
          //resetting all points to calculate the next boards points.
          whitePoints = 0;
          blackPoints = 0;
          totalPoints = 0;
        }
      }
      allPossibleMoves.clear();
    }
    currentChildrenList = stack<PieceNode*>();
    currentDepthLimit++;
  }
  currentNode = resultTree.getRoot();
  
  //Returns the value that is returned by the maxValue function which does the minimax algorithm and returns the best move to make.
  return maxValue(resultTree, *currentNode, maxDepthLimit);
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  //time_t startTime = time(NULL);
  Piece* chessBoard[9][9];
  Piece* referencePointer;
  PieceMove selectedMove;
  PieceMove lastMove;
  BestMove bestSelected;
  
  // Print out the current board state
  cout<<"+---+---+---+---+---+---+---+---+"<<endl;
  for(size_t rank=8; rank>0; rank--)
  {
    cout<<"|";
    for(size_t file=1; file<=8; file++)
    {
      bool found = false;
      // Loops through all of the pieces
      for(size_t p=0; !found && p<pieces.size(); p++)
      {
        // determines if that piece is at the current rank and file
        if(pieces[p].rank() == rank && pieces[p].file() == file)
        {
          found = true;
          referencePointer = &pieces[p];
          if(pieces[p].type() == 'P'){
            
            chessBoard[rank][file] = new Pawn(*referencePointer);
          
          }else if(pieces[p].type() == 'N'){
            
            chessBoard[rank][file] = new Knight(*referencePointer);
            
          }else if(pieces[p].type() == 'Q'){
            
            chessBoard[rank][file] = new Queen(*referencePointer);
            
          }else if(pieces[p].type() == 'B'){
            
            chessBoard[rank][file] = new Bishop(*referencePointer);
            
          }else if(pieces[p].type() == 'R'){
            
            chessBoard[rank][file] = new Rook(*referencePointer);
            
          }else if(pieces[p].type() == 'K'){
            
            chessBoard[rank][file] = new King(*referencePointer);
            
          }
          
          // Checks if the piece is black
          if(pieces[p].owner() == 1)
          {
            cout<<"*";
          }
          else
          {
            cout<<" ";
          }
          // prints the piece's type
          cout<<(char)pieces[p].type()<<" ";
        }
      }
      if(!found)
      {
        cout<<"   ";
        chessBoard[rank][file] = NULL;
      }
      cout<<"|";
    }
    cout<<endl<<"+---+---+---+---+---+---+---+---+"<<endl;
  }
  
  if(moves.size() > 0){
    lastMove.rank = moves[0].toRank();
    lastMove.file = moves[0].toFile();
    lastMove.fromRank = moves[0].fromRank();
    lastMove.fromFile = moves[0].fromFile();
  }
  
  //Getting all valid moves and inputting them in allPossibleMoves array.
  /*std::vector<PieceMove> allPossibleMoves;
  if(playerID() == 1){
    for (size_t rank=8; rank>0; rank--){
      for (size_t file=1; file<=8; file++){
        if(chessBoard[rank][file] != NULL){
          if(chessBoard[rank][file]->owner() == 1){
            //cout << (char)chessBoard[rank][file]->type() << endl;
            chessBoard[rank][file]->getValidMove(chessBoard, allPossibleMoves, lastMove);
          }
        }
      }
    }
  }else {
    for (size_t rank=8; rank>0; rank--){
      for (size_t file=1; file<=8; file++){
        if(chessBoard[rank][file] != NULL){
          if(chessBoard[rank][file]->owner() == 0){
            //cout << (char)chessBoard[rank][file]->type() << endl;
            chessBoard[rank][file]->getValidMove(chessBoard, allPossibleMoves, lastMove);
          }
        }
      }
    }
  }*/
  
  // Looks through information about the players
  for(size_t p=0; p<players.size(); p++)
  {
    cout<<players[p].playerName();
    // if playerID is 0, you're white, if its 1, you're black
    if(players[p].id() == playerID())
    {
      cout<<" (ME)";
    }
    cout<<" time remaining: "<<players[p].time()<<endl;
  }
    
  // if there has been a move, print the most recent move
  if(moves.size() > 0)
  {
    cout<<"Last Move Was: "<<endl<<moves[0]<<endl;
  }
  
  //Best move is returned from the iterativelyDeepeningDepthLimitedMiniMax search and inputs it into bestSelected variable.
  bestSelected = iterativelyDeepeningDepthLimitedMiniMax(chessBoard, &lastMove, playerID(), moves);
  
  //Makes the best move that was given through minimax algorithm
  bestSelected.move->movingPiece->move(bestSelected.move->file, bestSelected.move->rank, int('Q'));
  
  // select a random piece and move it to a random position on the board.  Attempts to promote to queen if a promotion happens
  
  /*selectedMove = allPossibleMoves[rand()%allPossibleMoves.size()];
  cout << "Type: " << (char)selectedMove.movingPiece->type() << " Owner: " << selectedMove.movingPiece->owner();
  cout << " Rank: " << selectedMove.rank << " File: " << selectedMove.file << endl;
  selectedMove.movingPiece->move(selectedMove.file, selectedMove.rank, int('Q'));*/
  
  //pieces[rand()%pieces.size()].move(rand()%8+1, rand()%8+1, int('Q'));
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
