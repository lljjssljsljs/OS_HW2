#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/list.h>

struct list_head *list;
void list_task(struct task_struct* task,int i){
  	struct task_struct * task_entry;
        int space;
        //list_head head_children = task->children;
	if(list_empty(&task->children)==0){
	//if(list_empty(task)==0){
	printk("It is not empty\n");
	list_for_each(list,&task->children){
	  task_entry = list_entry(list,struct task_struct, sibling);
	  for(space=0;space<i;space++){
		printk(" ");
	  }
	  printk("\\_[%d]\n",task_entry->pid);
	  i++;
	  list_task(task_entry,i);
	}
	
        }else{
		printk("empty\n");
	}
}

int simple_init(void)
{
  //struct task_struct *task,*task2;
  //struct list_head *list2;
  //extern struct task_struct init_task = INIT_TASK(init_task);
  //EXPORT_SYMBOL(init_task);
  printk(KERN_INFO "Loading Module\n");
  list_task(&init_task,0);
  
  /*for_each_process(task){
    printk("PID is %d\n",task->pid);
    }*/
   printk("\n--------------------\n");
   /*list_for_each(list, &init_task.children){
    if(list->prev!=NULL && list->next != NULL){
      task = list_entry(list,struct task_struct, sibling);
      printk("PID is %d\n",task->pid);
      list_for_each(list2, &task->children){
	task2 = list_entry(list2,struct task_struct, sibling);
	printk("----PID is %d\n",task2->pid);

      }
    }
    }*/

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
