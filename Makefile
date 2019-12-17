all:  bitmap.o libBitmap.o led.o button.o textlcd.o colorled.o touch.o fnd.o
	arm-linux-gnueabi-gcc -c bitmap.c libBitmap.c led.c button.c textlcd.c touch.c colorled.c fnd.c
	arm-linux-gnueabi-ar rc libMyPeri.a bitmap.o libBitmap.o led.o button.o textlcd.o colorled.o touch.o fnd.o
