#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>

#define _MIN_PID 300
#define _MAX_PID 5000

// A Strcut For PIDs
struct _PID_STRUCT
{
    // Status Of a PID
    int _PID_STATUS;
    // PID IT SELF !!!!
    pid_t _PID;
};

// Public Strct
struct _PID_STRUCT _AVA_PID[500];

// Function For Initialize The Struct
int allocate_map(void)
{
    // Change the seed For the time
    srand((unsigned)time(NULL));

    // looping throgh the struct
    for (int i = 0; i < 500; i++)
    {
        // Setting a random PID for each PID in The Struct
        _AVA_PID[i]._PID = rand() % _MAX_PID;
        // Also Setting The status to 0 to indicate thats free
        _AVA_PID[i]._PID_STATUS = 0;
    }
    // Return 1 on Sucesss
    return 1;
}

// Function for Allocateing a PID
int allocate_pid(void)
{
    // Looping Throgh The Struct
    for (int i = 0; i < 500; i++)
    {
        // Checking if the status is 0
        if (_AVA_PID[i]._PID_STATUS == 0)
        {
            // If its zero Set Status to 1
            _AVA_PID[i]._PID_STATUS = 1;
            // Then Return The PID
            return _AVA_PID[i]._PID;
        }
        // If No Free PID Is Avaliable
        else if (i == 499)
        {
            // Return -1
            printf("No Free PID Is Available");
            return -1;
        }
    }
}

// Function For Releaseing a PID
void release_pid(int pid)
{
    // Loopig through the struct
    for (int i = 0; i < 500; i++)
    {
        // Finding the givin PID
        if (_AVA_PID[i]._PID == pid)
        {
            // Set status to Free or 0
            _AVA_PID[i]._PID_STATUS = 0;
            printf("PID Is Free Now!");
        }
    }
}

int main()
{
    // Init The Struct
    allocate_map();
    // Gett A PID
    int x = allocate_pid();
    // Release The PID
    release_pid(x);
    return 0;
}
