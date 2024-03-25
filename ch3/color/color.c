# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/types.h>
# include <linux/slab.h>
# include <linux/list.h>

static LIST_HEAD(color_list);

struct color{
    int red;
    int blue;
    int green;
    struct list_head list;
};

int proc_init(void){
    struct color *violet;
    struct color *ptr;
    
    violet = kmalloc(sizeof(*violet), GFP_KERNEL);
    violet->red = 138;
    violet->blue = 43;
    violet->green = 226;
    
    INIT_LIST_HEAD(&violet->list);
    list_add_tail(&violet->list, &color_list);
    list_for_each_entry(ptr, &color_list, list){
        /* on each iteration ptr points */
        /* to the next struct color */
        printk(KERN_INFO "red: %4d\t blue: %4d\t green: %4d\n", ptr->red, ptr->blue, ptr->green);
    }
    
    printk(KERN_INFO "Loading kernel module\n");
    return 0;
}

void proc_exit(void){
    struct color *ptr;
    struct color *next;
    
    list_for_each_entry_safe(ptr, next, &color_list, list){
        /* on each iteration ptr points */
        /* to the next struct color */
        list_del(&ptr->list);
        kfree(ptr);
    } 
    
    printk(KERN_INFO "Removing kernel module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Color Module");
MODULE_AUTHOR("tjyu");
