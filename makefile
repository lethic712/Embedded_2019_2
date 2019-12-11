all: main.c textlcd.h textlcd.o touch.o led.h led.o fnd.h fnd.o colorled.h colorled.o buzzer.h buzzer.o button.h button.o
	arm-linux-gnueabi-gcc -c textlcd.c led.c buzzer.c fnd.c colorled.c button.c touch.c
	arm-linux-gnueabi-ar rc libMyPeri.a textlcd.o led.o colorled.o buzzer.o fnd.o button.o
	arm-linux-gnueabi-gcc -c main.c -L. -l MyPeri -o main `pkg-config --cflags --libs opencv`