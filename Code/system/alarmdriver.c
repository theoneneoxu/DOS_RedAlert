//alarmdriver.c
//file generated via DDL

#include <xinu.h>

#define INPUT 0
#define OUTPUT 1

//AM335x register type, not real address or offset
#define CONTROL_MODULE				0
#define GPIO_OE						1
#define GPIO_SETDATAOUT				2
#define GPIO_CLEARDATAOUT			3
#define CM_WKUP_ADC_TSC_CLKCTRL		4
#define CTRL						5
#define STEPENABLE					6
#define STEPCONFIG1					7
#define FIFO0DATA					8

uint32* getregaddr(uint32 pin_no, uint32 register_type)
{
	uint32 addr=0;
	switch (register_type) {
	case CONTROL_MODULE:
		switch (pin_no) {
		case 26:
			addr = 0x44E10828;
			break;
		case 44:
			addr = 0x44E10830;
			break;
		case 67:
			addr = 0x44E10894;
			break;
		case 68:
			addr = 0x44E10898;
			break;
		case 69:
			addr = 0x44E1089C;
			break;
		}
		break;
	case GPIO_OE:
	case GPIO_SETDATAOUT:
	case GPIO_CLEARDATAOUT:
		switch (pin_no / 32) {
		case 0:
			addr = 0x44E07000;
			break;
		case 1:
			addr = 0x4804C000;
			break;
		case 2:
			addr = 0x481AC000;
			break;
		case 3:
			addr = 0x481AE000;
			break;
		}
		switch (register_type) {
		case GPIO_OE:
			addr += 0x134;
			break;
		case GPIO_SETDATAOUT:
			addr += 0x194;
			break;
		case GPIO_CLEARDATAOUT:
			addr += 0x190;
			break;
		}
		break;
	case CM_WKUP_ADC_TSC_CLKCTRL:
		addr = 0x44E004BC;
		break;
	case CTRL:
		addr = 0x44E0D040;
		break;
	case STEPENABLE:
		addr = 0x44E0D054;
		break;
	case STEPCONFIG1:
		addr = 0x44E0D064;
		break;
	case FIFO0DATA:
		addr = 0x44E0D100;
		break;
	default:
		break;
	}
	return (uint32 *)addr;
}

bool8 gpiowrite(uint32 gpio_no, uint32 value)
{
	switch (value) {
	case 0:
		*getregaddr(gpio_no, GPIO_CLEARDATAOUT) = 1 << gpio_no % 32;
		break;
	case 1:
		*getregaddr(gpio_no, GPIO_SETDATAOUT) = 1 << gpio_no % 32;
		break;
	default:
		break;
	}
	return TRUE;
}

bool8 gpioinit(uint32 gpio_no, uint32 io_direction, uint32 default_value)
{
	switch (io_direction) {
	case INPUT:
		*getregaddr(gpio_no, CONTROL_MODULE) = 0x00000027;
		*getregaddr(gpio_no, GPIO_OE) |= 1 << gpio_no % 32;
		break;
	case OUTPUT:
		*getregaddr(gpio_no, CONTROL_MODULE) = 0x0000000F;
		*getregaddr(gpio_no, GPIO_OE) &= ~(1 << gpio_no % 32);
		gpiowrite(gpio_no, default_value);
		break;
	default:
		break;
	}
	return TRUE;
}

uint32 ainread(uint32 ain_no)
{
	return *getregaddr(ain_no, FIFO0DATA);
}

bool8 aininit(uint32 ain_no)
{
	*getregaddr(ain_no, CM_WKUP_ADC_TSC_CLKCTRL) = 0x00000002;
	*getregaddr(ain_no, CTRL) = 0x00000004;
	*getregaddr(ain_no, STEPENABLE) = 0x00000002;
	*getregaddr(ain_no, STEPCONFIG1) = ain_no << 19 | 0x00000011;
	*getregaddr(ain_no, CTRL) = 0x00000001;
	return TRUE;
}

uint32 devread(uint32 device_id)
{
	uint32 value = 0;
	switch (device_id) {
	case SENSOR_TEMP:
		value = ainread(5) * 0.044 - 50;
		break;
	default:
		break;
	}
	return value;
}

bool8 devwrite(uint32 device_id, uint32 value)
{
	switch(device_id) {
	case BUZZER:
		gpiowrite(67, value);
		break;
	case LIGHT_RED:
		gpiowrite(69, value);
		break;
	case LIGHT_GREEN:
		gpiowrite(68, value);
		break;
	default:
		break;
	}
	return TRUE;
}

bool8 devinit(uint32 device_id)
{
	switch (device_id) {
	case BUZZER:
		gpioinit(67, OUTPUT, 0);
		break;
	case LIGHT_RED:
		gpioinit(69, OUTPUT, 0);
		break;
	case LIGHT_GREEN:
		gpioinit(68, OUTPUT, 1);
		break;
	case SENSOR_TEMP:
		aininit(5);
		break;
	default:
		break;
	}
	return TRUE;
}