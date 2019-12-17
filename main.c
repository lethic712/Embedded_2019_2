#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <time.h>
#include <sys/msg.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "fnd.h"
#include "led.h"
#include "colorled.h"
#include "touch.h"
#include "textlcd.h"
#include "button.h"
#include "bitmap.h"
#include "libBitmap.h"
#include "./jpeg-6b/jpeglib.h"

int main()
{
	int A[6] = { 1,2,3,10,20,30 };  //  A[0]= 빨강1 A[1]=빨강2 A[2]=빨강3 A[3]=파랑1 A[4]=파랑2 A[5]=파랑3 배열안에값은 무시해도됨
	int F[2] = { 0,0 };  // 카드 위치 밑에가 F[0] 위에가 F[1]
	int fnd1 = 0;
	int fnd2 = 0;
	int fnd3 = 0;
	int state = 0;  // 메인화면 state=0 / 정지화면 state=1/ 시작화면 state=2  메인함수에 들어가야함
	int i = 0;
	int j = 0;
	int SIZE = 0;
	int score1 = 0;
	int score2 = 0;
	int CARD = 0;
	int waiting = 0;
	int count = 0;

	pwmLedInit();
	jpegInit();
	jpegWrite(98);
	lcdtextwrite(0x20, " Halli Galli", 1);
	lcdtextwrite(0x20, "", 2);

	srand(time(NULL));

	BUTTON_MSG_T msgRx;
	int ButtonMsgID = msgget((key_t)MESSAGE_ID, IPC_CREAT | 0666);
	buttonLibInit();

	TOUCH_MSG_T touchRx;
	int TouchMsgID = msgget((key_t)TOUCH_MESSAGE_ID, IPC_CREAT | 0666);
	touchLibInit();

	fndDisp(fnd3, 0);

	while (1)
	{
		SIZE = rand() % 6;  			//  0~5 난수 생성 
		i = (rand() % 2) + 3;  //  3~5초로 딜레이주는 난수함수 써주셈  
		fnd3 = fnd1 + fnd2;

		int returnButtonValue = 0;
		returnButtonValue = msgrcv(ButtonMsgID, &msgRx, sizeof(int), 0, IPC_NOWAIT);

		if ((msgRx.keyInput == KEY_BACK) || (msgRx.keyInput == KEY_VOLUMEDOWN) || (msgRx.keyInput == KEY_VOLUMEUP) || (msgRx.keyInput == KEY_HOME) || (msgRx.keyInput == KEY_SEARCH) || (msgRx.keyInput == KEY_MENU))
		{
			ledLibInit();
			ledOnOff(0, 1);
			ledOnOff(1, 1);
			ledOnOff(2, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledOnOff(5, 1);
			ledOnOff(6, 1);
			ledOnOff(7, 1);
			ledLibExit();
		}

		int returnTouchValue = 0;
		returnTouchValue = msgrcv(TouchMsgID, &touchRx, sizeof(TOUCH_MSG_T) - sizeof(long int), 0, IPC_NOWAIT);

		if (msgRx.keyInput == KEY_HOME)
		{
			state = 0;
		}
		else if (msgRx.keyInput == KEY_VOLUMEUP)
		{
			state = 2;
		}


		if (state == 0)  //메인화면
		{
			CARD = 0;
			F[0] = 0;
			F[1] = 0;
			score1 = 0;
			score2 = 0;
			fnd1 = 0;
			fnd2 = 0;
			jpegWrite(98);

			if ((touchRx.touch[0] > 330 && touchRx.touch[0] < 480) && (touchRx.touch[1] > 455 && touchRx.touch[1] < 565))  //START위치
			{
				state = 2;
			}

			if ((touchRx.touch[0] > 530 && touchRx.touch[0] < 680) && (touchRx.touch[1] > 455 && touchRx.touch[1] < 565))
			{
				jpegWrite(99);
				if (msgRx.keyInput == KEY_HOME)
				{
					state = 0;
				}
			}
		}
		else if (state == 1)
		{
			if (msgRx.keyInput == KEY_BACK)		//reset
			{
				score1 = 0;
				score2 = 0;
				fnd1 = 0;
				fnd2 = 0;
			}
		}
		else if (state == 2) // 게임 진행
		{
			F[CARD] = A[SIZE];
			jpegWrite(00);

			if (F[0] == A[0] && F[1] == 0)
			{
				jpegWrite(01);
			}
			else if (F[0] == A[1] && F[1] == 0)
			{
				jpegWrite(02);
			}
			else if (F[0] == A[2] && F[1] == 0)
			{
				jpegWrite(03);
			}
			else if (F[0] == A[3] && F[1] == 0)
			{
				jpegWrite(04);
			}
			else if (F[0] == A[4] && F[1] == 0)
			{
				jpegWrite(05);
			}
			else if (F[0] == A[5] && F[1] == 0)
			{
				jpegWrite(06);
			}

			//빨간 카드끼리  
			else if (F[0] == A[0] && F[1] == A[0])
			{
				jpegWrite(11);
			}
			else if (F[0] == A[1] && F[1] == A[0])
			{
				jpegWrite(12);
			}
			else if (F[0] == A[2] && F[1] == A[0])
			{
				jpegWrite(13);
			}
			else if (F[0] == A[0] && F[1] == A[1])
			{
				jpegWrite(21);
			}
			else if (F[0] == A[1] && F[1] == A[1])
			{
				jpegWrite(22);
			}
			else if (F[0] == A[2] && F[1] == A[1])
			{
				jpegWrite(23);
			}
			else if (F[0] == A[0] && F[1] == A[2])
			{
				jpegWrite(31);
			}
			else if (F[0] == A[1] && F[1] == A[2])
			{
				jpegWrite(32);
			}
			else if (F[0] == A[2] && F[1] == A[2])
			{
				jpegWrite(33);
			}

			// 위에 노랑 아래 빨강 
			else if (F[0] == A[3] && F[1] == A[0])
			{
				jpegWrite(14);
			}
			else if (F[0] == A[4] && F[1] == A[0])
			{
				jpegWrite(15);
			}
			else if (F[0] == A[5] && F[1] == A[0])
			{
				jpegWrite(16);
			}
			else if (F[0] == A[3] && F[1] == A[1])
			{
				jpegWrite(24);
			}
			else if (F[0] == A[4] && F[1] == A[1])
			{
				jpegWrite(25);
			}
			else if (F[0] == A[5] && F[1] == A[1])
			{
				jpegWrite(26);
			}
			else if (F[0] == A[3] && F[1] == A[2])
			{
				jpegWrite(34);
			}
			else if (F[0] == A[4] && F[1] == A[2])
			{
				jpegWrite(35);
			}
			else if (F[0] == A[5] && F[1] == A[2])
			{
				jpegWrite(36);
			}

			// 위에 빨강 아래 노랑 
			else if (F[0] == A[0] && F[1] == A[3])
			{
				jpegWrite(41);
			}
			else if (F[0] == A[1] && F[1] == A[3])
			{
				jpegWrite(42);
			}
			else if (F[0] == A[2] && F[1] == A[3])
			{
				jpegWrite(43);
			}
			else if (F[0] == A[0] && F[1] == A[4])
			{
				jpegWrite(51);
			}
			else if (F[0] == A[1] && F[1] == A[4])
			{
				jpegWrite(52);
			}
			else if (F[0] == A[2] && F[1] == A[4])
			{
				jpegWrite(53);
			}
			else if (F[0] == A[0] && F[1] == A[5])
			{
				jpegWrite(61);
			}
			else if (F[0] == A[1] && F[1] == A[5])
			{
				jpegWrite(62);
			}
			else if (F[0] == A[2] && F[1] == A[5])
			{
				jpegWrite(63);
			}

			//노랑 카드끼리 
			else if (F[0] == A[3] && F[1] == A[3])
			{
				jpegWrite(44);
			}
			else if (F[0] == A[4] && F[1] == A[3])
			{
				jpegWrite(45);
			}
			else if (F[0] == A[5] && F[1] == A[3])
			{
				jpegWrite(46);
			}
			else if (F[0] == A[3] && F[1] == A[4])
			{
				jpegWrite(54);
			}
			else if (F[0] == A[4] && F[1] == A[4])
			{
				jpegWrite(55);
			}
			else if (F[0] == A[5] && F[1] == A[4])
			{
				jpegWrite(56);
			}
			else if (F[0] == A[3] && F[1] == A[5])
			{
				jpegWrite(64);
			}
			else if (F[0] == A[4] && F[1] == A[5])
			{
				jpegWrite(65);
			}
			else if (F[0] == A[5] && F[1] == A[5])
			{
				jpegWrite(66);
			}

			if (touchRx.whoSend == 2)
			{
				if (waiting == 1)
				{
					if ((touchRx.touch[0] > 750 && touchRx.touch[0] < 1024) && (touchRx.touch[1] > 0 && touchRx.touch[1] < 300))
					{
						if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
						{
							score1 = score1 + 1;
							fnd1 = fnd1 + 1;
							fndDisp(fnd3, 0);
							// 맨왼쪽과 맨오른쪽만 표시 schemetic 아마 clk을빠르게하여 반복하면 그냥표시된것처럼 보임 
							pwmSetPercent(100, 1); // green 점등
							sleep(1);
							pwmSetPercent(0, 1);
						}
						else
						{
							pwmSetPercent(100, 0); // red 점등
							sleep(1);
							pwmSetPercent(0, 0);
						}
					}

					if ((touchRx.touch[0] > 0 && touchRx.touch[0] < 275) && (touchRx.touch[1] > 250 && touchRx.touch[1] < 550))
					{
						if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
						{
							score2 = score2 + 1;
							fnd2 = fnd2 + 100000;
							fndDisp(fnd3, 0);
							pwmSetPercent(100, 1); //green 점등
							sleep(1);
							pwmSetPercent(0, 1);
						}
						else
						{
							pwmSetPercent(100, 0); // red 점등
							sleep(1);
							pwmSetPercent(0, 0);
						}
					}
					waiting = 0;
				}
				else
				{
				}
			}
			else if (touchRx.whoSend == 1)
			{
				if (waiting == 0)
				{
					count++;
					if (count == i * 10)
					{
						count = 0;
						waiting = 1;
					}
				}
			}





		}
		if (score1 == 5)  	// player1 win
		{
			lcdtextwrite(0x20, "Player1 Win!", 1);    //test_lcd 에표시
			ledLibInit();
			ledOnOff(0, 1);
			ledOnOff(7, 1);
			ledOnOff(1, 1);
			ledOnOff(6, 1);
			ledOnOff(2, 1);
			ledOnOff(5, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledLibExit();
			state = 1;

		}
		else if (score2 == 5)  	// player2 win
		{
			lcdtextwrite(0x20, "Player2 Win!", 1);
			ledLibInit();
			ledOnOff(0, 1);
			ledOnOff(7, 1);
			ledOnOff(1, 1);
			ledOnOff(6, 1);
			ledOnOff(2, 1);
			ledOnOff(5, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledLibExit();
			state = 1;

		}
		if (CARD == 0)
		{
			j = 1;
		}
		if (CARD == 1)
		{
			j = 0;
		}
		buttonLibExit();
		touchLibExit();
	}

}







