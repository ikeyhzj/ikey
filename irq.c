#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/timer.h>

#define IRQ_NUM(n,m) n*32+m
#define IRQ_B8 gpio_to_irq(IRQ_NUM(1, 8))
#define IRQ_B16 gpio_to_irq(IRQ_NUM(1, 16))



struct timer_list hzj_timer;

 irqreturn_t hzj_irq_handler(int irqno, void *dev){

	
	mod_timer(&hzj_timer, jiffies + 5);

	return IRQ_HANDLED;
 }

 void hzj_timer_handle(unsigned long data){

	unsigned int gpiob8_status = gpio_get_value(IRQ_NUM(1, 8));
	unsigned int gpiob16_status = gpio_get_value(IRQ_NUM(1, 16));
	 if(gpiob8_status == 0){
	 	
			 printk("here b8\n");
		 } 
	 if(gpiob16_status == 0){
	 
			 printk("here b16\n");
		 }

	

 }

static int __init hzj_irq_init(void)
{

	int ret;
	//内核定时器初始化
	hzj_timer.expires = jiffies + HZ;
	hzj_timer.function = hzj_timer_handle;
	hzj_timer.data = 0;

	init_timer(&hzj_timer);

	add_timer(&hzj_timer);


	
	printk("irqno_b8 = %d, irqno_b16 = %d\n", IRQ_B8,IRQ_B16);
	
	ret = request_irq(IRQ_B8, hzj_irq_handler, IRQF_TRIGGER_RISING, "hzj", NULL);
		if(ret){
			printk("irq_b8 is error\n");
			return ret;
		}

	ret = request_irq(IRQ_B16, hzj_irq_handler, IRQF_TRIGGER_RISING, "hzj", NULL);
		if(ret){
			printk("irq_b8 is error\n");
			return ret;
		}

	return 0;
}



static void __exit hzj_irq_exit(void)
{
	free_irq(IRQ_B16, NULL);
	free_irq(IRQ_B8, NULL);
	del_timer(&hzj_timer);
}

module_init(hzj_irq_init);
module_exit(hzj_irq_exit);
MODULE_LICENSE("GPL");








































