#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>

int main()
{
	// Making a shared memory object
	long *SharedMemory = mmap(
		NULL,						// address is null
		sizeof(long),				// page size
		PROT_WRITE | PROT_READ,		// protection Read and Write
		MAP_SHARED | MAP_ANONYMOUS, // changes will be saved and file wont be used
		-1,							// no file discriptor
		0							// no offset
	);

	// Making a child
	pid_t p1 = fork();

	// Child code
	if (p1 == 0)
	{
		// gett current time
		*SharedMemory = clock();
		// Execute giving binary(executbale name ,process name ,args)
		execlp("ls", "lsx", "-l", NULL);
	}
	else
	{
		// parent will wait
		wait(0);
		// Print The loged time
		printf("\ntaken Time: %f Seconds\n ", (float)(clock() - *SharedMemory) / (float)1000);
	}
	return 0;
}