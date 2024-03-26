# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/sched/signal.h>

int proc_init(void){
    printk(KERN_INFO "Loading kernel module\n");
    struct task_struct *task;
    
    for_each_process(task){
        /* on each iteration task points to the next task */
        printk(KERN_INFO "pid: %d\t pname: %s\t state: %d\n", task->pid, task->comm, task->__state);
    }
    
    return 0;
}

void proc_exit(void){
    printk(KERN_INFO "Removing kernel module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Tasks Module");
MODULE_AUTHOR("tjyu");
