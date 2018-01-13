//flame_sensor_handler.c

#include <xinu.h>

void flame_sensor_handler(void)
{
	struct alarmmsg msg;

	//acknowledge the interrupt
	*(uint32 *)FLAME_SENSOR_GPIO_IRQSTATUS_0 = 1 << FLAME_SENSOR_GPIO_NO % 32;

	//send an alarm message to alarm process
	msg.msgcode = ALARM_SENSOR;
	msg.srcip = 0;
	sendalarmmsg(&msg);
}