# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/proc_fs.h>
# include <linux/jiffies.h>
# include <asm/param.h>

# define BUFFER_SIZE 128
# define PROC_NAME "seconds"

unsigned long int t = 0;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t cnt, loff_t *pos);

static struct proc_ops proc_ops = {
    .proc_read = proc_read
};

/* This function is called when the module is loaded. */
int proc_init(void){
    proc_create(PROC_NAME, 0666, NULL, &proc_ops); /* creates the /proc/seconds entry */
    printk(KERN_INFO "Loading Kernel Module\n");
    
    return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void){
    remove_proc_entry(PROC_NAME, NULL); /* removes the /proc/seconds entry */
    printk(KERN_INFO "Removing Kernel Module\n");
}

/* This function is called each time /proc/seconds is read */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t cnt, loff_t *pos){
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    
    if(completed){
        completed = 0;
        return 0;
    }
    
    completed = 1;
    rv = sprintf(buffer, "Number of elapsed seconds: %lu\n", (jiffies - t) / HZ);
    if(copy_to_user(usr_buf, buffer, rv)) return -1; /* copies kernel space buffer to user space usr_buf */
    
    return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("tjyu");
