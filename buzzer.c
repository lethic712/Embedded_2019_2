#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

char gBuzzerBaseSysDir[128]; //sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static int fd;

int buzzerLibInit(int frequency)
{
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", frequency);
	close(fd);
}
	
	
int buzzerLibOnBuz(void)
{
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	int fd=open(path,O_WRONLY);
	write(fd, &"1", 1);
	close(fd);
}


int buzzerLibOffBuz(void)
{
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	int fd=open(path,O_WRONLY);
	write(fd, &"0", 1);
	close(fd);
}


int buzzerLibExit(void)
{
	close(fd);
}
