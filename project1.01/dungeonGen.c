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
   for(int j = 0; j < X ;j++){
     for(int i = 0; i < Y;i++){
       printf("%d", dungeon[j][i]);
     }
     printf("\n");
   }
}
//I'm not sure if I did the pointers right
int main(int argc, char *argv[]) {
   struct room rooms[6];
   // char dungeon[Y][X];
   generateRooms(rooms);
   printf("%d",rooms[0].xPos);
   // dungeon[1][1] =* "g";
  //does this need pointers?
   /* for(int j = 0; j < X ;j++){
    dungeon[0][j] = '-';
    for(int i = 1; i < Y-1;i++){
       dungeon[i][j] = ' ';
    }
     dungeon[Y-1][j] = '-';
     }*/
  printf("made it here\n");
  return 0;
}
