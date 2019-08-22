#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int parentID = (int) getpid();
    int fdesc = 0;
    // open file
    //close(STDOUT_FILENO);
    //int fdesc = open("test.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    //if (fdesc < 0) { // failed to open file
    //    fprintf(stdout, "failed to open file. quitting...\n");
    //    exit(1);
    //}

    // fork
    int rc = fork();
    if (rc < 0) { // failed to fork
        fprintf(stdout, "failed to fork. quitting...\n");
        exit(1);
    }

    if (rc == 0) { // child process

        // open file
        close(STDOUT_FILENO);
        fdesc = open("test.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        if (fdesc < 0) { // failed to open file
            fprintf(stdout, "failed to open file. quitting...\n");
            exit(1);
        }

        printf("Child: fdesc = %d\n", fdesc);
    
        // see if we can write to fdesc        
        if (fdesc > 0) {
            printf("Child: writing to 'test.out'...\n");
            
            // use exec to write to file
            char *childargs[3];
            childargs[0] = strdup("echo");
            childargs[1] = strdup("CCCC");
            childargs[2] = NULL; // marks end of array

            execvp(childargs[0], childargs);
        }

    } else { // parent process
        printf("Parent: fdesc = %d\n", fdesc);
    
        // see if we can write to fdesc        
        if (fdesc > 0) {
            printf("Parent: writing to 'test.out'...\n");
            
            // use exec to write to file
            char *parentargs[3];
            parentargs[0] = strdup("echo");
            parentargs[1] = strdup("PPPP");
            parentargs[2] = NULL; // marks end of array

            execvp(parentargs[0], parentargs);
        }
    }

    return 0; 
}

