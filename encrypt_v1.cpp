//
//  Калькулятор nlock-кодов для модемов Huawei 
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления флеш-кодов
//
#include <openssl/md5.h>
#include "encrypt.h"

void encrypt_v1(char* imei, char* resbuf,char* hstr) {
  
unsigned char xbytes[17];
char ybytes[100];
char hash[100];
unsigned int rh[30];
unsigned char res[4];

int i;

memset(xbytes,0,17);
MD5((unsigned char*)hstr,strlen(hstr),xbytes);

//printf("\n xbytes (1) =\n");
//for(i=0;i<16;i++) printf(" %02x",xbytes[i]&0xff);
for(i=0;i<16;i++) sprintf(ybytes+(i*2),"%02x",xbytes[i]&0xff);

strcpy(hash,imei);
strncat(hash,ybytes+8,16);
hash[31]=0;
MD5((unsigned char*)hash,31,xbytes);

for (i=0;i<16;i++) rh[i]=xbytes[i]&0xff;
for(i=0;i<4;i++) res[3-i]=rh[i]^rh[i+4]^rh[i+8]^rh[i+12];
i=*((unsigned int*)&res);
i|=0x2000000;
i&=0x3FFFFFF;
sprintf(resbuf,"%i",i);
}
