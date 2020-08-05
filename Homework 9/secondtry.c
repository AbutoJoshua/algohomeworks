#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linked_list
{
    char *data;
    struct linked_list *next;
};

struct struct_graph 
{
    int number_of_vertices;
    //char *useless;
    int **adjacencies;
};

typedef struct struct_graph * graph;

int edgeExists(graph g, int v1, int v2)
{
    return g->adjacencies[v1][v2];
}
void addEdge(graph g, int v1, int v2)
{
    g->adjacencies[v1][v2] = 1;
    g->adjacencies[v2][v1] = 1;
}

void removeEdge(graph g, int v1, int v2)
{
    g->adjacencies[v1][v2] = 0;
    g->adjacencies[v2][v1] = 0;
}

void dfs(graph g, char *arr[],int u, struct linked_list tmp)
{
    int size = g->number_of_vertices;
    int i, j;
    for(j = 0; j < size; j++)
    {
        if(g->adjacencies[u][j] == 1)
        {
            g->adjacencies[u][j] = 0;
            g->adjacencies[j][u] = 0;
            struct linked_list *copy; //
            copy.data = arr[j];
            tmp.next = copy;
            arr[j] == NULL;
            dfs(g, arr, j, tmp.next);
        }
    }
    return;
}


int main()
{
    int size, i, j;
    graph g;

    printf("Enter the number of vertices: ");
    scanf("%d", &size);
    printf("%d\n", size);
    char *str;
    g->number_of_vertices = size;
    //int matrix[size][size];
    //g->adjacencies = matrix;
    printf("Graph V: %d\n", g->number_of_vertices);
    char *arr[size];

    for(i = 0; i < size; i++)
    {
        printf("Enter vertex: ");
        scanf("%s", &str);
        printf("%s\n", str);
        arr[i] = str;
    }

    while((str = getline())!= NULL)
    {
        printf("%s\n", str);
        char *edge1 = strtok(str, " ");
        char *edge2 = strtok(NULL, "\0");
        if(strcmp(edge1, "-1") == 0)
            break;

        int v1, v2;
        for(j = 0; j < size; j++)
        {
            if(strcmp(edge1, arr[j]) == 0)
            {
                v1 = j;
            }
                

            if(strcmp(edge2, arr[j]) == 0)
            {
                v2 = j;
            }
                
        }
        addEdge(g, v1, v2);
    }

    //print matrix
    for(i=0; i < size; i++)
    {
        for(j = 0; j <size; j++)
        {
            printf("%d", g->adjacencies[i][j]);
        }
    }

    //Finding groups
    struct linked_list tmp[size];
    //tmp = (linked_list)malloc(sizeof(linked_list)*size);
    int cnt = 0;
    for(i = 0; i < size; i++)
    {
        str = arr[i];
        if(str != NULL)
        {
            tmp->data = str;
            dfs(g, arr, i, tmp[cnt]);
            cnt++;
        }
        
    }

    printf("Number of groups: %d\n", cnt);
    for(i = 0; i < cnt; i++ )
    {
        printf("Group %i\n", i+1);
        for(j = 0; j < size; j++)
        {
            while(tmp[i].next != NULL)
            {
                printf("%s\n",tmp[i].next.data);
                tmp[i].next = tmp[i].next.next;
            }
        }
    }
    printf("Exiting");

    return 0;
}




