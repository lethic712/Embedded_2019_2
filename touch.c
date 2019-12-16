#include <fcntl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include "touch.h"

static pthread_t touchTh_id;
static int fd = 0;
static void* touchThFunc(void* arg);
static int msgID = 0;

int touchLibInit(void)
{
	fd=open (EVENT_DEVICE, O_RDONLY);
	msgID = msgget((key_t)TOUCH_MESSAGE_ID, IPC_CREAT|0666);
	pthread_create(&touchTh_id, NULL, &touchThFunc, NULL);
}

int touchLibExit(void)
{
	pthread_cancel(touchTh_id);
}

static void* touchThFunc(void* arg)
{
	TOUCH_MSG_T touchTx;
	touchTx.messageNum = 1;
	
	struct input_event touchEvent;
	
	while (1)
	{
		read(fd, &touchEvent, sizeof(touchEvent));
		
		if (touchEvent.type == EV_ABS && (touchEvent.code == ABS_X || touchEvent.code == ABS_Y)) 
		{
			if(touchEvent.code == ABS_X)
			{  
				touchTx.touch[0]= touchEvent.value;
			 }
			else if (touchEvent.code == ABS_Y)
			{  
				touchTx.touch[1]= touchEvent.value;
			}
		}
		
		msgsnd(msgID, &touchTx, sizeof(touchTx.touch), 0);
	}
}
