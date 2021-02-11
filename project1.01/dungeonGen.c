#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Y 21
#define X 80
//this is the array of charecters for the X by Y dungeon
char dungeon[Y][X];
void generateRooms();
int checkPoint();
int checkSize();

struct room
{
  int xPos;
  int yPos;
  int xSize;
  int ySize;
  int xEndPoint;
  int yEndPoint;
  int yMid;
  int xMid;
};
struct room rooms[6];

void addRooms(struct room rooms[6]){
  for(int room = 0; room < 6; room++){
    for(int j = rooms[room].yPos; j <= rooms[room].yEndPoint; j++){
      for(int i = rooms[room].xPos; i <= rooms[room].xEndPoint; i++){
	dungeon[j][i] = '.';
      }
    }
    printf("room %d (%d,%d) to (%d,%d)\n",room,rooms[room].yPos,rooms[room].xPos,rooms[room].yEndPoint,rooms[room].xEndPoint);
  }
}

void generateRooms(){
  
  srand(time(0));

  rooms[0].xPos = (rand() % 74) +1;
  rooms[0].yPos = (rand() % 16) +1;

  do {
    rooms[0].xSize = (rand() % 7) +4;  //7
    rooms[0].ySize = (rand() % 8) +3;  //8
    rooms[0].xEndPoint = rooms[0].xPos + rooms[0].xSize;
    rooms[0].yEndPoint = rooms[0].yPos + rooms[0].ySize;
  } while (rooms[0].xEndPoint >= X && rooms[0].yEndPoint >= Y);
  
  for(int i = 1; i < 6 ; i++){

    do {
    rooms[i].xPos = (rand() % 74) +1;
    rooms[i].yPos = (rand() % 16) +1;
    } while (checkPoint(i));

    do {
    rooms[i].xSize = (rand() % (10 - 4 + 1)) +4;
    rooms[i].ySize = (rand() % (10 - 3 + 1)) +3;
    rooms[i].xEndPoint = rooms[i].xPos + rooms[i].xSize;
    rooms[i].yEndPoint = rooms[i].yPos + rooms[i].ySize;
    } while (checkSize(i));
  }
}

int checkPoint(int i){
    for(int j = 0; j < i; j++) {
      if(rooms[i].xPos > rooms[j].xPos - 6 && rooms[i].xPos < rooms[j].xEndPoint + 2 &&
	  rooms[i].yPos > rooms[j].yPos - 5 && rooms[i].yPos < rooms[j].yEndPoint + 2){
	return 1;
      }
    }
    return 0;
}
int checkSize(int i)
  {
    for(int j = 0; j < i; j++) {
      if(rooms[i].xEndPoint >= X || rooms[i].yEndPoint >= Y || 
	 ((rooms[i].xPos < rooms[j].xEndPoint + 2 && rooms[i].xEndPoint > rooms[j].xPos-2) &&
	  (rooms[i].yPos < rooms[j].yEndPoint + 2 && rooms[i].yEndPoint > rooms[j].yPos-2))){
	 return 1;
      }
    }
      return 0;
  }
//This will  simply print the dungeon
void printDungeon(char dungeon[][X]){
  for(int i = 0; i < 82; i++){
    printf("-");
  }
  printf("\n");
   for(int j = 0; j < Y ;j++){
     printf("|");
     for(int i = 0; i < X;i++){
        printf("%c", dungeon[j][i]);
     }
      printf("|\n");
   }
  for(int i = 0; i < 82; i++){
    printf("-");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
   //The following for loops will populate the dungeon with empty space and boarders
     for(int j = 0; j < Y ;j++){
       for(int i = 0; i < X;i++){
       dungeon[j][i] = ' ';
     }
   }
   generateRooms();
   addRooms(rooms);
  printDungeon(dungeon);
  return 0;
}
