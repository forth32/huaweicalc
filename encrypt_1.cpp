//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 0
//

#include "encrypt.h"

void encrypt_1(char* imei,char* resbuf,int version) {

int i;
unsigned int r0,r1,r2,r3,r4,r5,r6,r7,r12,lr;
unsigned long long cx;
unsigned int ibuf128[128];
int srcbuf_201[]={0x6E9C2A,0x3CA2B3C,0x1080DC,0x30855EE,0x3D3283A,0x2F4F85A,0x1F8808E,0x3147D10,
          0x34BBBB5,0x29EEADD,0x2318616,0x50F3ADC,0xD11F38,0x2123BD2,0x4276C86,0x355CAAD};

int srcbuf_2[]={0x1966A9,0x21058F,0x2AEDA9,0x37CE91,0x488C9F,0x5E507D,0x7A9BE5,0x9F644B,0xCF35A1,0x10D5F55,0x15E2F25,
       0x1C73D6B,0x24FCFDD,0x3015B47,0x3E829E9,0x5143685};
	  
unsigned int buf512[128];
int zvar[8];
int* srcbuf;

if (version == 201) srcbuf=srcbuf_201;
else srcbuf=srcbuf_2;


memset(resbuf,0,9);
memset(buf512,0,512);
for(i=0;i<strlen(imei);i++) buf512[i]=(int)imei[i];  

for(i=0;i<16;i++) ibuf128[i]=srcbuf[i];
for(i=16;i<128;i++) ibuf128[i]=i;  // остаток буфер заполняем увеличивающимися числами
r6=0;

for (i=0;i<15;i++)  r6+=buf512[i]*ibuf128[i];

r2=r6;
r7=0xCCCCCCCD;

r3=r2&0xf0;
r1=r2&0xf00;
r0=r2&0xf000;
r12=r2&0xf0000;
lr=r2&0xf00000;
r4=r2&0xf000000;

r3>>=4;
r1>>=8;
zvar[1]=r3;
r0>>=12;
r3=r2>>28;
r12>>=16;
lr>>=20;
r4>>=24;
r2&=0xf;
zvar[2]=r1;
zvar[3]=r0;
zvar[4]=r12;
zvar[5]=lr;
zvar[6]=r4;
zvar[7]=r3;
zvar[0]=r2;

for (i=0;i<8; i++) {
  r3=zvar[i];
  cx=(unsigned long long)r7*(unsigned long long)r3;
  r1=cx&0xffffffff;
  r2=(cx>>32)&0xffffffff;
  r2>>=3;
  r1=r2<<3;
  r2<<=1;
  r2+=r1;
  r3=r3-r2;
  zvar[i]=r3;
}


r3=zvar[0];
if (r3 == 0) {
   r3++;
   zvar[0]=r3;
}

for(i=0;i<8;i++) {
  r3=zvar[i];
  r3+=0x30;
  resbuf[i]=r3;
}

}




