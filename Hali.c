#define SIZE 6
int A[SIZE] = {1,2,3, 10,20,30};  // kind of A cards 1~3 , 10~30 
int F[2];  // output
int pressed_in1=0;  //player1 btn press
int pressed_in2=0;  //plater2 btn press
int pressed_btn=0; //start button
int pressed_rst=0; //reset button
char start_box [5]="Start";
char rst_box [5] = "Reset";
int score1=0; //  player1 score
int score2=0; //  player2 score
int start=0; //game start,stop
int color_led;  	//color led
int buzzer=0;  	//buzzer
int fnd 				//fnd 처음에 0 , 0 으로 초기화  맨왼쪽이 (6'b100000)player1  맨오른쪽은 (6'b000001) player2 숫자 반대로보여야함



int main(void)
{
int i;


while(1){
printf ("%s" , box); 			//pressed_btn 위치에  항상 출력 
SIZE=rand()%10;  			// cardNum random
i=rand()%(2000)+1000;  //delay random(1~3sec)

if (start ==0 && pressed_btn==1)
{
	start =1;			//lcd화면 왼쪽에 네모버튼을  start 라 만들고 누르면 시작 그리고 글자가 stop이라고 바뀌면서 다시 stop누르면 멈춤 
	box = "Stop";
	
F[0] =  A[SIZE];   //? 
delay(i);
F[1] =  A[SIZE];  // ? 
delay(i);

////////////////조건문 /////////////////

if( pressed_in1==1)
{
	if( ((F[0]==A[0] && F[1]==A[2]) || (F[1]==A[0] && F[0]==A[2]))  || ( F[0]==A[1] && F[1]==A[1] ) || ((F[0]==A[3] && F[1]==A[5]) || (F[1]==A[3] && F[0]==A[5])) || (F[0]==A[4] &&	F[1]==A[4])  )
	{
		scroe1=score1+1;
		//fnd = fnd+1; 							//사용법 보고 재작성 왼쪽이 player1 점수,  fnd함수를 불러와 사용, +1이 아니고 변경 
																// 맨왼쪽과 맨오른쪽만 표시 schemetic 아마 clk을빠르게하여 반복하면 그냥표시된것처럼 보임 
		//color_led = 0 100 0;  //사용법 보고 재작성해야 함  1초간 점등
		
		delay(3000);		// i때문에 3000을 줌 
	}
	else 
	{
		//color_led = 100 0 0; 
	}
	
}
else if( pressed_in2==1)
{
	if( ((F[0]==A[0] && F[1]==A[2]) || (F[1]==A[0] && F[0]==A[2]))  || ( F[0]==A[1] && F[1]==A[1] ) || ((F[0]==A[3] && F[1]==A[5]) || (F[1]==A[3] && F[0]==A[5])) || (F[0]==A[4] &&	F[1]==A[4])  )
	{
		scroe2=score2+1;
		//fnd = fnd+1;					//오른쪽 반대방향으로 player2 점수 증가
		//color_led = 0 100 0;  
		delay(3000);
	}
	else 
	{
		//color_led = 100 0 0; 
	}
}

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
else if (start==1 && pressed_btn==1)
{
	start=0;
	box = "start";
	if (pressed_rst==1)  		//rst은 게임이 멈췄을때만 가능 
{
	score1=0;
	score2=0;
}
}}}



