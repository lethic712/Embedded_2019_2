#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <time.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "fnd.h"
#include "led.h"
#include "colorled.h"
#include "textlcd.h"
#include "buzzer.h"
#include "button.h"
#include "bitmap.h"
#include "libBitmap.h"
#include "./jpeg-6b/jpeglib.h"

int A[6] = { 1,2,3,10,20,30 };;  //  A[0]= 빨강1 A[1]=빨강2 A[2]=빨강3 A[3]=파랑1 A[4]=파랑2 A[5]=파랑3 배열안에값은 무시해도됨
int F[2];  // 카드 위치 밑에가 F[0] 위에가 F[1]
int fnd1 = 0;
int fnd2 = 0;
int fnd3 = 0;
int state = 0;  // 메인화면 state=0 / 정지화면 state=1/ 시작화면 state=2  메인함수에 들어가야함
int i;
int SIZE;
int score1=0, score2=0;

int main(void)
{
    int CARD=0;
    
	pwmLedInit();
	
	jpegInit();
	jpegWrite (98);
	
	ledLibInit();
	lcdtextwrite(0x02,"",1);
	lcdtextwrite(0x02,"",2);
	
	srand(time(NULL));
	
	BUTTON_MSG_T msgRx;
	int ButtonMsgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
	buttonLibInit();
	
	TOUCH_MSG_T touchRx;
	int TouchMsgID = msgget ((key_t)TOUCH_MESSAGE_ID, IPC_CREAT|0666);
	touchLibInit();
	
	while (1) 
	{
		SIZE = rand() % 6;  			//  0~5 난수 생성 
		i = (rand() % 2) + 3;  //  3~5초로 딜레이주는 난수함수 써주셈  
		
		int returnButtonValue = 0 ;
		returnButtonValue = msgrcv(ButtonMsgID, &msgRx, sizeof(int), 0 ,IPC_NOWAIT);

		if (msgRx.keyInput == KEY_BACK  || msgRx.keyInput == KEY_VOLUMEDOWN || msgRx.keyInput == KEY_VOLUMEUP || msgRx.keyInput == KEY_HOME)
		{
			ledOnOff(0, 1);
			ledOnOff(1, 1);
			ledOnOff(2, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledOnOff(5, 1);
			ledLibExit();
		}
		
		int returnTouchValue = 0 ;
		returnTouchValue = msgrcv(TouchMsgID, &touchRx, sizeof(touchRx.touch), 0 ,IPC_NOWAIT);
		
		if (state == 0)  //메인화면
		{
			jpegWrite (98);
			
			if ( (touchRx.touch[0] > 330 && touchRx.touch[0]< 480 ) && (touchRx.touch[1] > 455 && touchRx.touch[1]< 565 ) )  //START위치
			{			
				state = 2;
			}			
			if ( (touchRx.touch[0] > 530 && touchRx.touch[0]< 680 ) && (touchRx.touch[1] > 455 && touchRx.touch[1]< 565 ) )  //HOW TO PLAY위치
			{			
				jpegWrite (99);
				
				if(msgRx.keyInput == KEY_HOME)
				{
					state = 0
				}
			}			
		}
		else if (state == 2) // 게임 진행
		{
			F[CARD] = A[SIZE];   // 위에서 size 난수로 만들어서 들어감 	
			jpegWrite (00);
			
			if ( (touchRx.touch[0] > 750 && touchRx.touch[0]< 1024 ) && (touchRx.touch[1] > 0 && touchRx.touch[1]< 300 ) )
			{
				if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
				{
				score1 = score1 + 1;
				fnd1 = fnd1 + 1;
				fndDisp(fnd1+fnd2, 0);
				pwmSetPercent(100,1); // green 점등
				sleep(1);
				pwmSetPercent(0,1);
				}
				else
				{
					pwmSetPercent(100,0); // red 점등
					sleep(1);
					pwmSetPercent(0,0);
				}
			}

			if ( (touchRx.touch[0] > 0 && touchRx.touch[0]< 275 ) && (touchRx.touch[1] > 250 && touchRx.touch[1]< 550 ) )
			{	
				if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
				{
					score2 = score2 + 1;
					fnd2 = fnd2 + 100000;
					fndDisp(fnd1+fnd3, 0);
					pwmSetPercent(100,1); //green 점등
					sleep(1);							
					pwmSetPercent(0,1); 
				}
				else
				{
					pwmSetPercent(100,0); // red 점등
					sleep(1);
					pwmSetPercent(0,0); 
				}
			}		
		}
			
			
		if (score1 == 5)  	// player1 win
		{
			lcdtextwrite(0x20,"Player1 Win!",1);    //test_lcd 에표시
			jpegWrite (77);			
		}
		else if (score2 == 5)  	// player2 win
		{
			lcdtextwrite(0x20,"Player2 Win!",1);
			jpegWrite (78);
		}
					
		if(CARD == 0)
		{
			j = 1;
		}
		if(CARD == 1) 
		{
			j = 0;
		}
		
		if (msgRx.keyInput == KEY_VOLUMEDOWN )    // 정지상태로 만듬 
		{
			state = 1;
		}
	}
		
	buttonLibExit();
	touchLibExit();
}







