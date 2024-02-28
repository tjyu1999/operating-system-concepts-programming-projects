# include <linux/init.h>
# include <linux/jiffies.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/proc_fs.h>
# include <asm/uaccess.h>

# define BUFFER_SIZE 128
# define PROC_NAME "jiffies"

/*
 * Function prototypes
 */
static ssize_t proc_read(struct file* file, char* buffer, size_t cnt, loff_t* pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE;
    .read = proc_read;
};

static int porc_init(void){
    proc_create();
    printk();
    
    return 0;
}
