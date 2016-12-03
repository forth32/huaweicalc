//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 7
//

#include "encrypt.h"


void rehash7_2(int* hash,int* srcbuf) {

int r4,r5,r6,r7,r10,lr;
int inthash[30];

memcpy(inthash+1,srcbuf,64);  // переносим 16 слов в inthash

r4=hash[0];
r6=hash[1];
r7=hash[2];
r5=hash[3];
//--------- часть 1 --------

#define encpass1(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+inthash[nbyte/4]+((ra&rb)|(rc&(~ra)))+hconst,shift); 

// r4=r6+rotr32(r4+inthash[4/4]+(r6&r7|(r5&(~r6)))+0xD76AA478,25);
// rs ra        rs          nb   ra rb  rc   ra               sh 

encpass1(0xD76AA478,0x04,25,r4,r6,r7,r5)   // RAM:50D8A7F8
encpass1(0xE8C7B756,0x08,20,r5,r4,r6,r7)   // RAM:50D8A824
encpass1(0x242070DB,0x0c,15,r7,r5,r4,r6)   // RAM:50D8A84c
encpass1(0xC1BDCEEE,0x10,10,r6,r7,r5,r4)   // RAM:50D8A870

encpass1(0xF57C0FAF,0x14,25,r4,r6,r7,r5)   // RAM:50D8A898
encpass1(0x4787C62A,0x18,20,r5,r4,r6,r7)   // RAM:50D8A8c0
encpass1(0xA8304613,0x1c,15,r7,r5,r4,r6)   // RAM:50D8A8ec
encpass1(0xFD469501,0x20,10,r6,r7,r5,r4)   // RAM:50D8A914

encpass1(0x698098D8,0x24,25,r4,r6,r7,r5)   // RAM:50D8A938
encpass1(0x8B44F7AF,0x28,20,r5,r4,r6,r7)   // RAM:50D8A960
encpass1(0xffff5bb1,0x2c,15,r7,r5,r4,r6)   // RAM:50D8A988
encpass1(0x895CD7BE,0x30,10,r6,r7,r5,r4)   // RAM:50D8A9b0

encpass1(0x6B901122,0x34,25,r4,r6,r7,r5)   // RAM:50D8A9d8
encpass1(0xFD987193,0x38,20,r5,r4,r6,r7)   // RAM:50D8AA00
encpass1(0xA679438E,0x3c,15,r7,r5,r4,r6)   // RAM:50D8Aa28
encpass1(0x49B40821,0x40,10,r6,r7,r5,r4)   // RAM:50D8Aa54


//-------- алгоритм 2 --------------

//r4=r6+rotr32(r4+inthash[8/4]+(r6&r5|(r7&(~r5)))+0xF61E2562,27);
//rs ra        rs               ra rb  rc   rb

#define encpass2(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+inthash[nbyte/4]+((ra&rb)|(rc&(~rb)))+hconst,shift); 

encpass2(0xF61E2562,0x08,27,r4,r6,r5,r7)   // 50d8aa78
encpass2(0xC040B340,0x1c,23,r5,r4,r7,r6)   // 50d8aa98
encpass2(0x265E5A51,0x30,18,r7,r5,r6,r4)   // 50d8aabc
encpass2(0xE9B6C7AA,0x04,12,r6,r7,r4,r5)   // 50d8aae4

encpass2(0xD62F105D,0x18,27,r4,r6,r5,r7)   // 50d8ab0c
encpass2(0x02441453,0x2c,23,r5,r4,r7,r6)   // 50d8ab38
encpass2(0xD8A1E681,0x40,18,r7,r5,r6,r4)   // 50d8ab5c
encpass2(0xE7D3FBC8,0x14,12,r6,r7,r4,r5)   // 50d8ab80

encpass2(0x21E1CDE6,0x28,27,r4,r6,r5,r7)   // 50d8aba8
encpass2(0xC33707D6,0x3c,23,r5,r4,r7,r6)   // 50d8abcc
encpass2(0xF4D50D87,0x10,18,r7,r5,r6,r4)   // 50d8abf4
encpass2(0x455A14ED,0x24,12,r6,r7,r4,r5)   // 50d8ac20

encpass2(0xA9E3E905,0x38,27,r4,r6,r5,r7)   // 50d8ac44
encpass2(0xFCEFA3F8,0x0c,23,r5,r4,r7,r6)   // 50d8ac6c
encpass2(0x676F02D9,0x20,18,r7,r5,r6,r4)   // 50d8ac94
encpass2(0x8D2A4C8A,0x34,12,r6,r7,r4,r5)   // 50d8acc0

// Алгоритм 3

//r4=r6+rotr32(r4+inthash[0x18/4]+(r5^r7^r6)+0xFFFA3942,28);
//rs  ra       rs                  rb rc ra

#define encpass3(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+inthash[nbyte/4]+(rb^rc^ra)+hconst,shift); 

encpass3(0xFFFA3942,0x18,28,r4,r6,r5,r7)  //50D8ACDC
encpass3(0x8771F681,0x24,21,r5,r4,r7,r6)  //50D8Acfc
encpass3(0x6D9D6122,0x30,16,r7,r5,r6,r4)  //50D8Ad18
encpass3(0xFDE5380C,0x3c,9 ,r6,r7,r4,r5)  //50D8Ad34

encpass3(0xA4BEEA44,0x08,28,r4,r6,r5,r7)  //50D8Ad54
encpass3(0x4BDECFA9,0x14,21,r5,r4,r7,r6)  //50D8Ad70
encpass3(0xF6BB4B60,0x20,16,r7,r5,r6,r4)  //50D8AD94
encpass3(0xBEBFBC70,0x2c,9 ,r6,r7,r4,r5)  //50D8ADB0

encpass3(0x289B7EC6,0x38,28,r4,r6,r5,r7)  //50D8ADD0
encpass3(0xEAA127FA,0x04,21,r5,r4,r7,r6)  //50D8ADF0
encpass3(0xD4EF3085,0x10,16,r7,r5,r6,r4)  //50D8AE14
encpass3(0x04881D05,0x1c,9 ,r6,r7,r4,r5)  //50D8AE30

encpass3(0xD9D4D039,0x28,28,r4,r6,r5,r7)  //50D8AE50
encpass3(0xE6DB99E5,0x34,21,r5,r4,r7,r6)  //50D8AE70
encpass3(0x1FA27CF8,0x40,16,r7,r5,r6,r4)  //50D8AE94
encpass3(0xC4AC5665,0x0c,9 ,r6,r7,r4,r5)  //50D8AEB0

// Алгоритм 4
// смена регистра   r4 --> r0

// r0=r6+rotr32(r0+inthash[4/4]+((~r5|r6)^r7)+0xF4292244,26);
// rs ra        rs                 rb ra  rc  

#define encpass4(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+inthash[nbyte/4]+((~rb|ra)^rc)+hconst,shift); 

encpass4(0xF4292244,0x04,26,r4,r6,r5,r7)  // 50d8aed4
// смена регистра   r5 --> r1
encpass4(0x432AFF97,0x20,22,r5,r4,r7,r6)  // 50d8aef8
encpass4(0xAB9423A7,0x3c,17,r7,r5,r6,r4)  // 50d8af18
encpass4(0xFC93A039,0x18,11,r6,r7,r4,r5)  // 50d8af3c

encpass4(0x655B59C3,0x34,26,r4,r6,r5,r7)  // 50d8af60
encpass4(0x8F0CCC92,0x10,22,r5,r4,r7,r6)  // 50d8aF88
encpass4(0xFFEFF47D,0x2c,17,r7,r5,r6,r4)  // 50d8aFB4
encpass4(0x85845DD1,0x08,11,r6,r7,r4,r5)  // 50d8aFD4

encpass4(0x6FA87E4F,0x24,26,r4,r6,r5,r7)  // 50d8AFFC
encpass4(0xFE2CE6E0,0x40,22,r5,r4,r7,r6)  // 50d8B020
encpass4(0xA3014314,0x1c,17,r7,r5,r6,r4)  // 50d8B044
encpass4(0x4E0811A1,0x38,11,r6,r7,r4,r5)  // 50d8B068

encpass4(0xF7537E82,0x14,26,r4,r6,r5,r7)  // 50d8B088
encpass4(0xBD3AF235,0x30,22,r5,r4,r7,r6)  // 50d8B0A8
encpass4(0x2AD7D2BB,0x0c,17,r7,r5,r6,r4)  // 50d8B0CC

//  Смена накопительных регистров
//старый    новый 
//  R4       R10
//  R5       LR
//  R6       R4
//  R7       R5
//
r10=r4;
lr=r5;
r4=r6;
r5=r7;

// Последнее слагаемое - прямо в массив хешей, разбираем отдельно
hash[0]+=r10;
hash[1]+=r5+rotr32(r4+(((~r10)|r5)^lr)+inthash[0x28/4]+0xEB86D391,11);
hash[2]+=r5;
hash[3]+=lr;

}

