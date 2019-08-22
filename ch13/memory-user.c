#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

void printhelp() {
    printf("usage:\n    memory-user <megabytes>\n");
    printf("\n");
    printf("where <megabytes> is the number of megabytes < 500M to malloc'd\n");
    printf("\n");
}

int main (int argc, char** argv) {
    const int LIMIT = 500;

    if (argc !=2) {
        printhelp();
        exit(0);
    }

    int MB = atoi(argv[1]);
    if (MB < 0 || MB > LIMIT) {
        printf("user entered invalid value for <megabytes> : %d\n", LIMIT);
        exit(1);
    }

    printf("pid : %d\n", getpid());
    char* leakedmem = malloc(1000000 * MB * sizeof(char));
    int N = 1000*MB;
    int i;
    while (1) {
        for (i = 0; i < N; i++) {
            leakedmem[i] += i;
        }
    }
    return 0;
}
