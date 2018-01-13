//communication.c

#include <xinu.h>

//convert string to hex
uint32 stringtohex(char s[])
{
	int32 i;
	uint32 n, value;

	value = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] > '9')
		{
			if (s[i] > 'F')
			{
				n = s[i] - 'a' + 10;
			}
			else
			{
				n = s[i] - 'A' + 10;
			}
		}
		else
		{
			n = s[i] - '0';
		}

		value = value << 4 | n;
	}

	return value;
}

//send network message to remote receiver
int32 sendmsg(
	uint32 ip,		//receiver ip
	uint16 port,	//receiver port
	char *text		//text to send
) {
	uint32 slot;

	slot = udp_register(0, port, ALARM_DEVICE_PORT);
	udp_sendto(slot, ip, port, text, strlen(text));
	udp_release(slot);

	return OK;
}

//receive network message from specified port
process receivemsg(void)
{
	int32 slot, retval;
	uint32 senderip, senderport;
	char buff[1500];
	struct alarmmsg msg;

	slot = udp_register(0, 0, ALARM_DEVICE_PORT);
	
	while (1)
	{
		retval = udp_recvaddr(slot, &senderip, &senderport, buff, sizeof(buff), 600000);
		if (retval == TIMEOUT || retval == SYSERR) {
			continue;
		}

		if (strlen(buff) != 4) {
			continue;
		}
		msg.msgcode = stringtohex(buff);
		msg.srcip = senderip;
		sendalarmmsg(&msg);
	}
}

