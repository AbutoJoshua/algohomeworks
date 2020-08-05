
//Joshua Abuto 
//Homework 9
//1001530342

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct struct_graph 
{
    int number_of_vertices;
    int **adjacencies;
};

typedef struct struct_graph * graph;

int edgeExists(graph g, int v1, int v2)
{
    return g->adjacencies[v1][v2];
}
void addEdge(struct struct_graph *g, int v1, int v2)
{
    g->adjacencies[v1][v2] = 1;
    g->adjacencies[v2][v1] = 1;
}

void removeEdge(graph g, int v1, int v2)
{
    g->adjacencies[v1][v2] = 0;
    g->adjacencies[v2][v1] = 0;
}

void dfs_visit(graph g, int i, int color[], int pred[], int group_num, int groups[])
{
    color[i] = 1;
    int j;

    for(j = 0; j < g->number_of_vertices; j++)
    {
        if(g->adjacencies[i][j] == 1)
        {
            if(color[j] == 0)
            {
                pred[j]= i;
                
                dfs_visit(g, j, color, pred, group_num, groups);
            }
        }
    }
    groups[i] = group_num;
    color[i] = 2;

    return;
}

int dfs(graph g, int groups[])
{
    int i, j;
    int color[g->number_of_vertices];
    int pred[g->number_of_vertices];

    //color = (char *)malloc(g.number_of_vertices*(sizeof));
    //pred = (char *)malloc(g.number_of_vertices*(sizeof));
    // 0 - white, 1 - grey 2 - black -> for color array
    //
    for(i=0;i < g->number_of_vertices; i++)
    {
        color[i] = 0;
        pred[i] = 0;
        //groups[]
    }
    int group_num = 1;
    for(i=0;i < g->number_of_vertices; i++)
    {
        if(color[i] == 0)
        {
            dfs_visit(g, i, color, pred, group_num, groups);
            group_num++;
        }
            
        
    }

    return group_num;
}


void free2d(int **array, int rows, int columns)
{ 
   int row;
   // VERY IMPORTANT: free the space for each row
   for (row = 0; row < rows; row++)
      free(array[row]);
   
   // free the space with the pointer to each row.
   free(array);
}

void destroyGraph(graph g)
{
   if (g == NULL) return;
   free2d(g->adjacencies, g->number_of_vertices, g->number_of_vertices);
   free(g);
}


int ** malloc_2d(int row, int col)
{ 
   int rows;
   // allocate space to keep a pointer for each row
   int **result = (int**)malloc(row * sizeof(int *)); 
   
   // VERY IMPORTANT: allocate the space for each row
   for (rows = 0; rows < row; rows++)
      result[rows] = (int*)malloc(col * sizeof(int));
   
   return result;
}

graph newGraph(int size)
{
    graph g = malloc(sizeof(graph));
   g->number_of_vertices = size;
   g->adjacencies = (int **)calloc(size, sizeof(int *));
   
   // initialize adjacencies to signify that at present the
   // graph contains no edges.
   int i, j;
   for (i = 0; i < size; i++)
   {
      g->adjacencies[i] = calloc(size, sizeof(int));
   }
   
   return g;
}



int main()
{
    int size, i, j;
    struct struct_graph *g;

    printf("Enter the number of vertices: ");
    scanf("%d", &size);
    printf("%d\n", size);
    char str[100];
   // str = (char *)malloc(100*sizeof(char));
    //g->number_of_vertices = size;
    //g.adjacencies[size][size];
    //int matrix[size][size];
    g = newGraph(size);
    printf("Graph V: %d\n", g->number_of_vertices);
    char arr[size][100];
    //arr = (char *)malloc(100*sizeof(char *));

	printf("\n");
    for(i = 0; i < size; i++)
    {
        char tmpe[100];
        printf("Enter vertex: ");
        scanf("%s", tmpe);
        strcpy(arr[i], tmpe);
        printf("%s\n", arr[i]);
        
    }
    char str1[100];
    char str2[100];
	printf("\n");

    while(scanf("%s %s", str1, str2) != 1)
    {
        printf("%s %s\n", str1, str2);
        //char *edge1 = strtok(str, " ");
        //char *edge2 = strtok(NULL, "\0");
        if(strcmp(str1, "-1") == 0 || strcmp(str2, "-1") == 0)
            break;

        int v1, v2;
        for(j = 0; j < size; j++)
        {
            if(strcmp(str1, arr[j]) == 0)
            {
                v1 = j;
            }
                

            if(strcmp(str2, arr[j]) == 0)
            {
                v2 = j;
            }
                
        }
        //printf("addEdge worked");
        addEdge(g, v1, v2);
        
    }
    
	printf("\n");

    //print matrix
    for(i=0; i < size; i++)
    {
        for(j = 0; j <size; j++)
        {
            //g->adjacencies[i][j] = 0;
            printf("%d", g->adjacencies[i][j]);
            //printf("worked");
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < size; i++)
    {
        printf("%s\n", arr[i]);
    }
    
   //printf("Before groups");
    int groups[size];
	printf("\n");
    int gs = dfs(g, groups);
    printf("Total number of groups %d\n", gs-1);
    i = 1;
    while(i < gs)
    {
        printf("Group: %d\n", i);
        for(j=0; j < size; j++)
        {
            if(groups[j] == i)
            {
                printf("%s\n", arr[j]);
            }
        }
        printf("\n");
        i++;
    }
    
    printf("Exiting");

    return 0;
}

