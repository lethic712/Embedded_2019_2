#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "led.h"

void doHelp(void)
{
	printf("ledtest <hex byte> :data bit0 operation 1=>on 0=>off\n");
	printf(" ledtest 0x05 ;3th and 1th led on\n");
	printf(" ledtest 0xff ;all led on\n");
	printf(" ledtest 0x00 ;all led off\n");
}

int main(int argc , char **argv)
{
	unsigned int data = 0;
	int i;
	int tem1 = 0, tem2 = 0, tem3 = 0;
	
	if (argc < 2 )
	{
		perror(" Args number is less than 2\n");
		doHelp();
		return 1;
	}
	
	data = strtol(argv[1],NULL,16); //String을 16진수로 가정하고 integer형으로 변환
	printf("wrate data :0x%X\n", data);

	// open driver
	ledLibInit();
	
	tem1 = data;
	
	for(i = 0; i < 8; i++){
		if((tem1 % 2) == 1){
			ledOnOff (i, 1);
		}
		tem1 = tem1 / 2; 
	}
	
	ledLibExit();
	
return 0;
}
