# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/types.h>
# include <linux/list.h>

struct color{
    int red;
    int blue;
    int green;
    struct list_head list;
};

int proc_init(void){
    printk(KERN_INFO "Loading Kernel Module\n");
    
    static LIST_HEAD(color_list);
    struct color *violet;
    
    violet = kmalloc(sizeof(*violet), GPL_KERNEL);
    violet->red = 138;
    violet->blue = 43;
    violet->green = 226;
    
    INIT_LIST_HEAD(&violet->list);
    list_add_tail(&violet->list, &color->list);
    
    struct color *ptr;
    list_for_each_entry(ptr, &color_list, list){
        /* on each iteration ptr points */
        /* to the next struct color */
        printk(KERN_INFO "red: %d\t blue: %d\t green: %d\n", ptr>red, ptr->blue, ptr->green);
    }
    
    return 0;
}

void proc_exit(void){
    static LIST_HEAD(color_list);
    struct color *ptr;
    struct color *next;
    
    list_for_each_entry_safe(ptr, next, &color_list, list){
        /* on each iteration ptr points */
        /* to the next struct color */
        list_del(&violet->list);
        kfree(violet);
    } 
    
    printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Color Module");
MODULE_AUTHOR("tjyu");