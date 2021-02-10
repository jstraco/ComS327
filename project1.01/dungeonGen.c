#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Y 21
#define X 80

//This should simply print the dungeon
void printDungeon(char *dungeon[][X]){
   for(int j = 0; j < X ;j++){
     for(int i = 0; i < Y;i++){
       printf("%s", dungeon[j][i]);
     }
     printf("\n");
   }
}
//I'm not sure if I did the pointers right
int main(int argc, char *argv[]) {

  char *dungeon[Y][X];
  //this is just adding a top boarder and a bottom boarder of --- to the dungeon,
  //with white space in the middle
  for(int j = 0; j < X ;j++){
    *dungeon[0][j] = '-';
    for(int i = 1; i < Y-1;i++){
      *dungeon[i][j] = ' ';
    }
    *dungeon[Y-1][j] = '-';
  }
  printDungeon(dungeon);
  return 0;
}
