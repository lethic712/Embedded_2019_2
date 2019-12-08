#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "colorled.h"

int pwmActiveAll(void)
{
	int fd = 0;
	fd = open ( COLOR_LED_DEV_R_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_G_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_B_ PWM_EXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	return 1;
}

int pwmInactiveAll(void)
{
	int fd = 0;
	fd = open ( COLOR_LED_DEV_R_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_G_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_B_ PWM_UNEXPORT, O_WRONLY);
	write(fd,&"0",1);
	close(fd);
	return 1;
}

int pwmSetDuty(int dutyCycle, int pwmIndex)
{
	int fd = 0;
	switch (pwmIndex)
	{
	case 0:
			fd = open ( COLOR_LED_DEV_R_ PWM_DUTY, O_WRONLY);
			break;
	case 1:
			fd = open ( COLOR_LED_DEV_G_ PWM_DUTY, O_WRONLY);
			break;
	case 2:
			fd = open ( COLOR_LED_DEV_B_ PWM_DUTY, O_WRONLY);
			break;
	default:
			break;
	}
	dprintf(fd, "%d", dutyCycle);
	close(fd);
	return 1;
}

int pwmSetPeriod(int Period, int pwmIndex)
{
	int fd = 0;
	switch (pwmIndex)
	{
	case 0:
			fd = open ( COLOR_LED_DEV_R_ PWM_PERIOD, O_WRONLY);
			break;
	case 1:
			fd = open ( COLOR_LED_DEV_G_ PWM_PERIOD, O_WRONLY);
			break;
	case 2:
			fd = open ( COLOR_LED_DEV_B_ PWM_PERIOD, O_WRONLY);
			break;
	default:
			break;
	}
	//printf ("Set pwm%d, Period:%d\r\n",pwmIndex, Period);
	dprintf(fd, "%d", Period);
	close(fd);
	return 1;
}

int pwmSetPercent(int percent, int ledColor)
{
	if ((percent < 0) || (percent > 100)){
	printf ("Wrong percent: %d\r\n",percent);
	return 0;
	}
	int duty = (100 - percent) * PWM_PERIOD_NS / 100;
	//LED Sinking.
	pwmSetDuty(duty, ledColor);
	return 0;
}

int pwmStartAll(void)
{
	int fd = 0;
	fd = open ( COLOR_LED_DEV_R_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_G_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	
	fd = open ( COLOR_LED_DEV_B_ PWM_ENABLE, O_WRONLY);
	write(fd,&"1",1);
	close(fd);
	return 1;
}

int pwmLedInit(void)
{ 	
	//Initialize
	pwmActiveAll();
	pwmSetDuty(0, 0); //R<-0
	pwmSetDuty(0, 1); //G<-0
	pwmSetDuty(0, 2); //B<-0
	pwmSetPeriod(PWM_PERIOD_NS, 0); pwmSetPeriod(PWM_PERIOD_NS, 1); pwmSetPeriod(PWM_PERIOD_NS, 2);
	pwmStartAll();
	return 0;
}





