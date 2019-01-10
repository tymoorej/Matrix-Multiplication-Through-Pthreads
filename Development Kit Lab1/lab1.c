#include <stdio.h>
#include <stdlib.h>
#include "lab1_IO.h"


int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("Invalid Number of Arguments\n");
        exit(0);
    }

    int num_of_threads = atoi(argv[1]);

    if (num_of_threads <= 0){
        printf("Invalid argument");
        exit(0);
    }

    int **A; int **B; int size;

    Lab1_loadinput(&A, &B, &size);


    return 0;
}
