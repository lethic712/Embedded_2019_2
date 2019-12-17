#ifndef _TOUCH_H_
#define _TOUCH_H_

int touchLibInit(void);
int touchLibExit(void);

#define EVENT_DEVICE "/dev/input/event4"

#define TOUCH_MESSAGE_ID 8282

typedef struct
{
	long int messageNum;
	int touch[2];
	int whoSend;
} TOUCH_MSG_T;

#endif// _TOUCH_H_
