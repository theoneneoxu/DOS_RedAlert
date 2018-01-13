//flame_button_init.c

#include <xinu.h>

extern void flame_button_handler(void);

//flame button initialization
void flame_button_init(void)
{
	//set pin to input pulldown mode 7
	*(uint32 *)FLAME_BUTTON_CONTROL_MODULE = 0x00000027;
	//set pin gpio input enabled
	*(uint32 *)FLAME_BUTTON_GPIO_OE |= 1 << FLAME_BUTTON_GPIO_NO % 32;
	//set pin rising detect enabled
	*(uint32 *)FLAME_BUTTON_GPIO_RISINGDETECT |= 1 << FLAME_BUTTON_GPIO_NO % 32;
	//set pin interrupt enabled
	*(uint32 *)FLAME_BUTTON_GPIO_IRQSTATUS_SET_0 |= 1 << FLAME_BUTTON_GPIO_NO % 32;

	//add button handler to interrupt vector table
	set_evec(AM335X_GPIOINT1A_IRQ, (uint32)flame_button_handler);
}