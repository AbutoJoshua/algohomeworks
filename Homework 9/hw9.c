#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void matrix_call(int matrix[][10], char *vertices[], char *edges[], int size)
{
    int i, j;
    
    for(i = 0; i < size; i++)
    {
        char *str1, *str2;
        str1 = edges[0];
        str2 = vertices[i];
        if(strcmp(str1, str2) == 0)
        {
            for(j = 0; j < size; j++)
            {
                str1 = edges[1];
                str2 = vertices[j];
                if(strcmp(str1, str2)==0)
                {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
            }
        }
                
    }
    
}

void printmatrix(int matrix[][10], int size)
{
    int i, j;
    for(i=0; i < size; i++)
    {
        for(j = 0; j <size; j++)
        {
            printf("%d", matrix[i][j]);
        }
    }
}

void depthfirstsearch(int matrix[][10], char *vertices[], int size)
{
    int i, j, cnt = 1;
    char *str;

    for(i = 0; i < size; i++)
    {
        str = vertices[i];
        printf("Group %d", cnt);
        if(str != NULL)
        {
            for(j = 0; j < size; j++)
            {
                if(matrix[i][j] == 1 && vertices[j] != NULL)
                {
                    printf("%s\n", vertices[j]);
                    vertices[j] = NULL;
                }
            }
            
            printf("\n\n");
        }

        cnt++;
        
    }
}

int main()
{
    //FILE *fptr;
    int size, i, j;
    char  f_name[100];
    printf("please enter number of the vertice:\n");
    scanf("%d", &size);
    printf("%d", size);

    int matrix[size][size];
    char *vertices[size], *edges[2];
    char *str;
    str = (char *)malloc(sizeof(char *)*100);
    for(i = 0; i <size; i++)
    {
        printf("Enter Vertex");   
        scanf("%s", str); //assumes no line is greater than 100 charaters
        vertices[i]=str;
        for(j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }
    char *node1, *node2;
    node1 = "1";
    while(node1 != "-1")
    {
        //node1 = strtok(str, " ");
        //node2 = strtok(NULL, '\0');
        scanf("%s %s", node1, node2);
        char *str2;
        str2 = "-1";
        if(strcmp(node1, str2) == 0)
        {
            break;
        }

        edges[0] = node1;
        edges[1] = node2;

        matrix_call(matrix, vertices, edges, size);

    }

    printmatrix(matrix, size);

    depthfirstsearch(matrix, vertices, size);

    free(matrix);
    free(vertices);
    free(str);
    free(edges);

    //fclose(fptr);
}

