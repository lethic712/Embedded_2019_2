#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "fnd.h"
#include "led.h"
#include "colorled.h"
#include "textlcd.h"
#include "buzzer.h"



#define SIZE 6
int A[SIZE] = {1,2,3, 10,20,30};  //  A[0]= 빨강1 A[1]=빨강2 A[2]=빨강3 A[3]=파랑1 A[4]=파랑2 A[5]=파랑3 배열안에값은 무시해도됨
int F[2];  // 카드 위치 밑에가 F[0] 위에가 F[1]
int score1=0; //  player1 score
int score2=0; //  player2 score
int fnd1=0;
int fnd2=0;
int fnd3=fnd1+fnd2; 
int state =0;  // 메인화면 state=0 / 정지화면 state=1/ 시작화면 state=2  메인함수에 들어가야함


int main(void)
{
int i;

while(1){


SIZE=rand()%6;  			//  카드 6장 난수함수 써주셈 
i=rand()%(2000)+3000;  //  3~5초로 딜레이주는 난수함수 써주셈  

if(KEY_BACK==1 || KEY_VOLUMEDOWN==1 || KEY_VOLUMEUP==1 ||  KEY_HOME==1)
{
ledOnOff (0,1);
ledOnOff (1,1);
ledOnOff (2,1);
ledOnOff (3,1);
ledOnOff (4,1);
ledOnOff (5,1);
}

if ( KEY_HOME==1)  
{
	state=0;
}
if (state==0)
{
	//메인화면
	if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
{
	if(ev.code == EVENT_CODE_X &&  ? <ev.value < ?)
	{
		if(ev.code == EVENT_CODE_Y && ? <ev.value < ?)
		{
			state=2;
		}
	}
}
}

else if (state==1)
{
	//정지화면
	if (KEY_BACK==1)  		//rst은 게임이 멈췄을때만 가능 
{
	score1=0;
	score2=0;
	fnd1=0;
	fnd2=0;
}
else if ( KEY_VOLUMEUP==1)
{
	state=2;
}}

else if (state==2)
{
F[0] =  A[SIZE];   // 위에서 size 난수로 만들어서 들어감 
delay(i);
F[1] =  A[SIZE];  
delay(i);

if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
{
	if(ev.code == EVENT_CODE_X &&  750 <ev.value < 1024)
	{
		if(ev.code == EVENT_CODE_Y && 0 <ev.value < 300)
		{
	if( ((F[0]==A[0] && F[1]==A[2]) || (F[1]==A[0] && F[0]==A[2]))  || ( F[0]==A[1] && F[1]==A[1] ) || ((F[0]==A[3] && F[1]==A[5]) || (F[1]==A[3] && F[0]==A[5])) || (F[0]==A[4] &&	F[1]==A[4])  )
	{
		scroe1=score1+1;
		fnd1=fnd1+1;
		fndDisp(fnd3,0); 
																// 맨왼쪽과 맨오른쪽만 표시 schemetic 아마 clk을빠르게하여 반복하면 그냥표시된것처럼 보임 
		//color_led = 0 100 0;  //사용법 보고 재작성해야 함  1초간 점등
		
		sleep(3);		// i때문에 3000을 줌 
	}
	else
	{
		//color_led = 100 0 0; 
	}
	
}}}

if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
{
	if(ev.code == EVENT_CODE_X && 0 <ev.value < 275)
	{
		if(ev.code == EVENT_CODE_Y && 250 <ev.value < 550)
		{
	if( ((F[0]==A[0] && F[1]==A[2]) || (F[1]==A[0] && F[0]==A[2]))  || ( F[0]==A[1] && F[1]==A[1] ) || ((F[0]==A[3] && F[1]==A[5]) || (F[1]==A[3] && F[0]==A[5])) || (F[0]==A[4] &&	F[1]==A[4])  )
	{
		scroe2=score2+1;
		fnd2=fnd2+100000;
		fndDisp(fnd3,0);
		//color_led = 0 100 0;  
		delay(3000);
	}
	else 
	{
		//color_led = 100 0 0; 
	}
}}}

if (score1==5 )
{
	printf(" player1 win! " );    //test_lcd 에표시
	buzzer=1;  									// buzzer on 1sec
}
else if (score2==5 )
{
	printf(" player2 win! " );
	buzzer=1;  									
}
}



if ( KEY_VOLUMEDOWN==1)    // 정지상태로 만듬 
{
	state=1;
}
}







