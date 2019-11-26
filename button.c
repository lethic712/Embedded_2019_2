#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include ��button.h��
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl

#define  INPUT_DEVICE_LIST	"/dev/input/event"
//���� ����̽� ����̹� �������: �ڿ� ���ڰ� ����., ex)/dev/input/event5
#define PROBE_FILE	"/proc/bus/input/devices"	
static pthread_t buttonTh_id;
static int fd = 0;
static void buttonThFunc(void*);
static msgID = 0;

int probeButtonPath(char* newPath)
{
	int returnValue = 0;	//button�� �ش��ϴ� event#�� ã�ҳ�?
	int number = 0;				//ã�Ҵٸ� ���⿡ �������
	FILE* fp = fopen(PROBE_FILE, "rt");	//������ ����

#define HAVE_TO_FIND_1 	"N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2		"H: Handlers=kbd event"
	while (!feof(fp))	//���� ������ �о���δ�.
	{
		char tmpStr[200];	//200�ڸ� ���� �� �ְ� ����
		fgets(tmpStr, 200, fp);	//�ִ� 200�ڸ� �о
		//printf ("%s",tmpStr);
		if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
		{
			printf("YES! I found!: %s\r\n", tmpStr);
			returnValue = 1;	//ã��
		}
		if (
			(returnValue == 1) && 	//ã�� ���¿���
			(strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)
			//Event??�� ã������
			)
		{
			printf("-->%s", tmpStr);
			printf("\t%c\r\n", tmpStr[strlen(tmpStr) - 3]);
			number = tmpStr[strlen(tmpStr) - 3] - '0';	//Ascii character '0'-'9' (0x30-0x39) to interger(0)
			break;
		}
	}
	//�� ��Ȳ���� number���� event? �� ? �� �ش��ϴ� ���ڰ� �� �ִ�.
	fclose(fp);

	if (returnValue == 1)
		sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
	//���ڷ� ���� newPath �����Ϳ� /dev/input/event? �� ��Ʈ���� ä��
	return returnValue;
}

void buttonLibInit(char* argv)
{
	fd = open(argv, O_RDONLY);
	msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
	pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
}
int buttonLibExit(void)
{
	pthread_cancel(buttonTh_id);
}
static void buttonThFunc(void*)
{
	BUTTON_MSG_T msgTx;
	msgTx.messageNum = 1;
	struct input_event stEvent;
	while (1)
	{
		read(fd, &stEvent, sizeof(stEvent));
		if ((stEvent.type == EV_KEY) &&
			(stEvent.value == 0))
		{
			msgTx.keyInput = stEvent.code;
			msgsnd(messageID, &msgTx, sizeof(int), 0);
		}
	}
}