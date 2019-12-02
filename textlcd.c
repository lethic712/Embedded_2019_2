#ifndef __TEXTLCD_DRV_H__
#define __TEXTLCD_DRV_H__

#define LINE_NUM			2
#define COLUMN_NUM			16	

#define  LINE_BUFF_NUM 	(COLUMN_NUM + 4)  // for dummy 

#define  MODE_CMD	0
#define  MODE_DATA	1

#define  CMD_DISPLAY_MODE		0x10
	#define  BIT_DISPLAY_MODE_CURSOR_DISP	0x01
	#define  BIT_DISPLAY_MODE_CURSOR_BLINK	0x02
	#define  BIT_DISPLAY_MODE_DISP_ENABLE	0x04

#define  CMD_CURSOR_MOVE_MODE	0x11
	#define CURSOR_MOVE_MODE_ENABLE		0x01
	#define CURSOR_MOVE_MODE_RIGHT_DIR	0x02

#define  CMD_CURSOR_MOVE_POSITION	0x12
	#define  CURSOR_MOVE_X_MASK		0x3F
	#define  CURSOR_MOVE_Y_MASK		0xC0
	
#define  CMD_WRITE_STRING			0x20	
	#define CMD_DATA_WRITE_BOTH_LINE	0
	#define CMD_DATA_WRITE_LINE_1		1
	#define CMD_DATA_WRITE_LINE_2		2
	
#define  CMD_TEST_GPIO_HIGH			0x30
#define  CMD_TEST_GPIO_LOW			0x31


typedef struct TextLCD_tag 
{
	unsigned char cmd; //
	unsigned char cmdData;  
	unsigned char reserved[2];
	
	char	TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;


#endif//  __TEXTLCD_DRV_H__

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
#include  "textlcd.h"
#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

int fd;
stTextLCD  stlcd; 
int len;

int lcdtextwrite(const char *str1,const char *str2, int lineFlag)
{
	if ( lineFlag == 1) // firsst line
	{
		str1= CMD_DATA_WRITE_LINE_1;
	}
	else if ( lineFlag == 2) // second line
	{
		str1 = CMD_DATA_WRITE_LINE_2;
	}
	
	else
	{
		printf("linenum : %d  wrong .  range (1 ~ 2)\n", lineFlag);
		return 1; 
	}
	printf("string:%s\n",str2);
	len = strlen(str2);
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,len);
	}
	stlcd.cmd = CMD_WRITE_STRING;
	
	fd=open(TEXTLCD_DRIVER_NAME, O_WRONLY);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
		close(fd);
}
