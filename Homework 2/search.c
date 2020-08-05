/*Joshua Abuto 1001530342*/
//CSE 2320 - 002
//gcc search.c
//Only choice 0 and 1 work, choice 2 works but doesn't carry out the search due to segfaults
// I have created print statements for debugging purposes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu()
{
    int input;
    printf("0-exit\n1-create and save random data for search.\n2-load data from file, sort array and run searches.");
    printf("\nEnter your choice: ");
    scanf("%d", &input);
    return input;
}

void sorted_arr(int arr[], int num, int *sorted[])
{
    int c, d, dummy, position;
    for (c = 0; c < (num - 1); c++)
    {
        position = c;
    
        for (d = c + 1; d < num; d++)
        {
        if (arr[position] > arr[d])
            position = d;
        }
        if (position != c)
        {
            dummy = arr[c];
            arr[c] = arr[position];
            arr[position] = dummy;
        }
    }

    for (c = 0; c < num; c++)
    {
        *sorted[c] = arr[c];
    }
    
    return;
}

void randomize(int min, int max, int num_onum, FILE *output)
{
    int num, c, n;
    for (c = 1; c <= num_onum; c++) 
    {
        n = rand() % max + 1;
        printf("\n %d   %d", c, n);
        while(n < min)
        {
            n = rand() % max + 1;
        }
        fprintf(output,"%d ", n);
    }
    printf("\n");

    return;

}

int create_save()
{
    int N, S_val, start_val, end_val;
    char filename[256];

    printf("Enter: N S start_val end_val filename(with extension):");
    scanf("%d %d %d %d %s", &N, &S_val, &start_val, &end_val, &filename);


    FILE *output;
    output = fopen(filename, "w+");
    fprintf(output,"%d %d %d %d\n", &N, &S_val, &start_val, &end_val);

    randomize(start_val, end_val, N, output);

    randomize(start_val, end_val, S_val, output);

    fclose(output);

    return;

}

int binary_i(int x, int *arr[],int l, int r)
{
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle/itself 
        if (*arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then it can only be present in left subarray 
        if (*arr[mid] > x) 
            return binary_i(x, arr, l, mid - 1); 
  
        // Else the element can only be present in right subarray 
        return binary_i(x, arr, mid + 1, r);
    }

    return -1;
}

int binary(int x, int *arr[],int l, int r, int *cnt)
{
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle/itself 
        if (*arr[mid] == x) 
            return *cnt; 
  
        // If element is smaller than mid, then it can only be present in left subarray 
        if (*arr[mid] > x)
        {
            *cnt++;
            return binary(x, arr, l, mid - 1, cnt); 
        }
            
  
        // Else the element can only be present in right subarray 
        *cnt++;
        return binary(x, arr, mid + 1, r, cnt);
    }

    return 1;
}

