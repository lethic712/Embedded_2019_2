#ifndef _TOUCH_H_
#define _TOUCH_H_

int touchLibInit(void);
int touchLibExit(void);

#define EVENT_DEVICE "/dev/input/event4"

#define TOUCH_MESSAGE_ID 8282

#endif// _TOUCH_H_
