# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/types.h>
# include <linux/slab.h>
# include <linux/list.h>
# include <linux/moduleparam.h>

static LIST_HEAD(collatz_list);
static int start = 25;
module_param(start, int, 0);

struct collatz{
    int val;
    struct list_head list;
};

int calculation(int val){
    if(val % 2 == 0) return val / 2;
    return 3 * val + 1;
}

int proc_init(void){
    int val = start;
    struct collatz *ptr;
        
    printk(KERN_INFO "Loading Kernel Module\n");
    
    while(1){
        struct collatz *node = kmalloc(sizeof(*node), GFP_KERNEL);
        
        INIT_LIST_HEAD(&node->list);
        list_add_tail(&node->list, &collatz_list);
        node->val = val;
        
        if(val == 1) break;
        val = calculation(val);
    }
    
    list_for_each_entry(ptr, &collatz_list, list) printk(KERN_INFO "Collatz sequence value: %4d\n", ptr->val);

    return 0;
}

void proc_exit(void){
    struct collatz *ptr;
    struct collatz *next;
    
    list_for_each_entry_safe(ptr, next, &collatz_list, list){
        list_del(&ptr->list);
        kfree(ptr);
    } 
    
    printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Collatz Module");
MODULE_AUTHOR("tjyu");
