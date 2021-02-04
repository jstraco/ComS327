#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 23

void printArray(int arr[][MAX]){
  int i,j;
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      if(arr[j][i] == -1){
	printf("#");
      } else {
      printf("%d", arr[j][i]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void topple(int arr[][MAX], int y, int x){
  int i,j;
  arr[y][x] = 0;
  for (j=y-1 ;j < y+2 ; j++){
    for(i=x-1 ;i < x+2 ; i++){
      if(i >= 0 && i < MAX && j >=0 && j < MAX && arr[j][i] != -1){
	arr[j][i]++;
	if(arr[j][i] > 8){
	  topple(arr, j, i); 
	}
      }
    }
  } 
}


int highest(int first, int second);
int lowest(int first, int second);

/* TO DO
   impliment sleep time. I think we need to get user input for what they want the refresh rate to be; so you might need to pass another variable into the "topple" method for the refresh rate
 */
int main(int argc, char *argv[]) {

  int j, i;
  //definitions
  int plane[MAX][MAX];
  //populating array with 0, TODO: take user input from the command line
  //and populate the desired positions of the plane with the desired
  //values that the user has input, "./sandpile 11 11 8" would make the center
  //value at 11 11 be equal to 8.
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      plane[j][i] = 0;
    }
  }
  int argIndex = 1; 
  for(i=argc/3;i>0;i--) {
    plane[atoi(argv[argIndex + 1])][atoi(argv[argIndex])]  = atoi(argv[argIndex + 2]);
    argIndex += 3;
  }
  //main loop
  while(1){
    if(plane[11][11] != -1){	
      plane[11][11]++;
    }
    if(plane[11][11] > 8) {
      topple(plane, 11, 11);
    }
    printArray(plane);
  }
  return 0;
}

