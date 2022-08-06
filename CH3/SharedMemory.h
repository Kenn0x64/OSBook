#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <fcntl.h>

void *Shm_SYSV_Create(char *_fileName, int _NumOfBlocks, int _size, int _perm, void *__shmaddr, int _flags)
{
    // Make a Key Using ftok()
    key_t _key = ftok(_fileName, _NumOfBlocks);

    // Make A shared memorey shgment Using shmget()
    int shmid = shmget(_key, _size, _perm | IPC_CREAT);

    // Attach shared memorey bloack to address space
    return shmat(shmid, __shmaddr, _flags);
}

void Shm_SYSV_Destroy(char *_FileName, int _NumOfBlocks, int _size, int _perm)
{
    // DeAttach
    shmdt(_FileName);

    // Make a Key Using ftok()
    key_t _key = ftok(_FileName, _NumOfBlocks);

    // Make A shared memorey shgment Using shmget()
    int shmid = shmget(_key, _size, _perm | IPC_CREAT);

    // Destroy Memory Block
    shmctl(shmid, IPC_RMID, NULL);
}

void *Shm_POSIX_Create(char *FileName, int _perm, int _size)
{
    // Open A Shared Memory Object
    int fd = shm_open("Shm.txt", O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory object */
    ftruncate(fd, _size);

    printf("Remeber To Close The Opened Shared Memory Object\n");

    /* memory map the shared memory object */
    return mmap(
        NULL,                   // address is null
        _size,                  // page size
        PROT_WRITE | PROT_READ, // protection Write
        MAP_SHARED,             // changes will be saved and file wont be used
        fd,                     // file discriptor
        0                       // no offset
    );
}

void Shm_POSIX_Close(void *_Pointer, char *_FileName, int _size)
{
    // Un Map(Dealocate) The Shared Object
    munmap(_Pointer, _size);

    /* Remove shared memory segment.  */
    shm_unlink(_FileName);
    printf("This Function Dose not Close The Opened Shared Memory Object\n");
}
