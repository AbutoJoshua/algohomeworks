#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_merge(int *arr, int l, int k)
{
    int i;
    for(i = l; i < k; i++)
    {
        printf("%d\t", arr[i]);
    }

    return;
}

int min(int x, int y)
{ 
    if (x < y)
        return x;

    return y;  
} 

void mergeSort(int *arr, int n) 
{ 
   int curr_size, l_start;

   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
   {  
       for (l_start=0; l_start<n-1; l_start += 2*curr_size) 
       { 
           int m = l_start + curr_size - 1;
           int end = min(l_start + 2*curr_size - 1, n-1); 
           merge(arr, l_start, m, end); 
       } 
   } 
} 

void merge(int *arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int part_1 = m - l + 1; 
    int part_2 =  r - m; 
  
    int left_arr[part_1], right_arr[part_2]; 
  
    for (i = 0; i < part_1; i++) 
        left_arr[i] = arr[l + i]; 
    for (j = 0; j < part_2; j++) 
        left_arr[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < part_1 && j < part_2) 
    { 
        if (left_arr[i] <= right_arr[j]) 
        { 
            arr[k] = left_arr[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = right_arr[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < part_1) 
    { 
        arr[k] = left_arr[i]; 
        i++; 
        k++; 
    } 
  
    while (j < part_2) 
    { 
        arr[k] = right_arr[j]; 
        j++; 
        k++; 
    } 

    print_merge(arr, l, k);
} 

int main() 
{ 
    char f_name[100];
    //opening input file
    printf("Enter the input file:");
    FILE *fptr;
    scanf("%s", &f_name);
    fptr = fopen(f_name, 'r');
    
    //error handling
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    int size;
    int *d_arr, read;
    size_t len = 1000; //length of a line
    //Variable to store the input lines
    char *line; 
    

    while((read = getline(&line, &len, fptr)) != -1)
    {
        fscanf("%d", &size);
        if(size == -1)
            break;
        d_arr = (int *)malloc(size*sizeof(int));
        line = (char *)malloc(size*sizeof(char));

        if(fgets(line, size, fptr) != NULL)
        {
            int i;
            char *dummy[2];

            for(i = 0; i < size; i++)
            {
                d_arr[i] = (int) line[i];
            }
        }

        mergeSort(d_arr, size);
        
    }

   return 0;
} 


