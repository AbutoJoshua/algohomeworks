#include <stdio.h>
#include <stdlib.h>

//Linked list for the concatenated definition
struct Node1
{
    char definition[1000];
    struct Node *next;
}

//Object of word and definition linked with the linked list
struct Node
{
    char word[100];
    char definition[1000];
    struct Node1 *next;
}

//Used for array
struct trans*
{
    int flag; 
    /* flag = -1 : never been stored
	* flag = 1 : word already present
	* flag = 0 : data was present,but deleted
	*/
    Node *translate;
}

//I'll be using double hashing
int hashFunc1(int key, int max)
{
	return (key % max);
}
 
int hashFunc2(int key, int prime)
{
	return (prime - (key % prime));
}

int search(struct trans* hash_table, char *word, int *probe)
{
    int rt1 = hashFunc1(strlen(word), 5);
    int rt2 = hashFunc2(strlen(word), 13);

    int in = rt1;

    if(probe == 0)
    {
        printf("\n Hash Table is empty, cannot delete any items \n");
		return;
    }



    int cnt = 0; //counting the number of probes
    /* probing through other array elements */
	while (hash_table[in].flag != -1 ) 
    {
        probes++;
        if (hash_table[in].flag == 1  &&  hash_table[in].translate->word == word)
        {
			return in;
		}
		in = (in + rt2) % 5;
		if (in == hash1)
        {
			break;
		}
 
	}
    
    return -1;
    printf("\n Key (%d) does not exist \n", key);
}

int delete(struct trans* hash_table, char *word, int *size, int *probes)
{
    if(size == 0)
    {
        printf("\n Hash Table is empty, cannot delete any items \n");
        return;
    }

    int in = search(hash_table, word, probes);

    if(in == -1)
        return -1;

	if (hash_table[in].flag == 1  &&  hash_table[in].translate->word == word)
    {
		hash_table[in].translate = NULL;
		array[index].flag = 0;
		size--;
	    //printf("\n Key (%d) has been removed \n", key);
	    return;
	}

    //printf("\n Key (%d) does not exist \n", key);
}

void insert(char *word, char *definition, int line_cnt, struct trans* hash_table[], int *probe, int *table_stats, int *size)
{
    int rt1 = hashFunc1(strlen(word), 5);
    int rt2 = hashFunc2(strlen(word), 13);

    int in = rt1;

    if(probe == line_cnt)
    {
        printf("\n Hash Table is full, cannot insert more items \n");
		return;
    }

    /* create new data to insert */
	struct Node *new_item = (struct data*) malloc(sizeof(struct trans));
	new_item->word = word;
	new_item->definition = definition;

    int cnt = 0; //counting the number of probes
    /* probing through other array elements */
	while (hash_table[in].flag != 0) 
    {
        cnt++;
		if (hash_table[in].flag != 1 && hash_table[in].translate->word == word)
        {
			hash_table[in].translate.next->definition = definition;
			return;
		} else if(hash_table[in].flag != -1)
        {
            hash_table[in].translate = new_item;
	        hash_table[in].flag = 1;
            size++;
            table_stats[cnt-1] = table_stats[cnt-1] + cnt;
            probe = probe + cnt;
			return;
        }

		in = (in + rt2) % 5; 
		if (in == rt1)
        {
			printf("\n Add is failed \n");
			return;
		}
		printf("\n probing \n");
 
	}
    //keeping count of the probes
    table_stats[cnt] = table_stats[cnt] + cnt;
    probe = probe + cnt;

	printf("\n Key (%d) has been inserted \n", key);

}

int main(int argc, char** argv) 
{
    int line_cnt = 0;
    char f_name[100];
    //opening input file
    FILE *fptr;
    scanf("%s", f_name);
    fptr = fopen(f_name, 'r');
    
    //error handling
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    size_t len = 1000; //length of a line
    size_t read;
    //Variable to store the input lines
    char *line; 
    line = (char *)malloc(len*sizeof(char));

    while ((read = getline(&line, &len, fptr)) != -1) 
    {
        line_cnt++;
    }

    //Closing the file and avoiding memory leaks
	free(line);
	fclose(fptr);

    struct trans* hash_table[(line_cnt+1)*3]; //initializing the table

    //initializing the hashtable
    int i;
    for(i = 0; i <= ((line_cnt+1)*3); i++)
        hash_table[i]->flag = "-1";

    //reopening the file for reading again and hashing
    fptr = fopen(f_name, 'r');
    line_cnt = 0, w_len = 0;
    char *word= (char *)malloc(100*sizeof(char)); //will be used to store the word
    char *definition = (char *)malloc(1000*sizeof(char)); //will be used to store the rest of the line

    int *table_stats = (int *)malloc(101*sizeof(int));
    int *probe_stats;
    int probe = 0;
    probe_stats = &probe;
    int *size;
    int s_t = 0;
    size = &s_t;

    for(i = 0; i <= 100; i++)
    {
        table_stats[i]=0;

    }

    while(fgets(line, 1000, fptr) != EOF)
    {
        word = strtok(line, "\t"); // stores the first word of the sentence
        definition = strtok(NULL, "\0"); //stores the rest of the line

        struct trans* dummy;
        insert(word, definition, line_cnt+1, hash_table, probe_stats, table_stats, size); //hashing the word and definition

    }

    int max_probes = 1;
    for(i = 0; i <= 100; i++)
    {
        if(table_stats[i] >= max_probes)
            max_probes = i;

    }

    printf("Hash Table\n");
    printf("\taverage number of probes:\t\t%d", probe_stats/line_cnt);
    printf("\tmax_run of probes:\t\t%d",max_probes);
    printf("\ttotal Probes (for %d items): \t%d", line_cnt, probe_stats);
    printf("\titems NOT hashed (out of %d):\t\t%d",line_cnt, 0);

    printf("Probes | Count of keys")
    for(i = 0; i <= 100; i++)
    {
        printf("-------------------------------\n");
        printf("\t%d|\t%d", i+1, table_stats[i]);

    }

    printf("\n");

    free(line);
    free(dummy);
    free(table_stats);
    free(probe_stats);
    free(size);
    free(definition);
	fclose(fptr);

    printf("Enter words to look-up. Enter -1 to stop.\n");

    scanf("%s", &f_name);

    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    int cnt = 0;
    int t_probes = 0;
    while(fgets(line, 1000, fptr) != EOF)
    {
        
        probes = 0;
        char *action;
        int in;
        action = strtok(line, " "); // stores the action
        word = strtok(NULL, " "); //stores word
        definition = strok(NULL, "\0");

        if(strcomp(action, "s") == 0)
        {
            in = search(hash_table, word, probes);
            t_probes = t_probes + probes;
        } else if(strcomp(action, "d") == 0)
        {
            delete(hash_table, word, probes)
            t_probes = t_probes + probes;
        } else if(strcomp(action, "i") == 0)
        {
            insert(word,definition, line_cnt, hash_table, probe, table_stats, size);
            t_probes = t_probes + probes;
        } else if(strcomp(action, "q") == 0)
        {
            break;
        }
        cnt++;
       // insert(word, definition, line_cnt+1, hash_table, probe_stats, table_stats, size); //hashing the word and definition

    }

    printf("Average number of probes: %d", t_probes/cnt);

}
