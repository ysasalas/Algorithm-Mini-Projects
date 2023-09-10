/* Student Name: Ysabella Salas */
/* ID: 1002189535 */

/* Coding Assignment 4 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Create a function to read the file */
int ReadFileIntoArray(int argc, char *argv[], int **AP)
{
    FILE *fptr;
    fptr = fopen(argv[1], "r"); // opens and reads file
    char buffer[5000000];
    int counter = 0;
    int i = 0;

    while (fgets(buffer, sizeof(buffer), fptr)) // iterates and reads each line in file
    {
        counter++;
    }
        
    fseek(fptr, 0, SEEK_SET); // moves file pointer back to the beginning
        
    *AP = malloc(counter * sizeof(int)); // dynamically allocates memory
        
    while (i < counter && fgets(buffer, sizeof(buffer), fptr)) // iterates until last element is added to array
    {
        (*AP)[i] = atoi(buffer);
        i++;
    }
        
    return counter; // number of elements in array
}

/* Create a function to print the array */
void PrintArray(int ArrayToPrint[], int SizeAP)
{
    int i;

    for (i = 0; i < SizeAP; i++) // iterates until last element is printed
    {
        printf("%d\n", ArrayToPrint[i]);
    } 

    printf("\n\n");
}

/* Create a function to swap elements in the array */
void swap(int *SwapA, int *SwapB)
{
    int temp = *SwapA;
    *SwapA = *SwapB;
    *SwapB = temp;
}

/* Create a function to divide the array */
int partition(int ArrayToSort[], int low, int high)
{
    int i = low - 1;
    int j = 0;

    #if QSM // calls function to swap middle with last element in array when 'QSM' is called in command line
    int middle = (high + low) / 2;
    swap(&ArrayToSort[middle], &ArrayToSort[high]);
    #elif QSRND // calls function to swap random with last element in array when 'QSRND' is called in command line
    int random = (rand() % (high - low + 1)) + low;
    swap(&ArrayToSort[random], &ArrayToSort[high]);
    #endif
    
    int pivot = ArrayToSort[high];

    for (j = low; j < high; j++) // iterates until element's index is equal to last element's index 
    {
        if (ArrayToSort[j] < pivot) // element is less than the pivot
        {
            i++;
            swap(&ArrayToSort[i], &ArrayToSort[j]);
        }
    }

    swap(&ArrayToSort[i+1], &ArrayToSort[high]); // final swap

    return (i + 1); // index of pivot
}

/* Create a function to perform quick sort */
void QuickSort(int ArrayToSort[], int low, int high)
{
    if (low < high) // first element's index is less than last element's index
    {
        int ndx = partition(ArrayToSort, low, high); // call function to find index of pivot

        QuickSort(ArrayToSort, low, ndx-1); // calls function to perform quick sort on left side of pivot
        QuickSort(ArrayToSort, ndx+1, high); // call function to perform quick sort on right side of pivot
    }
}

int main(int argc, char *argv[])
{
    int *AP = NULL;
    int i;
    int counter = 10;
    unsigned long sum = 0;
    int average;
    int elements;
    clock_t start, end;

    if (argv[1] == NULL) // no file in command line
    {
        printf("Number of runs not specified on command line...defaulting to 10\n");
        printf("File must be provided on command line...exiting\n");

        exit(0);
    }

    if (argv[2] == NULL) // no number in command line
    {
        printf("Number of runs not specified on command line...defaulting to 10\n");
    }
    
    else // number in command line
    {
        counter = atoi(argv[2]);
    }

    for (i = 1; i <= counter; i++) // iterates until last run of quick sort
    {
        elements = ReadFileIntoArray(argc, argv, &AP); // calls function to find the number of elements in array
            
        #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
        PrintArray(AP, elements);
        #endif

        start = clock(); // starts the clock time
        QuickSort(AP, 0, elements-1);
        end = clock(); // ends the clock time

        sum += end-start;

        printf("Run %d complete: %ld tics\n", i, end-start);
        
        #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
        PrintArray(AP, elements);
        #endif
        
        free(AP); // deallocates memory
    }
        
    average = sum / counter; // calculates average run time
        
    printf("The average run time for %d runs is %d\n\n", counter, average);
    printf("Processed %d records\n", elements);

    return 0;
}