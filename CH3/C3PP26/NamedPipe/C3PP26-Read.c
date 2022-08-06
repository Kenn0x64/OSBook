#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    // Buffer
    char text[256];

    // Read From Stdin
    fgets(text, 255, stdin);

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

    // Open The Pipefile
    int d = open("pipefile", O_RDWR);

    // Write To The Pipefile
    write(d, text, 255);

    // Close The Pipefile
    close(d);

    return 0;
}
