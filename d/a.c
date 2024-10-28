#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> // for fork, pids, things
#include <time.h>   // for time getting
#include <wait.h>   // for... wait().

int nroot = 0;

/// @brief 
/// @param name 
/// give process a nickname
/// 
/// execute the fork().
///
/// prints to stdout as tagname, pid(current), pid(parent for current).
/// @return
/// zero if current is child.
/// otherwise will be parent.
pid_t mkproc(const char *name) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed\n");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("%s: %d => %d\n", name, getppid(), getpid());
        nroot = 1;
    }

    return pid; 
}

/// @brief 
/// Waits them all.  
///
/// if it is not root, process will be terminated.  
///
/// for beginner's safety.
void waitall() {
    while(wait(0) != -1);
    if(nroot) return exit(0);
}

/// @brief
/// just making left subtree
void LST() {
    if(!mkproc("LST")) {
        mkproc("LST1") && mkproc("RST1");
    }

    waitall();
}

/// @brief 
/// just making right subtree
void RST() {
    if(mkproc("RST")) goto end;
    if(mkproc("LST2")) goto end;
    if(!mkproc("NODE0")) goto end;
    
    mkproc("NODE1") ? mkproc("NODE2") : mkproc("NODETAIL");

    end:
    waitall();
}

#define NS_TO_MS 1000000.0

int main() {
    struct timespec start, end;
    double elapsed;

    timespec_get(&start, TIME_UTC);

    printf("Process start, ROOT: %d\n", getpid());
    LST(); RST();

    timespec_get(&end, TIME_UTC);
    printf("Process end, time: %lf (ms)\n", (double)(end.tv_nsec - start.tv_nsec) / NS_TO_MS);

    return 0;
}
