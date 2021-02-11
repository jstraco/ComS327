#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Y 21
#define X 80
//this is the array of charecters for the X by Y dungeon
char dungeon[Y][X];
void generateRooms();

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
  printf("room %d y value %d, x value %d \n",0,rooms[0].yPos,rooms[0].xPos);
  for(int currentRoom = 0; currentRoom < 6; currentRoom++){
    for(int currentY = rooms[currentRoom].yPos; currentY <= rooms[currentRoom].yEndPoint; currentY++){
      for(int currentX = rooms[currentRoom].xPos; currentX <= rooms[currentRoom].xEndPoint; currentX++){
	dungeon[currentY][currentX] = '.';
      }
    }
    printf("room %d y value %d, x value %d \n",0,rooms[0].yPos,rooms[0].xPos);
    printf("room %d (%d,%d) to (%d,%d)\n",currentRoom,rooms[currentRoom].yPos,rooms[currentRoom].xPos,rooms[currentRoom].yEndPoint,rooms[currentRoom].xEndPoint);
  }
}

void checkRooms(struct room rooms[6]){
  for(int i = 0; i < 6; i++){
    printf("room %d (%d,%d) to (%d,%d)\n",i,rooms[i].yPos,rooms[i].xPos,rooms[i].yEndPoint,rooms[i].xEndPoint);
    for(int j = 1; j < 6; j++){
      if(i == j && i == 5){
	break;
      }
      else{
	if(rooms[i].xPos == rooms[j].xPos || rooms[i].yPos == rooms[j].yPos){
	  generateRooms();
	  }
	 else if(rooms[i].xPos <= rooms[j].xPos && rooms[j].xPos <= rooms[i].xEndPoint && rooms[i].yPos <= rooms[j].yPos && rooms[j].yPos <= rooms[i].yEndPoint){
	  generateRooms();
	}
	 else if(rooms[i].xPos >= rooms[j].xPos && rooms[j].xPos >= rooms[i].xEndPoint && rooms[i].yPos >= rooms[j].yPos && rooms[j].yPos >= rooms[i].yEndPoint){
	  generateRooms();
	}
      }
    }
  }
}

void generateRooms(){
  
  srand(time(0));

  rooms[0].xPos = (rand() % 74) +1;
  rooms[0].yPos = (rand() % 16) +1;

  do {
    rooms[0].xSize = (rand() % 7) +4;
    rooms[0].ySize = (rand() % 8) +3;
  } while (rooms[0].xPos + rooms[0].xSize < X && rooms[0].yPos + rooms[0].ySize < Y);
  
  rooms[0].xEndPoint = rooms[0].xPos + rooms[0].xSize;
  rooms[0].yEndPoint = rooms[0].yPos + rooms[0].ySize;

  //set midpoint
  
  for(int i = 1; i < 6 ; i++){

    do{
    rooms[i].xPos = (rand() % 74) +1;
    rooms[i].yPos = (rand() % 16) +1;
    } while (checkRooms(i));
    rooms[i].xSize = (rand() % (10 - 4 + 1)) +4;
    rooms[i].ySize = (rand() % (10 - 3 + 1)) +3;
    
    rooms[i].xEndPoint = rooms[i].xPos + rooms[i].xSize;
    rooms[i].yEndPoint = rooms[i].yPos + rooms[i].ySize;
    if(checkRooms(i));
  }
}



  int checkRooms(int i)
  {
    for(int j = 0; j < i; j++) {
      if(rooms[j].xPos <= rooms[j].xPos && rooms[i].xEndpoint >= rooms[currIndex].x
	 return 0;
    }
      return 1;
  }

//This will  simply print the dungeon
void printDungeon(char dungeon[][X]){
   for(int j = 0; j < Y ;j++){
     for(int i = 0; i < X;i++){
        printf("%c", dungeon[j][i]);
     }
      printf("\n");
   }
}

int main(int argc, char *argv[]) {
   //The following for loops will populate the dungeon with empty space and boarders
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
   generateRooms();
   checkRooms(rooms);
   addRooms(rooms);
  printDungeon(dungeon);
  return 0;
}
