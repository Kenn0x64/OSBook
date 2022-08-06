#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/mman.h>

#define MaxLength 10000

//Function For Getting The Arguments
void GetArgs(char *_string, char *File,char * Args[10])
{
    //Getting File Name
    //Cut The String Until First Space
    //char 
    *File=*strtok(_string, " ");

    //Counter
    int i = 0;

    //The Loop Will Fail IF The First Eleement is empty
    Args[i] = File;
    printf("File is:%p\n Args[0] is:%p ",File,Args[i]);

    //Do Same Thing Untill We Reach End
    while (Args[i - 1] != NULL)
    {
        //Continue Cut Form Where Left Off
        Args[i] = strtok(NULL, " ");
        i++;
    }
    //return File;
}


int main()
{
    //Array Of Pointers
    char  * Args[10];

    //Sheard Memory Object For Input
    char *input = mmap(
        NULL,                       // address is null
        MaxLength,                  // page size
        PROT_WRITE | PROT_READ,     // protection Read and Write
        MAP_SHARED | MAP_ANONYMOUS, // changes will be saved and file wont be used
        -1,                         // no file discriptor
        0                           // no offset
    );

    //FIle Name
    char *exe = mmap(
        NULL,                       // address is null
        100 * sizeof(char),         // page size
        PROT_WRITE | PROT_READ,     // protection Read and Write
        MAP_SHARED | MAP_ANONYMOUS, // changes will be saved and file wont be used
        -1,                         // no file discriptor
        0                           // no offset
    );

    // do
    // {
    //     //Printing Label
    //     printf("\nOsh>");
    //     //Clear The Stdout
    //     fflush(stdout);
    //     //Reading From Stdin(keybord)
    //     fgets(input, MaxLength, stdin);
    //     //Extracting The Arguments
    //     exe =GetArgs(input,Args);

    //     // pid_t pid = fork();
    //     // if (pid != 0)
    //     // {

    //     //     //make a child-mmap objects
    //     //     //execute comand
    //     //     wait(NULL);
    //     // }
    //     // else if (pid == 0)
    //     // {
    //     //     execvp(exe, Args);
    //     // }

    // } while (strcmp(input, "exit"));

    //Reading From Stdin(keybord)
    fgets(input, MaxLength, stdin);
    //Extracting The Arguments
    // exe =
    GetArgs(input,exe,Args);
    

    //  pid_t pid = ;
    if (fork()== 0)
    {
        //execlp("ls", "lsx", Args[0],Args[1]);
        //Connat Use it cus not same arguments 
        //execvp("ls",Args);
    }
    else 
    {
        printf("EXE:%s",exe);
        for (int i = 0; i < sizeof(Args); i++)
        {
            printf("%s",Args[i]);
        }
        
        //execute comand
        wait(NULL);
    }

    return 0;
}
