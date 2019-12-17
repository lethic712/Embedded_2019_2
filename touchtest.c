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
	
	int count = 0, waiting = 0;
	touchLibInit();
	
	while(1)
	{
		int returnTouch = 0 ;
		returnTouch = msgrcv(msgID, &touchRx, sizeof(TOUCH_MSG_T)-sizeof(long int), 0 ,0);
			
		if (touchRx.whoSend == 2)
		{
			if(waiting == 1)
			{
				printf("X : %d\t",touchRx.touch[0]);
				printf("Y : %d\n",touchRx.touch[1]);
				printf("who : %d\n",touchRx.whoSend);
				waiting = 0;
			}
			else
			{
			}
		}
		else if(touchRx.whoSend == 1)
		{
			if(waiting == 0)
			{
				count++;
				if (count == 30)
				{
					printf("3 Sec.\n");
					count = 0;
					waiting = 1;
				}
			}
		}
	}
	
	touchLibExit();
}
