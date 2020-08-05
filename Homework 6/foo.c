#include <stdio.h>
#include <stdlib.h>

// Do not modify main
int main(int argc, char** argv) {
	int N, res1,res2;
	printf("Enter N: ");
	scanf("%d",&N);
    
	while (N!= -1){
		printf("Calling foo_iterative(N)\n");
		res1 = foo_iterative(N);
		printf("Result of iterative function for N=%d is: %d\n", N, res1);
		
		printf("Calling foo_wrapper(N)\n");
		res2 = foo_wrapper(N);
		printf("Result of memoized function for N=%d is: %d\n", N, res2);
		
		printf("\n--------------------------------\nEnter N: ");
		scanf("%d",&N);
	}
	return (EXIT_SUCCESS);
}

// Use this method to print the data for foo_memoized at different depth.
void print_at_depth(int depth, int N){
	int i;
	printf("\n");
	for(i=0;i<depth; i++){
		printf("   ");		
	}
	printf("N = %d, depth = %d\n", N, depth);
}


int foo_iterative(int N)
{
	int res1, res2, i;
	int arr[N+1];
	arr[0] = 5;
	arr[1] = 5;
	for(i = 2; i<=N; i++)
	{
		arr[i] = -1;
	}
	for(i = 2; i <= N; i++)
	{
		res1 = 3*arr[i/2];
		res2 = arr[N-1];

		if(res1 >= res2)
			arr[i]=res1;
		else
			arr[i]=res2;
	}
	return arr[N];  // TO DO: write your code in here
}

// This method should call foo_memoized
int foo_wrapper(int N)
{
	int depth = 0, i;
	int *arr = (int *)malloc(sizeof(int)*(N+1));
	arr[0] = 5;
	for(i = 1; i <= N; i++)
		arr[i] = -1;

	int val = foo_memoized(N, arr, depth);
	free(arr);
	return val; // TO DO: write your code in here. 
}       

// Write the foo_memized function
int foo_memoized(int N, int *M, int depth)
{
	int res1, res2;
	print_at_depth(depth, N);
	(depth)++;

	if(M[N] != -1)
		return M[N];

	if(N <= 1)
		return 5;

	res1 = 3*foo_memoized(N/2, M, depth);

	res2 = foo_memoized(N-1, M,depth);

	if(res1 >= res2)
	{
		M[N] = res1;
		return res1;
	} else
	{
		M[N] = res2;
		return res2;
	}
}
