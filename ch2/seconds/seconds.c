# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/proc_fs.h>
# include <linux/jiffies.h>
# include <asm/param.h>

# define BUFFER_SIZE 128
# define PROC_NAME "seconds"

unsigned long int t = 0;

static ssize_t proc_read(struct file *file, char *buffer, size_t cnt, loff_t *pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE;
    .read = proc_read;
};

/* This function is called when the module is loaded. */
static int porc_init(void){
    proc_create(PROC_NAME, 0666, NULL, &proc_ops); /* creates the /proc/seconds entry */
    return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(){
    remove_proc_entry(PROC_NAME, NULL); /* removes the /proc/seconds entry */
}

/* This function is called each time /proc/seconds is read */
static ssize_t proc_read(struct file *file, char *buffer, size_t cnt, loff_t *pos){
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    
    if(completed){
        completed = 0;
        return 0;
    }
    
    completed = 1;
    rv = sprintf(buffer, "Current value of jiffies: %lu\n", (jiffies - t) / HZ);
    copy_to_user(usr_buf, buffer, rv); /* copies kernel space buffer to user space usr_buf */
    
    return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("tjyu");
