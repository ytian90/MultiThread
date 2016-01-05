#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    time_t start_t, end_t;
    double diff_t;
    
    printf("Starting of the program...\n");
    time(&start_t);

    printf("Sleeping for 5 seconds...\n");
    sleep(5);

    time(&end_t);
    diff_t = difftime(end_t, start_t);

    printf("Execution time = %f\n", diff_t);
    printf("Exiting of the program...\n");

    return(0);

/*
    time_t start = time()
    sleep(2);
    time_t end = time();
    double diff = difftime(start, end);

    printf("Diff: %d\n", diff);    

    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
*/
}
