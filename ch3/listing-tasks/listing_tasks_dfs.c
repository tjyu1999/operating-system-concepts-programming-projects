# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/sched.h>

void dfs(struct task_struct *init_task){
    struct task_struct *task;
    struct list_head *list;
    
    list_for_each(list, &init_task->children){
        /* task points to the next child in the list */
        task = list_entry(list, struct task_struct, sibling);
        printk(KERN_INFO "pid: %d\t pname: %s\t state: %d\n", task->pid, task->comm, task->__state);
    }
}

int proc_init(void){
    printk(KERN_INFO "Loading Kernel Module\n");
    dfs(&init_task);
    
    return 0;
}

void proc_exit(void){
    printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks DFS Module");
MODULE_AUTHOR("tjyu");
