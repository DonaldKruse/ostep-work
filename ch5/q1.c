#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("pid %d: 'I'm the parent, x = %d'\n", (int) getpid(), x);
    int rc = fork();
    
    if (rc < 0) { // fork error; exit
        fprintf(stderr, "error with fork, quitting...\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("pid %d: 'I'm the child, x = %d'\n", (int) getpid(), x);
    } else { // parent goes down this path
        x++;
        printf("pid %d: 'I'm the parent.'", (int) getpid());
        printf("pid %d: ' x now equals %d'\n", (int) getpid(), x);
    }

    // look at new x
    if (rc == 0) { // child
        printf("pid %d: 'I'm the child, x = %d'\n", (int) getpid(), x);
        printf("pid %d: 'x = %d'\n", (int) getpid(), x);
        printf("pid %d: 'Changing x...'\n", (int) getpid());
        x++;
        printf("pid %d: 'x is %d'\n", (int) getpid(), x);
    } else { // parent
        printf("pid %d: 'I'm the parent and x = %d'\n", (int) getpid(), x);
    }
    return 0;
}

