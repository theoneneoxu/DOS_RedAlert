//flame_button_handler.c

#include <xinu.h>

void flame_button_handler(void)
{
	struct alarmmsg msg;

	//acknowledge the interrupt
	*(uint32 *)FLAME_BUTTON_GPIO_IRQSTATUS_0 = 1 << FLAME_BUTTON_GPIO_NO % 32;

	//send an alarm message to alarm process
	msg.msgcode = ALARM_BUTTON;
	msg.srcip = 0;
	sendalarmmsg(&msg);
}