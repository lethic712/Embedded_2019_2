#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "touch.h"

int main(int argc, char *argv[])
{	
	TOUCH_MSG_T touchRx;
	
	int msgID = msgget ((key_t)TOUCH_MESSAGE_ID, IPC_CREAT|0666);
	
	touchLibInit();
	
	while(1)
	{
		int returnTouch = 0 ;
		returnTouch = msgrcv(msgID, &touchRx, sizeof(touchRx.touch), 0 ,0);
		
			printf("X : %d\n",touchRx.touch[0]);
			printf("Y : %d\n",touchRx.touch[1]);		
	}
	
	touchLibExit();
}
