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
  
}

void updatePlane(int arr[][MAX]){
  int i,j;
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      printf("%d", arr[j][i]);
    }
    printf("\n");
  }
}

int main(/*int argc, char *argv[]*/) {


  //something
  int plane[MAX][MAX];
  int i,j;
  for(j=0;j<MAX;j++){
    for(i=0;i<MAX;i++){
      plane[j][i] = 0;
    }
  }
  printArray(plane);
  /*
  for (j = 0 ; j < 10000 ; j++) {
    for(i = 0; i < 10000 ; i++) {


    }
  }
  */
  return 0;
}
