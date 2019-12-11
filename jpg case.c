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
#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;


int A[6] = { 1,2,3,10,20,30 };  //  A[0]= 빨강1 A[1]=빨강2 A[2]=빨강3 A[3]=파랑1 A[4]=파랑2 A[5]=파랑3 배열안에값은 무시해도됨
int F[2];  // 카드 위치 밑에가 F[0] 위에가 F[1]
int score1 = 0; //  player1 score
int score2 = 0; //  player2 score
int fnd1 = 0;
int fnd2 = 0;
int fnd3 = fnd1 + fnd2;
int state = 0;  // 메인화면 state=0 / 정지화면 state=1/ 시작화면 state=2  메인함수에 들어가야함


int main(void)
{
	int i, SIZE;
  Mat img;
	pwmLedInit();
	ledLibInit();
	
	while (1) {
		
		srand(time(NULL));

		SIZE = rand() % 6;  			//  0~5 난수 생성 
		i = (rand() % 2000) + 3000;  //  3~5초로 딜레이주는 난수함수 써주셈  


		if (KEY_BACK == 1 || KEY_VOLUMEDOWN == 1 || KEY_VOLUMEUP == 1 || KEY_HOME == 1)
		{
			ledOnOff(0, 1);
			ledOnOff(1, 1);
			ledOnOff(2, 1);
			ledOnOff(3, 1);
			ledOnOff(4, 1);
			ledOnOff(5, 1);
			ledLibExit();
		}

		if (KEY_HOME == 1)
		{
			state = 0;
		}
		if (state == 0)
		{
			//메인화면
			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				if (ev.code == EVENT_CODE_X && ? < ev.value < ? )
				{
					if (ev.code == EVENT_CODE_Y && ? < ev.value < ? )
					{
						state = 2;
					}
				}
			}
		}

		else if (state == 1)
		{
			//정지화면
			if (KEY_BACK == 1)  		//rst은 게임이 멈췄을때만 가능 
			{
				score1 = 0;
				score2 = 0;
				fnd1 = 0;
				fnd2 = 0;
			}
			else if (KEY_VOLUMEUP == 1)
			{
				state = 2;
			}
		}

		else if (state == 2)
		{
			F[0] = A[SIZE];   // 위에서 size 난수로 만들어서 들어감 
			delay(i);

// 시작시 카드 한장만 띄울 때 
if(F[0]==A[0])
{
img = imread("01.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1])
{
img = imread("02.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2])
{
img = imread("03.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[3])
{
img = imread("04.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4])
{
img = imread("05.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5])
{
img = imread("06.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}

			F[1] = A[SIZE];
			delay(i);

if(F[0]==A[0] && F[1]==A[0])
{
//빨간 카드끼리  
img = imread("11.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[0])
{
img = imread("12.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[0])
{
img = imread("13.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[0] && F[1]==A[1])
{
img = imread("21.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[1])
{
img = imread("22.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[1])
{
img = imread("23.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[0] && F[1]==A[2])
{
img = imread("31.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[2])
{
img = imread("32.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[2])
{
img = imread("33.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}

// 위에 노랑 아래 빨강 
if(F[0]==A[3] && F[1]==A[0])
{
img = imread("14.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[0])
{
img = imread("15.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[0])
{
img = imread("16.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[3] && F[1]==A[1])
{
img = imread("24.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[1])
{
img = imread("25.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[1])
{
img = imread("26.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[3] && F[1]==A[2])
{
img = imread("34.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[2])
{
img = imread("35.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[2])
{
img = imread("36.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}

// 위에 빨강 아래 노랑 
if(F[0]==A[0] && F[1]==A[3])
{
img = imread("41.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[3])
{
img = imread("42.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[3])
{
img = imread("43.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[0] && F[1]==A[4])
{
img = imread("51.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[4])
{
img = imread("52.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[4])
{
img = imread("53.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[0] && F[1]==A[5])
{
img = imread("61.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[1] && F[1]==A[5])
{
img = imread("62.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[2] && F[1]==A[5])
{
img = imread("63.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}

//노랑 카드끼리 
if(F[0]==A[3] && F[1]==A[3])
{
img = imread("44.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[3])
{
img = imread("45.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[3])
{
img = imread("46.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[3] && F[1]==A[4])
{
img = imread("54.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[4])
{
img = imread("55.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[4])
{
img = imread("56.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[3] && F[1]==A[5])
{
img = imread("64.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[4] && F[1]==A[5])
{
img = imread("65.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}
if(F[0]==A[5] && F[1]==A[5])
{
img = imread("66.jpg", CV_LOAD_IMAGE_COLOR);
imshow("HaliGali", img);
waitKey(0);
return 0;
}


			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				if (ev.code == EVENT_CODE_X && 750 < ev.value < 1024)
				{
					if (ev.code == EVENT_CODE_Y && 0 < ev.value < 300)
					{
						if (((F[0] == A[0] && F[1] == A[2]) || (F[1] == A[0] && F[0] == A[2])) || (F[0] == A[1] && F[1] == A[1]) || ((F[0] == A[3] && F[1] == A[5]) || (F[1] == A[3] && F[0] == A[5])) || (F[0] == A[4] && F[1] == A[4]))
						{
							scroe1 = score1 + 1;
							fnd1 = fnd1 + 1;
							fndDisp(fnd3, 0);
							// 맨왼쪽과 맨오른쪽만 표시 schemetic 아마 clk을빠르게하여 반복하면 그냥표시된것처럼 보임 
							pwmSetPercent(100,1);//color_led = 0 100 0;  //사용법 보고 재작성해야 함  1초간 점등
							delay(3000);		// i때문에 3000을 줌 
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
							scroe2 = score2 + 1;
							fnd2 = fnd2 + 100000;
							fndDisp(fnd3, 0);
							pwmSetPercent(100,1);
							delay(3000);
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
				buzzer = 1;  									// buzzer on 1sec
			}
			else if (score2 == 5)
			{
				lcdtextwrite(0x20,"Player2 Win!",1);
				buzzer = 1;
			}
		}

		if (KEY_VOLUMEDOWN == 1)    // 정지상태로 만듬 
		{
			state = 1;
		}
	}
}







