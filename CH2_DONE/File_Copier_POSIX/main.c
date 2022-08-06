#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//Some Macros Because am lazy!!!!! :)
#define  Read_from argv[1]
#define  Write_to  argv[2]

//Alternative way Instead of using Write and read You can use sendfile()
//#include <sys/sendfile.h>
//sendfile(fd_to,fd_from,NULL,255);
 
long GetFileInfo(int fd_from,struct stat filestat)
{
    //Getting The File Info    
    fstat(fd_from,&filestat);
    return filestat.st_size;
}

int Read_Write(int fd_from,int fd_to,char buff[255],long st_size)
{
    //Reading From The First File 
    read(fd_from,buff,st_size)?
    //Writing To The Second file 
    write(fd_to,buff,st_size):
    write(STDOUT_FILENO,"Nothing To Write!",18);
    
    return 0;
}

int main(int argc, char const *argv[])
{
    //initialization 
    struct stat filestat;
    int fd_from,fd_to;
    char buff[255];

    
    if (Read_from==NULL | Write_to==NULL)
    {
         write(STDOUT_FILENO,"Please Pass Source And Desnation File\n",38);
        _exit(-1);
    }
    
    //Opening A Stream
    fd_from=open(Read_from,O_RDONLY);
    fd_to=open(Write_to,O_WRONLY);
    
    //Checking If The Disciptors Are -1 Or Not
    if (fd_from != -1 &&  fd_to != -1)
    {
        //Reading  From First File  And Writing To The Second File 
        Read_Write(fd_from,fd_to,buff,GetFileInfo(fd_from,filestat));
    }
    else if (fd_from==-1)
    {
        //Checking For The Source Existence 
        write(STDOUT_FILENO,"Source File Dose Not Exist!",28);
    }
    else
    {
        //Creating The File If It Dose Not Exist
        fd_to=creat(Write_to,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        //Reading  From First File  And Writing To The New File 
        Read_Write(fd_from,fd_to,buff,GetFileInfo(fd_from,filestat));
    }
        //Closeing The Stream
        close(fd_from);
        close(fd_to);
        return 0;
}
