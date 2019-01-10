#include <stdio.h>
#include <stdlib.h>
#include "lab1_IO.h"
#include <pthread.h>

struct thread_needed_info{
    pthread_t tid;
    int start;
    int end;
    int done;
};


void get_start_and_end(int s, int m, int* start, int* end){
    (*start) = s*m;
    (*end) = ((s+1) * m) -1;
}

void* thread(void* ptr){
    printf("here\n");
    struct thread_needed_info *th = (struct thread_needed_info *) ptr;

    while (1){
        printf("start=%d, end=%d\n", th->start, th->end);
    }
} 


int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("Invalid Number of Arguments\n");
        exit(0);
    }

    int p = atoi(argv[1]);

    if (p <= 0){
        printf("Invalid argument\n");
        exit(0);
    }

    int **A; int **B; int n;
    Lab1_loadinput(&A, &B, &n);

    int m = n / p;

    struct thread_needed_info threads[p];

    for (int s=0; s<p; s++){
        int start; 
        int end;
        get_start_and_end(s, m, &start, &end);
        struct thread_needed_info th;
        th.start = start;
        th.end = end;
        th.tid = -1;
        th.done = 0;
        threads[s] = th;
    }


    for (int s=0; s<p; s++){
        pthread_create(&threads[s].tid, NULL, thread, &threads[s]);
    }

    while(1){
        int all_done =1;
        for (int s=0; s<p; s++){
            if (threads[s].done == 0){
                all_done = 0;
            }
        }

        if(all_done){
            break;
        }
    }

    return 0;
}
