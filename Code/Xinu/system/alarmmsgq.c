//alarmmsgq.c

#include <xinu.h>

struct alarmmsgqentry alarmmsgqtab[NUM_ALARM_MSGQ_ENT];		//table of alarm message queue

//get an empty slot in alarm message queue table
//return index in alarm message queue table or SYSERR if no empty slot
qid16 newalarmmsgslot(void)
{
	int32 i;
	static qid16 slot = NUM_ALARM_MSGQ_HT;

	for (i = 0; i < NUM_ALARM_MSG; i++) {
		if (slot == NUM_ALARM_MSGQ_ENT) {
			slot = NUM_ALARM_MSGQ_HT;
		}
		if (alarmmsgqtab[slot].next == EMPTY) {
			return slot++;
		}
		slot++;
	}
	return SYSERR;
}

//insert alarm message before tail
//return OK if success or SYSERR if queue is full
int32 alarmmsgenq(
	struct alarmmsg *msgptr
) {
	qid16 tail, prev, slot;

	if (msgptr == NULL) {
		return SYSERR;
	}

	slot = newalarmmsgslot();
	if (slot == SYSERR) {
		return SYSERR;
	}
	tail = ALARM_MSGQ_TAIL;
	prev = alarmmsgqtab[tail].prev;

	alarmmsgqtab[prev].next = slot;
	alarmmsgqtab[tail].prev = slot;
	alarmmsgqtab[slot].next = tail;
	alarmmsgqtab[slot].prev = prev;
	memcpy(&alarmmsgqtab[slot].msg, msgptr, sizeof(struct alarmmsg));

	return OK;
}

//retrieve alarm message after head
//return OK if success or SYSERR if no message
int32 alarmmsgdeq(
	struct alarmmsg *msgptr
) {
	qid16 head, next, slot;

	if (msgptr == NULL) {
		return SYSERR;
	}

	head = ALARM_MSGQ_HEAD;
	slot = alarmmsgqtab[head].next;
	if (slot == ALARM_MSGQ_TAIL) {
		return SYSERR;
	}
	next = alarmmsgqtab[slot].next;

	alarmmsgqtab[head].next = next;
	alarmmsgqtab[next].prev = head;
	alarmmsgqtab[slot].next = EMPTY;
	alarmmsgqtab[slot].prev = EMPTY;
	memcpy(msgptr, &alarmmsgqtab[slot].msg, sizeof(struct alarmmsg));

	return OK;
}

//send an alarm message to alarm process
//return OK or SYSERR
syscall sendalarmmsg(
	struct alarmmsg *msgptr
) {
	intmask mask;

	mask = disable();
	if (msgptr == NULL) {
		restore(mask);
		return SYSERR;
	}

	if (alarmmsgenq(msgptr) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	switch (proctab[alarmpid].prstate) {
	case PR_RECV:
		ready(alarmpid);
		break;
	case PR_RECTIM:
		unsleep(alarmpid);
		ready(alarmpid);
		break;
	default:
		break;
	}

	restore(mask);
	return OK;
}

//receive an alarm message for alarm process
//return OK or SYSERR
syscall receivealarmmsg(
	struct alarmmsg *msgptr
) {
	intmask mask;

	mask = disable();
	if (msgptr == NULL) {
		restore(mask);
		return SYSERR;
	}

	while (alarmmsgdeq(msgptr) == SYSERR) {
		proctab[getpid()].prstate = PR_RECV;
		resched();
	}

	restore(mask);
	return OK;
}

//initialize alarm message queue table
void alarmmsgqinit(void)
{
	int32 i;

	alarmmsgqtab[ALARM_MSGQ_HEAD].next = ALARM_MSGQ_TAIL;
	alarmmsgqtab[ALARM_MSGQ_HEAD].prev = EMPTY;
	alarmmsgqtab[ALARM_MSGQ_TAIL].next = EMPTY;
	alarmmsgqtab[ALARM_MSGQ_TAIL].prev = ALARM_MSGQ_HEAD;
	
	for (i = NUM_ALARM_MSGQ_HT; i < NUM_ALARM_MSGQ_ENT; i++) {
		alarmmsgqtab[i].next = EMPTY;
		alarmmsgqtab[i].prev = EMPTY;
	}
}