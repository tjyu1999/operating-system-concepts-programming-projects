# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/proc_fs.h>
# include <asm/param.h>

# define BUFFER_SIZE 128
# define PROC_NAME "pid"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t cnt, loff_t *pos);
ssize_t proc_write(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)

static struct proc_ops proc_ops = {
    .proc_read = proc_read,
    .proc_write = proc_write
};

int proc_init(void){
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    printk(KERN_INFO "Loading Kernel Module\n");
    
    return 0;
}

void proc_exit(void){
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "Removing Kernel Module\n");
}

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t cnt, loff_t *pos){
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    struct task_struct *task = NULL;
    
    if(completed){
        completed = 0;
        return 0;
    }
    
    task = pid_task(find_vpid(), PIDTYPE_PID);
    if(task) rv = sprintf(buffer, BUFFER_SIZE, "command = [%s], pid = [%ld], state = [%ld]\n", task->comm, curr_pid, task->state);
    else printk(KERN_INFO "Invalid PID %d!", curr_pid);
    
    completed = 1;
    copy_to_user(usr_buf, buffer, rv);
    
    return rv;
}

ssize_t proc_write(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
    int rv = 0;
    char *k_mem;
    
    /* allocate kernel memory */
    k_mem = kmalloc(count, GFP_KERNEL);
    
    /* copies user space usr buf to kernel memory */
    copy_from_user(k_mem, usr_buf, count);
    k_mem[count] = '\0';
    kstrtoint(k_mem, 10, &curr_pid);
    
    /* return kernel memory */
    kfree(k_mem);
    
    return count;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Pid Module");
MODULE_AUTHOR("tjyu");
