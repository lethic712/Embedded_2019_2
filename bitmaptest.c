#include <stdio.h>
#include <stdlib.h>
#include "libBitmap.h"
#include "./jpeg-6b/jpeglib.h"
#include "bitmap.h"

int main(void)
{
	jpegInit();
	jpegWrite(1);	
}
