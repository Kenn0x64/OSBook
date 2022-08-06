#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    // make a child
    pid_t c1 = fork();

    // Take input and Convert to int
    int n = atoi(argv[1]);

    // Child Instruction
    if (c1 == 0)
    {
        // Check if n is 1 or not
        while (n != 1)
        {
            // Check if n is postive
            if (n > 0)
            {
                // Print The result
                printf("%i,", n);
                // Check if n is even
                if (n % 2 == 0)
                {
                    n = n / 2;
                }
                // if n is odd
                else
                {
                    n = (n * 3) + 1;
                }
            }
        }
    }
    else
    {
        // Parent Wait For Child To finish
        wait(0);
        printf("\n");
    }
    return 0;
}
