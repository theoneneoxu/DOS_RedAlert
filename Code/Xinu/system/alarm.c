//alarm.c

#include <xinu.h>

extern syscall receivealarmmsg(struct alarmmsg *);
extern void alarmmsgqinit(void);
extern void flame_sensor_init(void);
extern void flame_button_init(void);

pid32 alarmpid;			//alarm process id
uint32 alarmserverip;	//ip of alarm server

//alarm process
process alarmproc(void)
{
	struct alarmmsg msg;
	char msgtext[LEN_ALARM_TEXT];

	while (1) {
		//receive an alarm message 
		receivealarmmsg(&msg);

		if (alarmserverip == 0) {
			//broadcast HELLO to find server
			sprintf(msgtext, "%04X", HELLO);
			sendmsg(IP_BCAST, ALARM_SERVER_PORT, msgtext);
		}

		switch (msg.msgcode) {
		case HITHERE:
			//update server ip
			alarmserverip = msg.srcip;
			break;
		case ALARM_SENSOR:
		case ALARM_BUTTON:
			//turn off green light; turn on red light and buzzer
			devwrite(LIGHT_GREEN, 0);
			devwrite(LIGHT_RED, 1);
			devwrite(BUZZER, 1);
			//broadcast ALARM_NETWORK to other devices
			sprintf(msgtext, "%04X", ALARM_NETWORK);
			sendmsg(IP_BCAST, ALARM_DEVICE_PORT, msgtext);
			//send corresponding message code to server
			sprintf(msgtext, "%04X", msg.msgcode);
			sendmsg(alarmserverip, ALARM_SERVER_PORT, msgtext);
			break;
		case ALARM_NETWORK:
			//turn off green light; turn on red light and buzzer
			devwrite(LIGHT_GREEN, 0);
			devwrite(LIGHT_RED, 1);
			devwrite(BUZZER, 1);
			break;
		case ALARM_DISMISSION:
			//turn on green light; turn off red light and buzzer
			devwrite(LIGHT_GREEN, 1);
			devwrite(LIGHT_RED, 0);
			devwrite(BUZZER, 0);
			break;
		case REPORT_TEMP:
			//send REPORT_TEMP and temperature to server
			sprintf(msgtext, "%04X|%d", REPORT_TEMP, devread(SENSOR_TEMP));
			sendmsg(alarmserverip, ALARM_SERVER_PORT, msgtext);
			break;
		default:
			break;
		}
	}
}

//initialize alarm module
void alarminit(void)
{
	int32 i;

	//initialize alarm message queue
	alarmmsgqinit();

	//initialize flame sensor and button
	flame_sensor_init();
	flame_button_init();

	//initialize alarm devices
	for (i = 0; i < NUM_ALARM_DEVICE; i++) {
		devinit(i);
	}

	//create alarm process before interrupt is enabled
	alarmpid = create(alarmproc, INITSTK, 100, "Alarm Process", 0, NULL);
	resume(alarmpid);
}
