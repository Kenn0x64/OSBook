#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <wait.h>

long GetFileInfo(int fd_from, struct stat filestat)
{
    // Getting The File Info
    fstat(fd_from, &filestat);
    return filestat.st_size;
}

int main(int argc, char const *argv[])
{
    // Getting Arrguments
    char const *From = argv[1];
    char const *To = argv[2];

    // File Discriptor For Pipe
    int fd[2];
    // Making Pipes
    pipe(fd);

    // Open Files
    int File1 = open(From, O_RDWR);
    int File2 = open(To, O_RDWR);

    // Stat Struct
    struct stat Fileinfo;
    // Get File Size
    long size = GetFileInfo(File1, Fileinfo);

    // Buffer
    char buff[size];

    // Create Child
    int p = fork();

    // Parent Code
    if (p != 0)
    {
        // Read Form The File
        read(File1, buff, size);

        // Write Too Pipe
        write(fd[1], buff, size);

        // Wait For Child To Finish
        wait(NULL);
    }
    // Child Code
    else
    {
        // Read From Pipe
        read(fd[0], buff, size);

        // Check For File Availability
        if (File2 == -1)
        {
            File2 = creat(To, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        else if (File1 == -1)
        {
            // Checking For The Source Existence
            write(STDOUT_FILENO, "Source File Dose Not Exist!", 28);
        }

        // Write To File
        write(File2, buff, size);

        // Close File Streams
        close(File1);
        close(File2);

        return 0;
    }

    // Close File Streams
    close(File1);
    close(File2);

    return 0;
}
