

#ifndef __TEXTLCD_DRV_H__
#define __TEXTLCD_DRV_H__

int lcdtextwrite(const char *str1,const char *str2, int lineFlag);

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

#endif//  __TEXTLCD_DRV_H__
