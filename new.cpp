#include <stdlib.h>
#include <map>
#include <iostream>
#include <sstream>
#include <unistd.h>

std::map<std::string,std::string> plastic; //Too lazy to keep copy and pasting.
std::string board[8][8]; //Global.




/* Initiate game. Setup board. */

void init() {

 plastic["b+rook"] = " ♜ ";
 plastic["w+rook"] = " ♖ ";
 plastic["b+knight"] = " ♞ ";
 plastic["w+knight"] = " ♘ ";
 plastic["b+jester"] = " ♝ ";
 plastic["w+jester"] = " ♗ ";
 plastic["b+queen"] = " ♛ ";
 plastic["w+queen"] = " ♕ ";
 plastic["b+king"] = " ♚ ";
 plastic["w+king"] = " ♔ ";
 plastic["b+pawn"] = " ♟ ";
 plastic["w+pawn"] = " ♙ ";


 board[0][0] = "b+rook";
 board[1][0] = "b+knight";
 board[2][0] = "b+jester";
 board[3][0] = "b+queen";
 board[4][0] = "b+king";
 board[5][0] = "b+jester";
 board[6][0] = "b+knight";
 board[7][0] = "b+rook";
 board[0][1] = "b+pawn";
 board[1][1] = "b+pawn";
 board[2][1] = "b+pawn";
 board[3][1] = "b+pawn";
 board[4][1] = "b+pawn";
 board[5][1] = "b+pawn";
 board[6][1] = "b+pawn";
 board[7][1] = "b+pawn";
 for (int i = 2; i < 6; i++) {//Initialize tiles between as empty.
  for (int j = 0; j <= 7; j++) {
   board[j][i] = "open";
  }
 }
 board[0][7] = "w+rook";
 board[1][7] = "w+knight";
 board[2][7] = "w+jester";
 board[3][7] = "w+queen";
 board[4][7] = "w+king";
 board[5][7] = "w+jester";
 board[6][7] = "w+knight";
 board[7][7] = "w+rook";
 board[0][6] = "w+pawn";
 board[1][6] = "w+pawn";
 board[2][6] = "w+pawn";
 board[3][6] = "w+pawn";
 board[4][6] = "w+pawn";
 board[5][6] = "w+pawn";
 board[6][6] = "w+pawn";
 board[7][6] = "w+pawn";
}

/*
Construct a string for each row to be passed into system().
1 - start with each row (y value).
2 - read contents of the coord. If empty, add an empty tile char to the row string.
3 - if not empty, then add the char that corresponds to the string.
4 - if the if string has "+h" at s.length()-1 + s.length(), then add an additional
    "/033.. char /033.." to change the background for that particular tile. 
5 - Once that row string has been made, execute in a system() call.
6 - Go to the next row, y++, repeat until all 8 rows are redrawn. 
*/


int draw() {
 //system("echo -en \"\\033[s\""); //Save cursor position.
 std::string rowCall = "";
 for (int row = 0; row <= 7; row++) {
  rowCall = "";
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << "\\033[";
  ss << row + 1;
  ss << ";";
  ss << 1;
  ss << "f";
  rowCall = ss.str();
  for (int col = 0; col <= 7; col++) {
   std::string tile = board[col][row];
   if ((tile[tile.length()] == 'h') && (tile[tile.length()-1] == '+')) {
    rowCall += "\\033[7m"; //If highlighted, invert everything.
   }
   if (tile == "open" || tile == "open+h") {
   //Alternate all of the tiles like a chess board.
    if (row % 2 == 0) {
     if (col % 2 == 0) { rowCall += " ☐ "; }
     if (col % 2 == 1) { rowCall += " ☒ "; }
    } else if (row % 2 == 1) {
     if (col % 2 == 1) { rowCall += " ☐ "; }
     if (col % 2 == 0) { rowCall += " ☒ "; }
    }
   }
    
   //If not an empty tile, then just make it equal to whatever value the key is.
   rowCall += plastic[tile]; //Make sure adds as string.
  
   
   
  }
  //std::cout << rowCall << std::endl;
  rowCall = "echo  -en \"" + rowCall + "\"";
  const char* callThis = rowCall.c_str();
  //std::cout << callThis << " a " << std::endl;
  system(callThis);
  usleep(500000);
 }   
 //system("echo -en \"\\033[u\""); //Restore cursor position.
 
}
 
 
 
 
 
 /*
 //system("echo -en \"\\033[s\""); //Save cursor position.
 std::string rowCall = "";
 for (int row = 0; row <= 7; row++) {
  for (int col = 0; col <= 7; col++) {
   rowCall = "";
   std::stringstream ss(std::stringstream::in | std::stringstream::out);
   ss << "\\033[";
   ss << col + 1;
   ss << ";";
   ss << row + 1;
   ss << "f";
   rowCall = ss.str();
   
   std::string tile = board[col][row];
   if ((tile[tile.length()] == 'h') && (tile[tile.length()-1] == '+')) {
    rowCall += "\\033[7m"; //If highlighted, invert everything.
   }
   if (tile == "open" || tile == "open+h") {
   //Alternate all of the tiles like a chess board.
    if (row % 2 == 0) {
     if (col % 2 == 0) { rowCall += " ☐ "; }
     if (col % 2 == 1) { rowCall += " ☒ "; }
    } else if (row % 2 == 1) {
     if (col % 2 == 1) { rowCall += " ☐ "; }
     if (col % 2 == 0) { rowCall += " ☒ "; }
    }
   }
  
   //If not an empty tile, then just make it equal to whatever value the key is.
   rowCall += plastic[tile]; //Make sure adds as string.
   rowCall = "echo -en \"" + rowCall + "\"";
   
   std::cout << rowCall << std::endl;
   const char* callThis = rowCall.c_str();
   //system(callThis);
   usleep(100000);
  }
  
 }   
 //system("echo -en \"\\033[u\""); //Restore cursor position.
}  

*/


class piece {
 public:
  virtual int move() = 0;
  int x;
  int y;
 private:
  
};


class king : piece {
 public:
  void highlight() { //Highlight possible moves
   if (x > 0) {
    board[x-1][y] += "+h";
   }
   if (x < 8) {
    board[x+1][y] += "+h";
   }
   if (y > 0) {
    board[x][y-1] += "+h";
   }
   if (y < 8) {
    board[x][y+1] += "+h";
   }
   //Goes through all the boards, and also changes background if has +h.
   draw();
  };
 private:
  int xPos;
  int yPos;
};


int main() {
 system("./conf.sh");
 init();
 draw();
 draw();
 draw();
}

