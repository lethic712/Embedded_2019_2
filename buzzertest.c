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

char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
const int musicScale[MAX_SCALE_STEP] ={262, /*do*/ 294,330,349,392,440,494, /* si */ 523};


//버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것
int findBuzzerSysPath(){
DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
int ifNotFound = 1;
if (dir_info != NULL){
while (1){
struct dirent *dir_entry;
dir_entry = readdir (dir_info);
if (dir_entry == NULL) break;
if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){
ifNotFound = 0;
sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
}
}
}
printf("find %s\n",gBuzzerBaseSysDir);
return ifNotFound;
}


void doHelp(void)
{
printf("Usage:\n");
printf("buzzertest <buzzerNo> \n");
printf("buzzerNo: \n");
printf("do(1),re(2),mi(3),fa(4),sol(5),ra(6),si(7),do(8) \n");
printf("off(0)\n");
}

int main(int argc , char **argv)
{
int freIndex;
if (argc < 2 || findBuzzerSysPath() )
{
printf("Error!\n");
doHelp();
return 1;
}
freIndex = atoi(argv[1]);
printf("freIndex :%d \n",freIndex);

if ( freIndex > MAX_SCALE_STEP )
{
printf(" <buzzerNo> over range \n");
doHelp();
return 1;
}
if ( freIndex == 0)// disable
{
 buzzerLibOffBuz();
}
else
{
buzzerLibInit(musicScale[freIndex-1]);
buzzerLibOnBuz();
}
buzzerLibExit();
return 0;

}
