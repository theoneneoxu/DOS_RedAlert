//xsh_dismissalarm.c

#include <xinu.h>

shellcmd xsh_dismissalarm(int nargs, char *args[])
{
	struct alarmmsg msg;

	//For argument '--help', display help about this command
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
		printf("Use: %s address\n\n", args[0]);
		printf("Description:\n");
		printf("\tDismiss alarm\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	//Check for valid number of arguments
	if (nargs != 1)
	{
		printf("%s: no argument is allowed\n", args[0]);
		printf("Try '%s --help' for more information\n", args[0]);
		return 1;
	}

	msg.msgcode = ALARM_DISMISSION;
	msg.srcip = 0;
	sendalarmmsg(&msg);
}