//====================================================================================================

//
//  Len = r2
//
void rehash7_1(int* hash,char* buf,int len) {

int r0,r1,r2,r3,r4,r5,r7,r12;

r2=hash[4];
r7=len;
r3=r2;
r12=r7<<3;
r3+=r12;
hash[4]=r3;
r0=r3;
r2>>=3;
r2&=0x3f;
if (r12>r0) hash[5]++;
r5=0x40-r2;
r3=hash[5];
r3=r3+(r7>>29);
hash[5]=r3;
if (r7 < r5) {
  // CC
  r5=0;
  r1=0;	
  memcpy(hash+6+(r2>>2),buf,r7-r5);
  return;
}  

//CS- 50D8b2ec

memcpy(hash+6+(r2>>2),buf,r5);
rehash7_2(hash,hash+6);
r3=r5+0x3f;
if (r7>r3) {
  r4=r5;  // buf* - индекс
  do {
    rehash7_2(hash,(int*)(buf+r4));
    r5+=0x40;
    r3=r5+0x3f;
    r4+=0x40;
  } while (r7>r3);
}
  // 50D8B338  
  r1=r5;
  r2=0;
  memcpy(hash+6+(r2>>2),buf+r5,r7-r5);

}  

//========================================================================================================
void encrypt_7(char* imei,char* resbuf,int version) {

int i;
int r0,r1,r2,r3,r4,r5,r6,r7,r8,r12,lr;
unsigned int u1;
long long cx;
long long  rr5,rr12;

char buf128[128];

// структура в памяти из кучи буферов, отдельные ссылки смотрят в этот общий массив

char fullbuf[100];

char* buf16=fullbuf+16;
char* buf17=fullbuf;
char* bufc=fullbuf+32;
char* buf30=fullbuf+44;
//char* cbufptr=fullbuf+52; - используется для адресации остальных смещений, нам не нужна

unsigned char cb_201[]={0xB, 0xD,0x11,0x13,0x17,0x1D,0x1F,0x25,0x29,0x2B,0x3B,0x61};
unsigned char cb_2[]={1,   1,   2,   3,   5,   8,   0xD,0x15,0x22,0x37,0x59,0x90};
unsigned char* cb;

char c;

char pattern80[64];

int hash[30];  // на самом деле 22
int hsum;


if (version == 201) cb=cb_201;
else                cb=cb_2;
memset(resbuf,0,9);
memset(buf128,0,128);
memset(buf16,0,16);
memcpy(bufc,cb,12);
memset(pattern80,0,64);
pattern80[0]=0x80;

// i==r1

for(i=0;i<15;i++) {
  cx=(long long)i*(long long)0x55555556;
  r2=(cx>>32)-(i>>31);
  r3=(r2<<1)+r2;
  u1=i-r3;
  r2=(int)imei[i];
  r3=r2;
  switch(u1) {
 
   case 0: {  //50d8b400
    r3<<=6;
    r3|=((int)r2)>>2;
    break;
  }

   case 1: {
    r3<<=5;
    r3|=((int)r2)>>3;
    break;
  }

   default: {
    r3>>=4;
    r3|=((int)r2)<<4;
    break;
   }

    
  } 
  r3&=0xff;
  buf128[i]=r3;
}

// 50D8B48C

hsum=0;

for (i=0;i<7;i++) hsum+=((unsigned int)buf128[14-i]&0xff)+(((unsigned int)buf128[i]&0xff)<<8);
hsum+=(buf128[8]&0xff);
r8=0;

for(i=15;i<0x80;i++) {
   r6=i;
   r3=i>>31;
   lr=0x2AAAAAAB;
   cx=(long long)lr*(long long)i;
   r1=cx>>32;
   cx=(long long)lr*(long long)r8;
   lr=cx>>32;
   r0=r8>>31;
   r2=r0;
   r5=(r1>>1)-r3;
   r12=r5<<4;
   r0=(lr>>1)-r0;
   r2=(lr>>1)-r2;
   r1=r0<<4;
   r12=r12-(r5<<2);
   r3=r2<<4;
   lr=r6-r12;
   r1=r1-(r0<<2);
   r7=r5+lr;
   r3=r3-(r2<<2);
   r1=r8-r1;
   r2=r5+r1;
   r3=r8-r3;
   r12=r12-0x18;
   if (r7 > 0xb) r7=r7-0xc;
   r3+=r5;
   if (r5>1) r3=r2+r12;
//RAM:50D8B5E8    
   r0=hsum;
   r1=r6;
   if (r8 == 0) {
     r4=buf128[r3];
     r0=r0%r1;
     r1=bufc[r7];
     r4=r4&r1;
     r12=buf128[r0];
     r3=buf128[r0+1];
     r4|=r12;
   }
   else {
   //RAM:50D8B5F8
     r1=r6;
     r0=hsum;
     r4=buf128[r3];
     r0=r0%r1;
     r1=r8;
     r5=buf128[r0];
     r0=hsum;
     r0=r0%r1;
     r3=buf128[r0];
     r2=bufc[r7];
     r4=r4&r2;
     r4=r4|r5;
   }
// RAM:50D8B54C
   r3=~r3; 
   r3|=r4;
   r3&=0xff;
   buf128[i]=r3;
   r8++;
}

// RAM:50D8B678

r8=0;

for(i=0;i<7;i++) {
  r1=imei[i];
  r2=imei[i+1];
  r2=r2|(r1<<8);
  r8+=r2;
}  

r8+=imei[14];

memset(hash,0,120);

hash[5]=0;
hash[4]=0;
hash[0]=0x67452301;
hash[1]=0xEFCDAB89;
hash[2]=0x98BADCFE;
hash[3]=0x10325476;

//50D8B710
rehash7_1(hash,buf128,0x80);

memcpy(buf30,hash+4,8);
r3=hash[4];
r3>>=3;
r2=r3&0x3f;
if (r2 <= 0x37) r2=0x38-r2;
else            r2=0x78-r2;
rehash7_1(hash,pattern80,r2);

//50D8B748

rehash7_1(hash,buf30,8);  //50D8B754
//50D8B758

memcpy(buf16,hash,16);
r5=r8&3;  // 50D8B768

memcpy(buf17,buf16,16);
r12=*((int*)(buf17+(r5<<2)));
r4=0;
r0=0;


// Этап 1 - пытаемся наскрести в buf16 готовых ascii-цифр

for(r2=0;r2<=15;r2++) {
 c=buf16[r2];
 if ((c>0x2f)&&(c <= 0x39)) resbuf[r4++]=c;
 if (r4>7) break;   //50D8B7D4
}
if (r4 > 7) goto bdone; // набрали все 8 цифр - нам хватит

// Этап 2 - попытка полцчить недостающие цифры.

//printf("\n 1cycle: imei=%s r4=%i",imei,r4);

r6=0;
u1=(3-r5)<<2;    // индекс в buf17
r5=0xcccccccd;
rr5=r5&0xffffffff;

do {
  r0=r6^1;
  rr12=r12&0xffffffff;
  cx=rr12*rr5;
  r2=((cx>>32)&0xffffffff)>>3;
  if (r2 == 0) {
    r0&=1;
  } 
  else r0=0;
  r3=r2<<1;
  r1=r2<<3;
  r3=r3+r1;
  r3=r12-r3;
  r3+=0x30;
  r12=r2;
  r3&=0xff;
  resbuf[r4++]=r3;
  if (r0 != 0) {
    r12=*((int*)(buf17+u1));
    r6=1;
  }
} while ((r4<8) && (r12 != 0)); 

//50D8B888

if (r4>7) goto bdone;  // наконец наскребли нужное количество цифр
r12=r5;
r0=0;
//printf("\n 2cycle: imei=%s r4=%i",imei,r4);

loc_50D8B8DC:
 if ((r4>7)&&(resbuf[0] != 0)) goto bdone;
 
//50D8B8F4
  r3=buf16[r0]&0xff;
  rr12=r12&0xffffff;
  rr5=r3&0xffffff;
  cx=rr12*r5;
  r2=(cx>>32)&0xffffffff;
  r2>>=3;
  r1=r2<<3;
  r2<<=1;
  r2+=r1;
  r3=r3-r2;
  r3+='0';
  r0++;
if (r4 == 8) resbuf[0]=r3&0xff;
else resbuf[r4++]=r3&0xff;

if (r0 == 16) goto bdone;
  goto loc_50D8B8DC;
//50D8B89C   r4!= 8

//  --- Все, буфер готов ! -------
bdone:
  if(resbuf[0] == '0') {
    r2=0;
    if (r8 != 0) r2=1;
    r3=(buf16[r2]&7)+'1';
    resbuf[0]=r3;
  }
  resbuf[8]=0;


}
