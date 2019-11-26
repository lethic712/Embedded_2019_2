#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "button.h"
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event1"

int main(int argc, char* argv[])
{
	int readSize, inputIndex;
	struct input_event stEvent;
	char PATH[200] = { 0 };

	if (probeButtonPath(PATH) == 0)
	{
		printf("ERROR! File Not Found!\r\n");
		printf("Did you insmod?\r\n");
		return 0;
	}

	buttonLibInit(PATH);

	while (1)
	{
		readSize = read(fp, &stEvent, sizeof(stEvent));
		if (readSize != sizeof(stEvent))
		{
			continue;
		}
		if (stEvent.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch (stEvent.code)
			{
			case KEY_VOLUMEUP: printf("Volume up key):"); break;
			case KEY_HOME: printf("Home key):"); break;
			case KEY_SEARCH: printf("Search key):"); break;
			case KEY_BACK: printf("Back key):"); break;
			case KEY_MENU: printf("Menu key):"); break;
			case KEY_VOLUMEDOWN:printf("Volume down key):"); break;
			}
			if (stEvent.value) printf("pressed\n");
			else printf("released\n");
		}
		else //EV_SYN
		{
			// do nothing
		}
	}
	buttonLibExit();
}