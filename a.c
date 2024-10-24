#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/time.h>

// fork()
// returns 0 when successed, for child
// returns -1 when crashed
// returns child process's pid for parent

// wait()
// wait until child to finish
// after it would return the child's pid.
#define wait_FAILED_SOMEHOW ((pid_t)-1)

/// @brief 
/// Left for each trees
int ID[4][3] = {
    {2, 0, 0},
    {2, 1, 0},
    {0, 0, 3},
    {0, 1, 0}
};

/// @brief 0 ~ 3
int ID_x = 0;

/// @brief 0 ~ 4
int ID_y = 0;

#define currID ID[ID_y][ID_x]


/// @brief Prints the id.
void sayID(bool asroot) {
    if(asroot) {
        sayID(0);
    }
    
    char k[4] = {0, };
    k[0] = ID_x + '0';
    k[1] = ':';
    k[2] = ID_y + '0';

    FILE* stream = asroot ? fopen(k, "a") : fopen(k, "w");

    if(asroot) {
        fprintf(stream, "Became a root\n");
        fclose(stream);
        return;
    } else {
        fprintf(stream, "This is newly made fork: \n");
    }

    fprintf(stream, "IDX: %d, IDY: %d\n", ID_x, ID_y);

    for(int i = 0; i < 5; i++) {
        fprintf(stream, "%d %d %d\n", ID[i][0], ID[i][1], ID[i][2]);
    }

    fclose(stream);
}


/// @brief 
/// @return
/// -1: done
/// 
/// 0: process root not
/// 
/// others: process root 
int subtree_Create() {
    int stackx;
    pid_t pid;
    int pidcount;
    int first = 0;

    startover:

    stackx = 0;
    int* curr = &currID;
    for(int x = 0; x < ID_x; x++) {
        stackx += ID[ID_y][x];
    }

    if(++ID_y == 4) exit(0);
    int _curr = curr[0];

    printf("_curr: %d stack: %d\n", _curr, stackx);
    for(int i = stackx; i < curr[0] + stackx;) {
        ID_x = --curr[0] + stackx;
        pid = fork();

        if(pid == -1) exit(-1);
        else if(!pid) break;
    }

    if(pid) {
        ID_y--;
        ID_x = curr - &ID[ID_y][0];
        curr[0] = _curr;
        while(wait(0) != -1);
        sayID(1);
        if(first) exit(0);
    }
    else {
        sayID(0);
        first++;
        goto startover;
    }

    return pid;
}


int main() {
    struct timeval start, end;
    double elapsedTime;

    // Start measuring time
    gettimeofday(&start, NULL);

    int isroot;

    
    isroot = subtree_Create();

    gettimeofday(&end, NULL);
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    printf("Total Execution Time: %.2f ms\n", elapsedTime);

    return 0;
}
