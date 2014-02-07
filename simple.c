#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/list.h>


void list_task(struct task_struct* task,int i){
        struct task_struct * task_entry;
	struct list_head *list;
        int space;
	//       list_head head_children = task->children;
	if(task){
	  if(i==0){
	    printk("-- [%d] %s \n",task->pid,task->comm);
	  }else{
	    for(space=0;space<i;space++){
		printk("  ");
	    }
	    printk("\\_ [%d] %s \n",task->pid,task->comm);
	  }
	}
	
	list_for_each(list,&task->children){
	  task_entry = list_entry(list,struct task_struct, sibling);
	  list_task(task_entry,i+1);
	  }
}

int simple_init(void)
{
  printk(KERN_INFO "Loading Module\n");
  list_task(&init_task,0);
  return 0;
}

void simple_exit(void){

  printk(KERN_INFO "Removing Module\n");

}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
