//temperature.c

#include <xinu.h>

process temperature(void)
{
	struct alarmmsg msg;

	while (1) {
		msg.msgcode = REPORT_TEMP;
		msg.srcip = 0;
		sendalarmmsg(&msg);
		sleep(TEMP_INTERVAL);
	}
}
