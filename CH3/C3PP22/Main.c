#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>

int main(int argc, char const *argv[])
{
    // Check if there is input or not
    argv[1] == NULL ? exit(-1) : printf("\nCollatz conjecture of %s\n", argv[1]);

    // Make A Shared Memory
    int(*Nums)[] = mmap(
        NULL,                       // address is null
        sizeof(int),                // page size
        PROT_WRITE | PROT_READ,     // protection Write
        MAP_SHARED | MAP_ANONYMOUS, // changes will be saved and file wont be used
        -1,                         // no file discriptor
        0                           // no offset
    );

    // A Pointer To counter and its a shared memory object
    int *i = mmap(
        NULL,                       // address is null
        sizeof(int),                // page size
        PROT_WRITE | PROT_READ,     // protection Write
        MAP_SHARED | MAP_ANONYMOUS, // changes will be saved and file wont be used
        -1,                         // no file discriptor
        0                           // no offset
    );

    // make a child
    pid_t c1 = fork();

    // Child Instruction
    if (c1 == 0)
    {
        // Take input and Convert to int
        int n = atoi(argv[1]);

        // Check if n is 1 or not
        while (n != 1)
        {
            // Check if n is postive
            if (n > 0)
            {
                // Check if n is even
                if (n % 2 == 0)
                {
                    n = n / 2;
                    (*Nums)[*i] = n;
                }
                // if n is odd
                else
                {
                    n = (n * 3) + 1;
                    (*Nums)[*i] = n;
                }
            }
            // Increase Counter
            *i += 1;
        }
    }
    else
    {
        // Parent Wait For Child To finish
        wait(0);

        // Print Every Elemnt Of The Array
        for (int j = 0; j < *i; j++)
        {
            if (j == *i - 1)
            {
                printf("%i", (*Nums)[j]);
            }
            else
            {
                printf("%i,", (*Nums)[j]);
            }
        }
        printf("\n");

        // Dealocate The Shared Memory objects
        munmap(Nums, sizeof(int));
        munmap(i, sizeof(int));
    }
    return 0;
}
