#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 23

//method to print the plane
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
//method to cause a pile of >8 to topple, handles other piles that might topple recursivly
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
int main(int argc, char *argv[]) {
  //declarations
  int j, i, fps;
  int argIndex = 1;
  int plane[MAX][MAX];
  //for loop to populate the plane with zeros
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      plane[j][i] = 0;
    }
  }
  //taking user input from command line
  if (!strcmp("--fps", argv[1])){
    fps = atoi(argv[2]);
    argIndex = 3;
    argc = argc - 2;
  } else {
    fps = 60;
  }
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
    printf("FPS = %d\n", fps);
    usleep(100000/fps);
  }
  return 0;
}

