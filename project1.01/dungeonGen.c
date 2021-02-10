#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Y 21
#define X 80

struct room
{
  int xPos;
  int yPos;
  int xSize;
  int ySize;
};

void generateRooms(struct room rooms[6]){
  //https://www.geeksforgeeks.org/generating-random-number-range-c/ (random num gen)
  // todo generate rooms of random size to fit room size requirements 
  for(int i = 0; i < 6 ; i++){
    printf("%d",i);
  }
}

//This should simply print the dungeon
void printDungeon(char dungeon[][X]){
   for(int j = 0; j < Y ;j++){
     for(int i = 0; i < X;i++){
       printf("%c", dungeon[j][i]);
     }
     printf("\n");
   }
}
//I'm not sure if I did the pointers right
int main(int argc, char *argv[]) {
  //struct room rooms[6];

   char dungeon[Y][X];

   //generateRooms(rooms);

   //printf("%d",rooms[0].xPos);
   //dungeon[1][1] =* "g";
  //does this need pointers?
   for(int j = 0; j < Y ;j++){
     dungeon[j][0] = '|';
     dungeon[j][X-1] = '|';
     for(int i = 1; i < X-1;i++){
       dungeon[j][i] = ' ';
     }
   }
   for(int i = 0; i < X; i++){
     dungeon[0][i] = '-';
     dungeon[Y-1][i] = '-';
   }
  printDungeon(dungeon);
  return 0;
}
