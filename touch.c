#include <fcntl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include "touch.h"

static pthread_t touchTh_id;
static pthread_t timerTh_id;
static int fd = 0;
static void* touchThFunc(void* arg);
static void* timerThFunc(void* arg);
static int msgID = 0;

int touchLibInit(void)
{
	fd=open (EVENT_DEVICE, O_RDONLY);
	msgID = msgget((key_t)TOUCH_MESSAGE_ID, IPC_CREAT|0666);
	pthread_create(&touchTh_id, NULL, &touchThFunc, NULL);
	pthread_create(&timerTh_id, NULL, &timerThFunc, NULL);
}

int touchLibExit(void)
{
	pthread_cancel(touchTh_id);
}

static void* timerThFunc(void* arg)
{
	TOUCH_MSG_T timerTx;
	timerTx.messageNum = 1;
	timerTx.touch[0] = 0;
	timerTx.touch[1] = 0;
	timerTx.whoSend = 1;
	
	while(1)
	{
		usleep(1000*100); // 0.1초
		msgsnd(msgID, &timerTx, sizeof(TOUCH_MSG_T)-sizeof(long int), 0);
	}
}

static void* touchThFunc(void* arg)
{
	TOUCH_MSG_T touchTx;
	touchTx.messageNum = 1;
	touchTx.whoSend = 2;
	
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
		
		msgsnd(msgID, &touchTx, sizeof(TOUCH_MSG_T)-sizeof(long int), 0);
	}
}