int interpol_i(int x, int *arr[], int l, int r)
{
    if (r >= l) 
    { 
        int mid = l + (x - *arr[l])*(r - l) / (*arr[r] - *arr[l]);
  
        // If the element is present at the middle/itself 
        if (*arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then it can only be present in left subarray 
        if (*arr[mid] > x) 
            return interpol_i(x, arr, l, mid - 1); 
  
        // Else the element can only be present in right subarray 
        return interpol_i(x, arr, mid + 1, r);
    }

    return -1;
}

int interpol(int x, int *arr[], int l, int r, int *cnt)
{

    if (r >= l) 
    { 
        int mid = l + (x - *arr[l])*(r - l) / (&arr[r] - &arr[l]);
  
        // If the element is present at the middle/itself 
        if (*arr[mid] == x)
        {
            return *cnt;
        }
            
  
        // If element is smaller than mid, then it can only be present in left subarray 
        if (*arr[mid] > x)
        {
            *cnt++;
            return interpol(x, arr, l, mid - 1, cnt);
        }
             
  
        // Else the element can only be present in right subarray 
        *cnt++;
        return interpol(x,arr, mid + 1, r, cnt);
    }

    return 1;
}

search_v(char *f_name)
{
    int N, S_val, start_val, end_val, val;
    printf("Input done");
    FILE *input = fopen(f_name, "r");
    fscanf(input,"%f %f %f %f\n", &N, &S_val, &start_val, &end_val);

    printf("Input done");

    int n_arr[N], s_arr[S_val], count = 0;
    while(count < N)
    {
        fscanf(input,"%f",&val);
        n_arr[count] = val;

        count++;
    }

    printf("while loop 1 done");

    count = 0;

    while(count < S_val)
    {
        fscanf(input,"%f",&val);
        s_arr[count] = val;

        count++;
    }
    
    printf("while loop 1 done");

    int *sorted[N];
    printf("sorted array:");
    sorted_arr(n_arr, N, sorted);
    int c;
    for (c = 0; c < N; c++)
    {
        printf("%f ", &sorted[c]);
    }
    printf("|       |       | found at index|  repetitions  |\n|      i|  value| interp| binary| interp| binary|");

    int l = 0;
    int r = N-1;
    int j,k, se, sd, avg_ir, avg_br;
    for(j=0; j < S_val; j++)
    {
        for(k=0; k < N; k++)
        {
            int *cnti = 0, *cntb = 0;
            int i_r = interpol(s_arr[j], sorted, l, r, cnti);
            int b_r = binary(s_arr[j], sorted, l, r, cntb);
            printf("|      %f|    %f|     %f|     %f|      %f|      %f|", j, s_arr[j], interpol_i(s_arr[j], sorted, l, r), binary_i(s_arr[j], sorted, l, r), i_r, b_r);
            avg_ir = avg_ir + i_r;
            avg_br = avg_br + b_r;
        }
    }

    avg_ir = avg_ir/S_val;
    avg_br = avg_br/S_val;

    printf("|    avg|       |       |       |   %d|   %d|", avg_ir, avg_br);

    fclose(input);
    
}

search_nv(char *f_name)
{
    int N, S_val, start_val, end_val, val;
    FILE *input = fopen(f_name, "r");
    fscanf(input,"%d %d %d %d\n", &N, &S_val, &start_val, &end_val);

    int n_arr[N], s_arr[S_val], count = 0;
    while(count < N)
    {
        fscanf(input,"%d",&val);
        n_arr[count] = val;

        count++;
    }

    count = 0;

    while(count < S_val)
    {
        fscanf(input,"%d",&val);
        s_arr[count] = val;

        count++;
    }
    int *sorted[N];
    sorted_arr(n_arr, N, sorted);
    printf("|       |       | found at index|  repetitions  |\n|      i|  value| interp| binary| interp| binary|");

    int l = 0;
    int r = N-1;
    int j,k, se, sd, avg_ir, avg_br;
    for(j=0; j < S_val; j++)
    {
        for(k=0; k < N; k++)
        {
            int *cnti = 0;
            int *cntb = 0;
            int i_r = interpol(s_arr[j], sorted, l, r, cnti);
            int b_r = binary(s_arr[j], sorted, l, r, cntb);
            avg_ir = avg_ir + i_r;
            avg_br = avg_br + b_r;
        }
    }

    avg_ir = avg_ir/S_val;
    avg_br = avg_br/S_val;

    printf("|    avg|       |       |       |   %d|   %d|", avg_ir, avg_br);

    fclose(input);
}

void b_i_search()
{
    int mode;
    char *f_name;
    f_name = (char *) malloc(250);

    printf("Enter: filename, mode(1-verbose, 2-not verbose): ");
    scanf("%s %f", &f_name, &mode);

    printf("After prompt searching\n");
    switch(mode)
    {
        case 1:
            printf("Verbose search");
            search_v(f_name);// this method segfaults
            break;
        case 2:
            printf("|       |       | found at index|  repetitions  |\n|      i|  value| interp| binary| interp| binary|");
            search_nv(f_name);// implies that this method segfaults too
            break;
        default:
            break;
    }
    printf("Skipped the if else and while statement that determines whether to search verbose or not\n");
    return;
}


int main()
{
    int N, S_val;
    int choice = 1;
    while(choice != 0)
    {
        
        choice = menu();
        //printf("in the while loop"); - i used this as a debuggin method and I couldn't figure why it was seg faulting even before printing this statement
        if(choice == 1)
        {
            create_save();
        } else if(choice == 2)
        {
            b_i_search();
        } else if(choice == 0)
        {
            exit(0);
        }
    }
    
    return 0;
}








