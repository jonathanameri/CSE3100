#include <stdio.h>
#include <stdlib.h>



typedef struct SubArray{
	int start;
	int end;
	int sum;
} SubArray;

SubArray kadane(int* numbers, int length){
  /* Given the numbers array containing length integers, compute the max sub array and return struct SubArray 
     
    We begin by initializing a struct that contains the best sub array we've found so far (bestSubArray), and the best subarray ending at the previous position. 
   */
  SubArray bestSubArray = {0, 0, numbers[0]};
  SubArray prevSubArray = {0, 0, numbers[0]};

  for(int j = 1; j < length; j++){
	if(prevSubArray.sum > 0){
		prevSubArray.end = j;
		prevSubArray.sum += numbers[j];
	}
	else{
		prevSubArray.start = j;
		prevSubArray.end = j;
		prevSubArray.sum = numbers[j];
	}
	if(prevSubArray.sum > bestSubArray.sum){
		bestSubArray = prevSubArray;
	}

    /*
      When we are at index j, we need to make a decision about what the best sub-array ending at index j is. As described in the assignment, there are two options:

    1) The best sub-array ending at index j also starts at index j
    2) The best sub-array ending at index j starts at an index before j

    Suppose case 2 is true. Then, the best sub-array ending at index j is just an extension of the best array ending at index j - 1.

    To evaluate which case is better, we need to keep track of the best sub-array ending at index j - 1.
      TODO: Decide if case 1 or 2 is correct, and then do what is necessary for each case. 
     */
  }
  return bestSubArray;


}


int main(int argc, char* argv[]){
  printf("Enter numbers (then press 0 and enter): ");
  int numbersLength = 1;
  int* numbers =  (int*)malloc(sizeof(int)*numbersLength);
  int x = 0;
  int i = 0;
  while(scanf("%d", &x) == 1 && x != 0){
    if(i == numbersLength){
	    numbers = (int*)realloc(numbers, sizeof(int)*(numbersLength+1));
	    numbersLength++;
    }
    numbers[i] = x;
    i++;
  }
  struct SubArray result = kadane(numbers, i);
  printf("Max Sub Array: ");
  for(i = result.start; i <= result.end; i++){
    printf("%d ", numbers[i]);
  }
  printf("\n");
  free(numbers);
  return 0;
}
