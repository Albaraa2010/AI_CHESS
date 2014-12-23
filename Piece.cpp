// -*-c++-*-

#include "Piece.h"
#include "game.h"

using namespace std;

Piece::Piece(_Piece* pointer)
{
    ptr = (void*) pointer;
}

int Piece::id()
{
  return ((_Piece*)ptr)->id;
}

int Piece::owner() const
{
  return ((_Piece*)ptr)->owner;
}

int Piece::file()
{
  return ((_Piece*)ptr)->file;
}

int Piece::rank()
{
  return ((_Piece*)ptr)->rank;
}

int Piece::hasMoved()
{
  return ((_Piece*)ptr)->hasMoved;
}

int Piece::type()
{
  return ((_Piece*)ptr)->type;
}

int Piece::move(int file, int rank, int type)
{
  return pieceMove( (_Piece*)ptr, file, rank, type);
}

//If king is in check function (sent in the board, a move, and the piece moving)
//returns true if king is in check.
bool Piece::isKingInCheck(Piece* (&chessBoard)[9][9], PieceMove currentMove, Piece & sentPiece){

  bool isCheck = false;
  
  //Initializing new board that will copy sent board (to create new move and see if king becomes in check)
  Piece *tempChessBoard[9][9];
  
  //Initializing piece to equal the piece sent in after the move occurs.
  Piece currentPiece;
  
  //cout <<"Before: "<<endl;
  for (size_t rank=8; rank>0; rank--){
    //cout << "|";
    for (size_t file=1; file<=8; file++){
      tempChessBoard[rank][file] = chessBoard[rank][file];
      /*if(tempChessBoard[rank][file] != NULL){
        if(tempChessBoard[rank][file]->owner() == 1){
          cout << "*";
        } else{
          cout << " ";
        }
        cout << (char)tempChessBoard[rank][file]->type() << " ";
      }else{
        cout << "   ";
      }
      cout << "|";*/
    }
    //cout << endl;
  }

  tempChessBoard[currentMove.rank][currentMove.file] = &sentPiece;
  currentPiece = *tempChessBoard[currentMove.rank][currentMove.file];
  tempChessBoard[sentPiece.rank()][sentPiece.file()] = NULL;
  /*cout <<"After: "<<endl;
  for (size_t rank=8; rank>0; rank--){
    cout << "|";
    for (size_t file=1; file<=8; file++){
      if(tempChessBoard[rank][file] != NULL){
        if(tempChessBoard[rank][file]->owner() == 1){
          cout << "*";
        } else{
          cout << " ";
        }
        cout << (char)tempChessBoard[rank][file]->type() << " ";
      }else{
        cout << "   ";
      }
      cout << "|";
    }
    cout << endl;
  }*/
  
  if(currentPiece.owner() == 1){
    //Checking if enemy pawn is able to take the king from (-1, -1) and (-1, +1) diagonals (DIFFERENT IF PLAYER IS BLACK OR WHITE)
    if(currentPiece.rank() - 1 > 0 && currentPiece.file() - 1 > 0
       && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 1] != NULL
       && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 1]->owner() != currentPiece.owner()
       && (char)tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 1]->type() == 'P'){
      isCheck = true;
      return isCheck;
    }
    if(currentPiece.rank() - 1 > 0 && currentPiece.file() + 1 <= 8
       && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 1] != NULL
       && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 1]->owner() != currentPiece.owner()
       && (char)tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 1]->type() == 'P'){
      isCheck = true;
      return isCheck;
    }
  } else {
    //Checking if enemy pawn is able to take the king from (+1, -1) and (+1, +1) diagonals (DIFFERENT IF PLAYER IS BLACK OR WHITE)
    if(currentPiece.rank() + 1 <= 8 && currentPiece.file() - 1 > 0
       && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 1] != NULL
       && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 1]->owner() != currentPiece.owner()
       && (char)tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 1]->type() == 'P'){
      isCheck = true;
      return isCheck;
    }
    if(currentPiece.rank() + 1 <= 8 && currentPiece.file() + 1 <= 8
       && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 1] != NULL
       && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 1]->owner() != currentPiece.owner()
       && (char)tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 1]->type() == 'P'){
      isCheck = true;
      return isCheck;
    }
  }
  //Checking straight line after the king (up, down, right, and left) for Rook or Queen piece of other player that is able to take the king.
  for(int i = currentPiece.rank() + 1; i <= 8; i++){
    if(tempChessBoard[i][currentPiece.file()] != NULL && tempChessBoard[i][currentPiece.file()]->owner() == currentPiece.owner()){
      break;
    }
    else if(tempChessBoard[i][currentPiece.file()] != NULL && tempChessBoard[i][currentPiece.file()]->owner() != currentPiece.owner()
       && ((char)tempChessBoard[i][currentPiece.file()]->type() == 'R' || (char)tempChessBoard[i][currentPiece.file()]->type() == 'Q')){
      isCheck = true;
      return isCheck;
    }
  }
  for(int i = currentPiece.rank() - 1; i > 0; i--){
    if(tempChessBoard[i][currentPiece.file()] != NULL && tempChessBoard[i][currentPiece.file()]->owner() == currentPiece.owner()){
      break;
    }
    else if(tempChessBoard[i][currentPiece.file()] != NULL && tempChessBoard[i][currentPiece.file()]->owner() != currentPiece.owner()
       && ((char)tempChessBoard[i][currentPiece.file()]->type() == 'R' || (char)tempChessBoard[i][currentPiece.file()]->type() == 'Q')){
      isCheck = true;
      return isCheck;
    }
  }
  for(int i = currentPiece.file() + 1; i <= 8; i++){
    if(tempChessBoard[currentPiece.rank()][i] != NULL && tempChessBoard[currentPiece.rank()][i]->owner() == currentPiece.owner()){
      break;
    }
    else if(tempChessBoard[currentPiece.rank()][i] != NULL && tempChessBoard[currentPiece.rank()][i]->owner() != currentPiece.owner()
            && ((char)tempChessBoard[currentPiece.rank()][i]->type() == 'R' || (char)tempChessBoard[currentPiece.rank()][i]->type() == 'Q')){
      isCheck = true;
      return isCheck;
    }
  }
  for(int i = currentPiece.file() - 1; i > 0; i--){
    if(tempChessBoard[currentPiece.rank()][i] != NULL && tempChessBoard[currentPiece.rank()][i]->owner() == currentPiece.owner()){
      break;
    }
    else if(tempChessBoard[currentPiece.rank()][i] != NULL && tempChessBoard[currentPiece.rank()][i]->owner() != currentPiece.owner()
       && ((char)tempChessBoard[currentPiece.rank()][i]->type() == 'R' || (char)tempChessBoard[currentPiece.rank()][i]->type() == 'Q')){
      isCheck = true;
      return isCheck;
    }
  }
  //Checking all 4 diagonal lines after the king for a Bishop or Queen piece of other player that is able to take the king.
  int breakFlag = 0;
  int rankCounter = 0;
  int fileCounter;
  for(int i = currentPiece.rank() + 1; i <= 8; i++){
    fileCounter = 0;
    for(int j = currentPiece.file() + 1; j <= 8; j++){
      if(rankCounter == fileCounter){
        if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() == currentPiece.owner()){
          breakFlag = 1;
          break;
        }
        else if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() != currentPiece.owner()
           && ((char)tempChessBoard[i][j]->type() == 'B' || (char)tempChessBoard[i][j]->type() == 'Q')){
          isCheck = true;
          return isCheck;
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
  for(int i = currentPiece.rank() - 1; i > 0; i--){
    fileCounter = 0;
    for(int j = currentPiece.file() + 1; j <= 8; j++){
      if(rankCounter == fileCounter){
        if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() == currentPiece.owner()){
          breakFlag = 1;
          break;
        }
        else if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() != currentPiece.owner()
           && ((char)tempChessBoard[i][j]->type() == 'B' || (char)tempChessBoard[i][j]->type() == 'Q')){
          isCheck = true;
          return isCheck;
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
  for(int i = currentPiece.rank() + 1; i <= 8; i++){
    fileCounter = 0;
    for(int j = currentPiece.file() - 1; j > 0; j--){
      if(rankCounter == fileCounter){
        if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() == currentPiece.owner()){
          breakFlag = 1;
          break;
        }
        else if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() != currentPiece.owner()
           && ((char)tempChessBoard[i][j]->type() == 'B' || (char)tempChessBoard[i][j]->type() == 'Q')){
          isCheck = true;
          return isCheck;
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
  for(int i = currentPiece.rank() - 1; i > 0; i--){
    fileCounter = 0;
    for(int j = currentPiece.file() - 1; j > 0; j--){
      if(rankCounter == fileCounter){
        if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() == currentPiece.owner()){
          breakFlag = 1;
          break;
        }
        else if(tempChessBoard[i][j] != NULL && tempChessBoard[i][j]->owner() != currentPiece.owner()
           && ((char)tempChessBoard[i][j]->type() == 'B' || (char)tempChessBoard[i][j]->type() == 'Q')){
          isCheck = true;
          return isCheck;
        }
      }
      fileCounter++;
    }
    if(breakFlag == 1){
      break;
    }
    rankCounter++;
  }
  //Checking for 8 possible places that enemy horse can be located in order to take the king.
  if(currentPiece.rank() + 2 <= 8 && currentPiece.file() + 1 <= 8
     && tempChessBoard[currentPiece.rank() + 2][currentPiece.file() + 1] != NULL
     && (char)tempChessBoard[currentPiece.rank() + 2][currentPiece.file() + 1]->type() == 'N'
     && tempChessBoard[currentPiece.rank() + 2][currentPiece.file() + 1]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() + 2 <= 8 && currentPiece.file() - 1 > 0
     && tempChessBoard[currentPiece.rank() + 2][currentPiece.file() - 1] != NULL
     && (char)tempChessBoard[currentPiece.rank() + 2][currentPiece.file() - 1]->type() == 'N'
     && tempChessBoard[currentPiece.rank() + 2][currentPiece.file() - 1]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() - 2 > 0 && currentPiece.file() + 1 <= 8
     && tempChessBoard[currentPiece.rank() - 2][currentPiece.file() + 1] != NULL
     && (char)tempChessBoard[currentPiece.rank() - 2][currentPiece.file() + 1]->type() == 'N'
     && tempChessBoard[currentPiece.rank() - 2][currentPiece.file() + 1]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() - 2 > 0 && currentPiece.file() - 1 > 0
     && tempChessBoard[currentPiece.rank() - 2][currentPiece.file() - 1] != NULL
     && (char)tempChessBoard[currentPiece.rank() - 2][currentPiece.file() - 1]->type() == 'N'
     && tempChessBoard[currentPiece.rank() - 2][currentPiece.file() - 1]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() + 1 <= 8 && currentPiece.file() + 2 <= 8
     && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 2] != NULL
     && (char)tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 2]->type() == 'N'
     && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() + 2]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() + 1 <= 8 && currentPiece.file() - 2 > 0
     && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 2] != NULL
     && (char)tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 2]->type() == 'N'
     && tempChessBoard[currentPiece.rank() + 1][currentPiece.file() - 2]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() - 1 > 0 && currentPiece.file() + 2 <= 8
     && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 2] != NULL
     && (char)tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 2]->type() == 'N'
     && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() + 2]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  if(currentPiece.rank() - 1 > 0 && currentPiece.file() - 2 > 0
     && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 2] != NULL
     && (char)tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 2]->type() == 'N'
     && tempChessBoard[currentPiece.rank() - 1][currentPiece.file() - 2]->owner() != currentPiece.owner()){
    isCheck = true;
    return isCheck;
  }
  return isCheck;
}

std::ostream& operator<<(std::ostream& stream,Piece ob)
{
  stream << "id: " << ((_Piece*)ob.ptr)->id  <<'\n';
  stream << "owner: " << ((_Piece*)ob.ptr)->owner  <<'\n';
  stream << "file: " << ((_Piece*)ob.ptr)->file  <<'\n';
  stream << "rank: " << ((_Piece*)ob.ptr)->rank  <<'\n';
  stream << "hasMoved: " << ((_Piece*)ob.ptr)->hasMoved  <<'\n';
  stream << "type: " << ((_Piece*)ob.ptr)->type  <<'\n';
  return stream;
}
