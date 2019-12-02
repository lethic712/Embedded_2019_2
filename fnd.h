
#ifndef __FND_DRV_H__
#define __FND_DRV_H__

#define MAX_FND_NUM			6
#define FND_DATA_BUFF_LEN	(MAX_FND_NUM + 2)

int fndDisp(int num , int dotflag)
int fndOff(void)

#define FND_DRIVER_NAME "/dev/perifnd"
#endif// __FND_DRV_H__
