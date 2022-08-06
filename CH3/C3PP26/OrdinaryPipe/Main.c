#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <ctype.h>

int main()
{
    // A Array of file discriptor
    int _fd[2];
    // Creating A Pipe
    pipe(_fd);

    // Create A Child
    int X = fork();

    // Child Code
    if (X != 0)
    {
        // Buffer
        char Buffer[255] = "NoInput";

        // Get InPut
        scanf("%20s", Buffer);

        // Write To Pipe
        write(_fd[1], Buffer, 255);

        // Parent will wait
        wait(0);

        // read from the pipe
        read(_fd[0], Buffer, strlen(Buffer));

        // print the information
        printf("%s\n", Buffer);

        // Close the pipe
        close(_fd[0]);
        close(_fd[1]);
    }
    else
    {
        // Buffer
        char text[255];

        // Reading From Pipe
        read(_fd[0], text, 255);

        // CONVERTING UPPER CASE TO LOWER CASE
        for (int i = 0; i < 256; i++)
        {
            if (text[i] < 65 || text[i] > 123)
            {
                continue;
            }
            else if (text[i] >= 65 && text[i] <= 90)
            {
                text[i] = tolower(text[i]);
            }
            else
            {
                text[i] = toupper(text[i]);
            }
        }

        // Writing To Pipe
        write(_fd[1], text, strlen(text));

        // Closing The Pipe
        close(_fd[0]);
        close(_fd[1]);
    }
    return 0;
}
