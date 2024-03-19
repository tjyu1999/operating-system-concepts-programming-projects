# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/sched.h>

int proc_init(void){
    printk(KERN_INFO "Loading Kernel Module∖n");
    struct task_struct *task;
    
    for_each_proc(task){
        /* on each iteration task points to the next task */
        printk(KERN_INFO "pid: %d\t pname: %ld\t state: %d\n", task->pid, task->comm, task->state);
    }
    
    return 0;
}

void proc_exit(void){
    printk(KERN_INFO "Removing Kernel Module∖n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List Tasks Module");
MODULE_AUTHOR("tjyu");
