#include <stdio.h>
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

void topple(int arr[][MAX], int x, int y){
  int i,j;
  for (j=y-1 ;j < y+2 ; j++){
    for(i=x-1 ;i < x+2 ; i++){
      if(j == y && i == x){
	arr[j][i] = 0;
      }
      else if(i >= 0 && i < MAX && j >=0 && j < MAX){
	arr[j][i]++;
	if(arr[j][i] > 8){
	  topple(arr, j, i); 
	}
      }
    }
  } 
}

int main(/*int argc, char *argv[]*/) {


  //something
  int plane[MAX][MAX];
  int i,j;
  //populating array with 0s
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      plane[j][i] = 0;
    }
  }
  
  //printArray(plane);
  plane[11][11]=8;
  printArray(plane);
  topple(plane, 11, 11);
  printArray(plane);

  
  return 0;
}
