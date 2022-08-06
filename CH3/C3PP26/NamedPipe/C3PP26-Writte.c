#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    // Create The PipeFile
    if (fork() == 0)
    {
        execlp("mkfifo", "mkfifo", "pipefile", NULL);
    }
    else
    {
        // Wait For Child To Finish
        wait(NULL);
    }

    // Text
    char Text[] = "NoINput";

    // input
    scanf("%30s", Text);

    // Open PipeFile
    int d = open("pipefile", O_RDWR);

    // Open Process With Stdin
    // Open Process
    FILE *x = popen("./C3PP26-Read", "w");

    // Write To Stdin Of The Opened Process
    fwrite(Text, 1,strlen(Text), x);

    // Close The Process
    pclose(x);




    // Reading From PipeFile
    // Read From The PipeFile
    read(d, Text, strlen(Text));

    // Print The Result
    printf("%s\n", Text);

    // Close The Stream
    close(d);

    return 0;
}
