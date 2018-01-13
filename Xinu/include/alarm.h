//alarm.h

//device id for DDL generated driver
#define BUZZER			0
#define LIGHT_RED		1
#define LIGHT_GREEN		2
#define SENSOR_TEMP		3

//number of alarm devices
#define NUM_ALARM_DEVICE 4

//interrupts used for flame sensor and button
#define AM335X_GPIOINT0A_IRQ 96
#define AM335X_GPIOINT1A_IRQ 98

//flame sensor and button GPIO No
#define FLAME_SENSOR_GPIO_NO 26
#define FLAME_BUTTON_GPIO_NO 44

//flame sensor and button register address
#define FLAME_SENSOR_CONTROL_MODULE			0x44E10828
#define FLAME_SENSOR_GPIO_OE				0x44E07134
#define FLAME_SENSOR_GPIO_RISINGDETECT		0x44E07148
#define FLAME_SENSOR_GPIO_IRQSTATUS_SET_0	0x44E07034
#define FLAME_SENSOR_GPIO_IRQSTATUS_0		0x44E0702C
#define FLAME_BUTTON_CONTROL_MODULE			0x44E10830
#define FLAME_BUTTON_GPIO_OE				0x4804C134
#define FLAME_BUTTON_GPIO_RISINGDETECT		0x4804C148
#define FLAME_BUTTON_GPIO_IRQSTATUS_SET_0	0x4804C034
#define FLAME_BUTTON_GPIO_IRQSTATUS_0		0x4804C02C

#define TEMP_INTERVAL 3			//temperature message report interval in seconds

#define ALARM_DEVICE_PORT 35271
#define ALARM_SERVER_PORT 35272

//message code
#define HELLO				0x1100		//Device broadcasts to find Edge.
#define HITHERE				0x1101		//Edge replies to device HELLO Message.
#define DEVICE_ONLINE		0x1200		//Edge reports device becomes online to Cloud.
#define DEVICE_OFFLINE		0x1300		//Edge reports device becomes offline to Cloud.
#define ALARM_SENSOR		0x2100		//Device flame sensor has detected fire.
#define ALARM_BUTTON		0x2200		//Device alarm button has been pushed.
#define ALARM_NETWORK		0x2300		//Device broadcasts to other devices.
#define ALARM_DISMISSION	0x3100		//Alarm dismission command.
#define REPORT_TEMP			0x4100		//Device automatically reports temperature.Work as heartbeat Message.

#define ALARM_MSGQ_HEAD 0		//index of head of alarm message queue
#define ALARM_MSGQ_TAIL 1		//index of tail of alarm message queue

#define NUM_ALARM_MSGQ_HT 2										//number of head + tail in alarm message queue
#define NUM_ALARM_MSG 100										//number of messages in alarm message queue
#define NUM_ALARM_MSGQ_ENT (NUM_ALARM_MSGQ_HT + NUM_ALARM_MSG)	//number of entries in alarm message queue table

#define LEN_ALARM_TEXT 64	//length of alarm message text

//alarm message
struct alarmmsg {
	uint16 msgcode;					//message code
	uint32 srcip;					//source ip
	byte msgtext[LEN_ALARM_TEXT];	//message text
};

//entry of alarm message queue
struct alarmmsgqentry {
	qid16 next;				//index of next entry
	qid16 prev;				//index of previous entry
	struct alarmmsg msg;	//message
};

extern pid32 alarmpid;		//alarm process id
