 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/

int edit_distance(char * first_string, char * second_string, int print_table)
{
	int distance, i, j, k, l;
    int f_size = strlen(first_string), l_size = strlen(second_string);
    int d_table[f_size][l_size];
    
    //Creating the cost for the row 0
    for(i=0; i < l_size + 2 ; i++)
    {
        d_table[0][i] = i;
       // printf(" %d|", i);
    }
    //creating the cost for column 0
    for(j=0; j < f_size + 2; j++)
    {
        d_table[j][0] = j;
       // printf(" %d|", j);
    }    
    for(k = 1; k < f_size+2; k++)
    {
        for(l=1; l < l_size+2; l++)
        {
            if(first_string[k-1] == second_string[l-1]) //if char's are equal
            {
                int s = min(d_table[k-1][l],d_table[k][l-1]);
                if(s == d_table[k-1][l-1]) //checks if all three numbers are equal
                {
                    d_table[k][l]= d_table[k-1][l-1];
                } else //picks the smallest number
                {
                    d_table[k][l]= min(min(d_table[k-1][l],d_table[k][l-1]), d_table[k-1][l-1]);
                }                
            } else //if the char's are not equal
            {
                d_table[k][l]= min(min(d_table[k-1][l],d_table[k][l-1]), d_table[k-1][l-1]) + 1;
            }            
        }
    }
    if(print_table == 1)
    {
		for(k=0; k < l_size + 2; k++)
		{
			if(k == 0 || k == 1)
				printf("  |");
			else
				printf("  %c", second_string[l-2]);
		}
		printf("\n");
        for(k = 1; k <= f_size + 1; k++)
        {
            for(l=0; l <= l_size + 1; l++)
            {
                    if(k==1 && l == 0)
                    {
                        printf("  |");
                    } else if(l==0)
                    {
                        printf( "  %c|", first_string[k-2]);
                    } else
                    {
                        printf("  %d|", d_table[k-1][l-1]);
                    }
               
                
            }

            printf("\n");
            
        }
    }

    distance = d_table[f_size][l_size];
   // printf("edit distance: %d", distance);
    return distance;  // replace this line with your code
}
	  
	  
void spellcheck(char * dictname, char * testname)
{	
    FILE *dptr;
    dptr = fopen(dictname, "r");
    FILE *tptr;
    tptr = fopen(testname, "r");
    

    if(dptr == NULL || tptr == NULL)
    {
        printf("Opening file error!\n");
    }

    int dsize, x;

    fscanf(dptr, "%d", &dsize);
    int *ptr = (int*)malloc(sizeof(int)*dsize);
    char *wptr[dsize];
    char cword[101];
    int d_distances[dsize];
    int min_d, tsize;
    fscanf(tptr, "%d", &tsize);

    while(!feof(tptr)) //!feof(tptr);
    {
        fscanf(tptr, "%s", cword);
        printf("\n------- Current test word: %s\n", cword);
        int distance;
        x = 0;
        min_d = 1000;
        //scanf("%s",names[n][0]);
        while(x < dsize)
        {
            fscanf(dptr,"%s", wptr[x]);

            distance = edit_distance(wptr[x], cword, 0);

            if(min_d > distance)
                min_d = distance;
            d_distances[x] = distance;
            x++;
        }
        //scanf("%d", &dsize);

        printf("Minimum distance: %d\n", min_d);
        printf("Words that give minimum distance: \n");

        for(x = 0; x < dsize; x++)
        {
            if(min_d == d_distances[x])
                printf("%s\n", wptr[x]);
        }
        
        printf("\n");
    }

    free(ptr);
    fclose(dptr);
    fclose(tptr);

}


int min(int x, int y) 
{ 
    return y ^ ((x ^ y) & -(x < y)); 
} 
