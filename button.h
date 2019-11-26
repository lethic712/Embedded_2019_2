#ifndef _BUTTON_H_
#define _BUTTON_H_
int buttonLibInit(char* argv)
int buttonLibExit(void);
int probeButtonPath(char* newPath)
#define MESSAGE_ID 1122
typedef struct
{
	long int messageNum;
	int keyInput;
} BUTTON_MSG_T;
#endif _LED_H_