#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>

int main()
{
    // A Array of file discriptor
    int _fd[2];
    // Creating A Pipe
    pipe(_fd);

    // Child Code
    if (fork() == 0)
    {
        // Close reading side of the pipe
        close(_fd[0]);
        // Timestamp
        long t = clock();
        // Writing to the write part of the pipe
        write(_fd[1], &t, sizeof(long));
        // executing the binary
        execlp("ls", "lsx", "-l", NULL);
    }
    else
    {
        // Parent will wait
        wait(0);
        // close writing part of pipe
        close(_fd[1]);
        // making buffer to read into
        long t;
        // read from the pipe
        read(_fd[0], &t, sizeof(long));
        // print the information
        printf("\ntaken Time: %f Seconds\n ", (float)(clock() - t) / (float)1000);
    }
    return 0;
}
