#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/list.h>



static LIST_HEAD(birthday_list);

struct birthday{
  int day;
  int month;
  int year;
  struct list_head list;
};
int i=1;


void list_add_to_tail(struct list_head *new, struct list_head *head)
{
  head->prev->next=new;
  new->prev = head->prev;
  new->next=head;
  head->prev = new;
}

void list_delete(struct list_head *prev, struct list_head *next)
{
  next->prev = prev;
  prev->next = next;
}

int simple_init(void)
{
  

  struct birthday *p1,*p2,*p3,*p4,*p5;
  struct birthday *ptr,*f;
  struct list_head *p;
  i=1;
  printk(KERN_INFO "Loading Module\n");
  p1 = kmalloc(sizeof(*p1),GFP_KERNEL);
  p1 -> day = 20;
  p1 -> month = 7;
  p1 -> year = 1991;
  INIT_LIST_HEAD(&p1->list);
  list_add_to_tail(&p1->list, &birthday_list);

    
  p2 = kmalloc(sizeof(*p2),GFP_KERNEL);
  p2 -> day = 23;
  p2 -> month = 2;
  p2 -> year = 1961;
  INIT_LIST_HEAD(&p2->list);
  list_add_to_tail(&p2->list, &birthday_list);

  p3 = kmalloc(sizeof(*p3),GFP_KERNEL);
  p3 -> day = 10;
  p3 -> month = 11;
  p3 -> year = 1989;
  INIT_LIST_HEAD(&p3->list);
  list_add_to_tail(&p3->list, &birthday_list);

  
  p4 = kmalloc(sizeof(*p4),GFP_KERNEL);
  p4 -> day = 2;
  p4 -> month = 12;
  p4 -> year = 1999;
  INIT_LIST_HEAD(&p4->list);
  list_add_to_tail(&p4->list, &birthday_list);

  p5 = kmalloc(sizeof(*p5),GFP_KERNEL);
  p5 -> day = 14;
  p5 -> month = 9;
  p5 -> year = 2001;
  INIT_LIST_HEAD(&p5->list);
  list_add_to_tail(&p5->list, &birthday_list);

  
  list_for_each(p, &birthday_list){
    f = list_entry(p,struct birthday, list);
    printk("Birthday %d is : ",i);
    printk("day: %d, month %d, year %d\n",f->day, f-> month,f->year);
    i++;
  }

  return 0;
}

void simple_exit(void){
  struct birthday *ptr, *next;
  printk(KERN_INFO "Removing Module\n");
  list_for_each_entry_safe(ptr, next, &birthday_list,list){
    list_del(&ptr->list);
    kfree(ptr);
  }
  i=1;
  list_for_each(p, &birthday_list){
    f = list_entry(p,struct birthday, list);
    printk("Birthday %d is : ",i);
    printk("day: %d, month %d, year %d\n",f->day, f-> month,f->year);
    i++;
  }
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
