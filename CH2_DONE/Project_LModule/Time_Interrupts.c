#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>
#include <linux/version.h>

//Run this in terminal for clean and make and insret and remove 
//make clean && make all && sudo dmesg -c
//&& sudo insmod simple.ko && sudo rmmod simple.ko

//Some Macros
#define PROC_NAME "Time_Interrupts"
#define BUFFER_SIZE 500

//Checking If The Kernal Is 5.6 or newer
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
#define HAVE_PROC_OPS
#endif


//Method Decleareation And A  Variable 
long TI_INIT; 
long Elapsed_Time;
ssize_t proc_read(struct file *file,char *usr_buf,size_t count, loff_t *pos);


//Struct for file operations
#ifdef HAVE_PROC_OPS
static struct proc_ops Proc_Ops={
    
    //proc_owner:THIS_MODULE,
    .proc_read=proc_read

};
#else
struct file_operations Proc_Ops={
    
    //Designated Initializer   
    owner:THIS_MODULE,
    .read=proc_read

};
#endif


int MY_INIT(void)
{
    //Capturing jiffes 
    TI_INIT=jiffies;
    
    //Proc Creation
    proc_create(PROC_NAME,0,NULL,&Proc_Ops);
    printk(KERN_ERR "\n\tOMG AM IN!!!!:)\n");
    return 0;
}


void MY_EXIT(void)
{
    //Proc Removal
    remove_proc_entry(PROC_NAME,NULL);
    printk(KERN_ERR "\n\tOh NO! I HAVE BEEN REMOVED!!!!:(\n\t");
}



ssize_t proc_read(struct file *file, char  *usr_buf, size_t count, loff_t *pos)
{
    //Declerations
    static int cated=0;
    long Total_TI_Since_Installed;
    int TI_Every_MilSecond;
    char *String;
    char buff[BUFFER_SIZE];
    int byte;
  

    //Assignments
    Total_TI_Since_Installed=jiffies-TI_INIT;
    TI_Every_MilSecond=1000/HZ;
    Elapsed_Time=(Total_TI_Since_Installed*TI_Every_MilSecond)/1000;
    String="Every %d Mliseconds Timer Interrupt Occur\nTime Elapsed Since This Module Was Installed Is %ld Seconds\nTotal Time Interrupts That Acoured Since System Boot Is %ld\nTotal Time Interrupts Since Module Installtion is %ld";
    
    //Making Sure We Dont Get In A loop 
    if (cated)
    { 
        cated=0;
        return 0;
    }
    
    cated=1;
    
    byte=sprintf(buff,String,TI_Every_MilSecond,Elapsed_Time,jiffies,Total_TI_Since_Installed);
    raw_copy_to_user(usr_buf,buff,byte);

    return byte;
}


//I GOT ERROR BECAUSE I DIDNT SPECIFIE A LICENSE!!!!!
MODULE_LICENSE("GPL");

module_init(MY_INIT);
module_exit(MY_EXIT);


