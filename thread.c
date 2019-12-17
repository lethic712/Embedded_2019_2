
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <pthread.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <time.h>
#include <iostream>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include <sys/msg.h>
#include "myMessage.h" // msg 사용
#define INPUT_DEVICE_LIST "/dev/input/event5"
#include "fnd.h"
#include "led.h"
#include "colorled.h"
#include "textlcd.h"
#include "buzzer.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


#define MAX_SCALE_STEP 8
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

pthread_t thread_object_timer; //스레드 1
pthread_t thread_object_touch; //스레드 2

int A[6] = { 1,2,3,10,20,30 };;  //  A[0]= 빨강1 A[1]=빨강2 A[2]=빨강3 A[3]=파랑1 A[4]=파랑2 A[5]=파랑3 배열안에값은 무시해도됨
int F[2];  // 카드 위치 밑에가 F[0] 위에가 F[1]
int fnd1;
int fnd2;
int fnd3;
int state;  // 메인화면 state=0 / 정지화면 state=1/ 시작화면 state=2/ 게임방법 state=3  메인함수에 들어가야함
int i;
int SIZE;
int score1=0;
int score2=0;
char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
const int musicScale[MAX_SCALE_STEP] ={262, /*do*/ 294,330,349,392,440,494, /* si */ 523};
int whosend=0;//어떤 thread에서 보냈는지 



void* do_timer(){


if (msgQueue == -1)
{
printf ("msgQueueID Fault\r\n");
return -1;
}
   
    whosend=1;
    while(1){
    usleep(100*1000);
  messageTxData.messageType = 1;
    msgsnd(msgQueue, &messageTxData, sizeof(messageTxData.piggyBack), 0);
  
}
    
    usleep(100);
}

int main(void)
{
	Mat img = imread("start.jpg",  CV_LOAD_IMAGE_COLOR); //게임 메인화면 불러들임
	struct input_event stEvent;
	struct input_event ev;
	int readSize,inputIndex;
    int fd,fp;
structMyMsg messageTxData;
int msgQueue = msgget((key_t)MY_MESSAGE_ID, IPC_CREAT|0666);
	
	fnd1=0;
	fnd2=0;
	fnd3=fnd1+fnd2;
	state=0;
	
	int freIndex;
	

	while (1) {
	pwmLedInit();
	ledLibInit();
		int returnValue = 0 ;
		fp = open(INPUT_DEVICE_LIST, O_RDONLY);
		
		srand(time(NULL));
		buzzerLibInit(musicScale[freIndex-1]);
		SIZE = rand() % 6;  			//  0~5 난수 생성 
		i = (rand() % 2) + 3;  //  3~5초로 딜레이주는 난수함수 써주셈  

readSize = read(fp, &stEvent , sizeof(stEvent));
if (readSize != sizeof(stEvent))
{
continue;
}
      if ( stEvent.type == EV_KEY)
      {
		if (stEvent.code==KEY_BACK  || stEvent.code==KEY_VOLUMEDOWN || stEvent.code==KEY_VOLUMEUP || stEvent.code== KEY_HOME )
		{
			ledOnOff(0, 1);
			ledOnOff(1, 1);
			ledOnOff(2, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledOnOff(5, 1);
			ledLibExit();
		  }
	   }

        if (stEvent.code==KEY_HOME ) //홈누를시 시작화면
		{
			state = 0;
		}
		
		if (state == 0)
		{
			img = imread("start.jpg", CV_LOAD_IMAGE_COLOR); //룰 화면에서 돌아오기위해
			imshow("Halli Galli", img);
			//메인화면
			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				//게임시작 부분 터치 판별
				if (ev.code == EVENT_CODE_X && 300 < ev.value < 510)
				{
					if (ev.code == EVENT_CODE_Y && 420< ev.value < 520 )
					{
						state = 2;
					}
				}
				//게임방법 부분 터치 판별
				if (ev.code == EVENT_CODE_X && 510 < ev.value < 720)
				{
					if (ev.code == EVENT_CODE_Y && 420 < ev.value < 520)
					{
						state = 3;
					}
				}
			}
		}
		//게임방법 출력
		else if (state == 3){
			img = imread("rule.jpg", CV_LOAD_IMAGE_COLOR);
			imshow("Halli Galli", img);
			if (stEvent.code == KEY_BACK)  		//BACK 키 누를시 메인화면으로 돌아감
			{
				state = 0;
			}
		}
		else if (state == 1)
		{
			//정지화면
			img = imread("pause.jpg");
			imshow("Halli Galli", img);
			if (stEvent.code==KEY_BACK )  		//rst은 게임이 멈췄을때만 가능 
			{
				score1 = 0;
				score2 = 0;
				fnd1 = 0;
				fnd2 = 0;
			}
			else if (stEvent.code==KEY_VOLUMEUP) //볼륨업 누르면 게임 계속 진행
			{
				state = 2;
			}
		}

		else if (state == 2)
		{
        
       if(whosend==0){
            pthread_create(&thread_object_timer, NULL, do_timer, NULL);
        }
			F[0] = A[SIZE];   // 위에서 size 난수로 만들어서 들어감 
			sleep(i);
			F[1] = A[SIZE];
			sleep(i);

			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				if (ev.code == EVENT_CODE_X && 750 < ev.value < 1024)
				{
					if (ev.code == EVENT_CODE_Y && 0 < ev.value < 300)
					{
						if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
						{
							score1 = score1 + 1;
							fnd1 = fnd1 + 1;
							fndDisp(fnd3, 0);
							// 맨왼쪽과 맨오른쪽만 표시 schemetic 아마 clk을빠르게하여 반복하면 그냥표시된것처럼 보임 
							pwmSetPercent(100,1);//color_led = 0 100 0;  //사용법 보고 재작성해야 함  1초간 점등
							sleep(3);		// i때문에 3000을 줌 
						}
						else
						{
							pwmSetPercent(100,0);
						}

					}
				}
			}

			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				if (ev.code == EVENT_CODE_X && 0 < ev.value < 275)
				{
					if (ev.code == EVENT_CODE_Y && 250 < ev.value < 550)
					{
						if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
						{
							score2 = score2 + 1;
							fnd2 = fnd2 + 100000;
							fndDisp(fnd3, 0);
							pwmSetPercent(100,1);
							sleep(3);
						}
						else
						{
							pwmSetPercent(100,0);
						}
					}
				}
			}

			if (score1 == 5)
			{
				lcdtextwrite(0x20,"Player1 Win!",1);    //test_lcd 에표시
				buzzerLibOnBuz();
				sleep(1);
				 buzzerLibOffBuz();									// buzzer on 1sec
			}
			else if (score2 == 5)
			{
				lcdtextwrite(0x20,"Player2 Win!",1);
				buzzerLibOnBuz();
				sleep(1);
				 buzzerLibOffBuz();
			}
		}
		if (stEvent.code==KEY_VOLUMEDOWN )    // 정지상태로 만듬 
		{
			state = 1;
		}
		close(fp);
	}
	pthread_join(thread_object_timer, NULL);
}






