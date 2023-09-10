/* Student Name: Ysabella Salas */
/* ID: 1002189535 */

/* Coding Assignment 3 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Create a function to read the file */
int ReadFileIntoArray(int argc, char *argv[], int **AP)
{
    if (argv[1] == NULL) // no file in command line
    {
        printf("File must be provided on command line...exiting\n");

        exit(0);
    }

    else // file in command line
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

/* Create a function to perform insertion sort */
void InsertionSort(int ArrayToSort[], int SizeAP)
{
    int i, j;
    int key;

    for (j = 1; j < SizeAP; j++) // iterates until last element is found
    {
        key = ArrayToSort[j];
        i = j - 1;

        while (i >= 0 && ArrayToSort[i] > key) // iterates until i is less than 0 and the element is greater than the key
        {
            ArrayToSort[i+1] = ArrayToSort[i]; // replaces element
            i--;
        }

        ArrayToSort[i + 1] = key; // replaces element with key
    }
}

/* Create a function to combine elements */
void Merge(int ArrayToMerge[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2]; // Create arrays of size n1 and n2

    for (i = 0; i < n1; i++) // iterates until last element is added to L[]
    {
        L[i] = ArrayToMerge[left+i];
    }

    for (j = 0; j < n2; j++) // iterates until last element is added to R[]
    {
        R[j] = ArrayToMerge[middle+1+j];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) // iterates until one array is completely added into ArrayToMerge[]
    {
        if (L[i] <= R[j]) // element in L[] is less than or equal to element in R[]
        {
            ArrayToMerge[k] = L[i];
            i++;
        }

        else // element in R[] is greater than element in L[]
        {
            ArrayToMerge[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) // iterates until rest of L[] is completely added to ArrayToMerge[]
    {
        ArrayToMerge[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) // iterates until rest of R[] is completely added to ArrayToMerge[]
    {
        ArrayToMerge[k] = R[j];
        j++;
        k++;
    }
}

/* Create a function to perform merge sort */
void MergeSort(int ArrayToSort[], int L, int R)
{
    if (L < R) // left index is less than right index
    {
        int M = (L + R) / 2; // calculates middle index

        MergeSort(ArrayToSort, L, M); // calls function to perform merge sort on left side of array
        MergeSort(ArrayToSort, M+1, R); // calls function to perform merge sort on right side of array
        Merge(ArrayToSort, L, M, R); // calls function to merge elements in array
    }
}

int main(int argc, char *argv[])
{
    int *AP = NULL;
    clock_t start1, end1, start2, end2;

    int elements = ReadFileIntoArray(argc, argv, &AP); // calls function to find the number of elements in array

    #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
    PrintArray(AP, elements);
    #endif

    start1 = clock(); // starts the clock time
    MergeSort(AP, 0, elements-1);
    end1 = clock(); // ends the clock time

    #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
    PrintArray(AP, elements);
    #endif
    
    free(AP); // deallocates memory

    elements = ReadFileIntoArray(argc, argv, &AP); // calls function to find the number of elements in array

    #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
    PrintArray(AP, elements);
    #endif

    start2 = clock(); // starts the clock time
    InsertionSort(AP, elements);
    end2 = clock(); // ends the clock time

    #ifdef PRINTARRAY // calls function to print array when 'PRINTARRAY' is called in command line
    PrintArray(AP, elements);
    #endif

    free(AP); // deallocates memory

    printf("Processed %d records\n", elements);
    printf("Merge Sort = %ld Tics\n", end1-start1);
    printf("Insertion Sort = %ld Tics\n", end2-start2);

    return 0;
}