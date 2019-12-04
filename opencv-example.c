#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
//기본 구성

//컴파일은
//g++ -o hali main.cpp `pkg-config opencv --cflags --libs`
//명령어로 실행합니다
int main(void){
Mat img;                      //이미지 저장을 위한 변수를 매트타입으로 선언

img = imread("0-hali.png", CV_LOAD_IMAGE_COLOR);
//변수에 이미지를 읽어와 대입
//그림파일은 코드와 같은 디렉토리에 존재해야합니다.
//아닐경우 세세한 디렉토리를 써줘야함.
//ex)D:\0-hali.png

imshow("HaliGali", img);
//HaliGali라는 이름의 창에 img란 변수의 내용을 띄워줌.

waitKey(0);      //바로 꺼지는 것을 방지하기위해 키입력을 대기
return 0;        //키입력될경우 꺼짐
}