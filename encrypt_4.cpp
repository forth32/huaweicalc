//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 3
//

#include "encrypt.h"


void rehash4(unsigned int* hash,unsigned  int* rhash) {
  
int r0,r1,r4,r6,r7,r10,r12,lr;

int inthash[16];

memcpy(inthash,rhash,64);

r7=hash[0];
r6=hash[1];
r12=hash[2];
lr=hash[3];

//  начинаются алгоритмы свертки

//   r1=r6+rotr32(r7+inthash[0]+((r6&r12)|((~r6)&lr))+0xD76AA478,25);
//  rsum ra       rb        nb    ra  rc     ra   rd    hconst   shift
#define encpass1(hconst,nbyte,shift,rsum,ra,rb,rc,rd) \
   rsum=ra+rotr32(rb+inthash[nbyte/4]+((ra&rc)|((~ra)&rd))+hconst,shift); 

encpass1(0xD76AA478,0,25,r1,r6,r7,r12,lr)

// lr=r1+rotr32(lr+inthash[4/4]+((r6&r1)|(~r1&r12))+0xE8C7B756,20);
// rs ra        rb                rc ra   ra   rd

encpass1(0xE8C7B756,4,20,lr,r1,lr,r6,r12)   //50d88854
encpass1(0x242070DB,8,15,r12,lr,r12,r1,r6)  //50d8887c
encpass1(0xC1BDCEEE,0xc,10,r0,r12,r6,lr,r1) // 50d888a4

encpass1(0xF57C0FAF,0x10,25,r1,r0,r1,r12,lr) // 50d888cc
encpass1(0x4787C62A,0x14,20,lr,r1,lr,r0,r12) // 50d888f8
encpass1(0xA8304613,0x18,15,r12,lr,r12,r1,r0) // 50d8891c
encpass1(0xFD469501,0x1c,10,r0,r12,r0,lr,r1)  // 50D88944

encpass1(0x698098D8,0x20,25,r1,r0,r1,r12,lr)  // 50d88970
encpass1(0x8B44F7AF,0x24,20,lr,r1,lr,r0,r12)  // 50d88994
encpass1(0xffff5c00-0x4f,0x28,15,r12,lr,r12,r1,r0) // 50d889c0
encpass1(0x895CD7BE,0x2c,10,r0,r12,r0,lr,r1)     //    9e4

encpass1(0x6B901122,0x30,25,r1,r0,r1,r12,lr)  // a0c
encpass1(0xFD987193,0x34,20,lr,r1,lr,r0,r12)   // a38
encpass1(0xA679438E,0x38,15,r12,lr,r12,r1,r0)  // a5c
encpass1(0x49B40821,0x3c,10,r0,r12,r0,lr,r1)   // a88

//   r1=r0+rotr32(r1+inthash[4/4]+(lr&r0|(~lr&r12))+0xF61E2562,27);
//   rs  ra       rb               rc ra   rc  rd 

#define encpass2(hconst,nbyte,shift,rsum,ra,rb,rc,rd) \
   rsum=ra+rotr32(rb+inthash[nbyte/4]+((ra&rc)|((~rc)&rd))+hconst,shift); 

encpass2(0xF61E2562,0x04,27,r1,r0,r1,lr,r12);  // 50d88aac
encpass2(0xC040B340,0x18,23,lr,r1,lr,r12,r0);  //acc
encpass2(0x265E5A51,0x2c,18,r12,lr,r12,r0,r1)  // af0
encpass2(0xE9B6C7AA,0x00,12,r0,r12,r0,r1,lr)      // b18

encpass2(0xD62F105D,0x14,27,r1,r0,r1,lr,r12) //b44
encpass2(0x02441453,0x28,23,lr,r1,lr,r12,r0) //b68
encpass2(0xD8A1E681,0x3c,18,r12,lr,r12,r0,r1)  // b90
encpass2(0xE7D3FBC8,0x10,12,r0,r12,r0,r1,lr)      // bb4

encpass2(0x21E1CDE6,0x24,27,r1,r0,r1,lr,r12)  // be0
encpass2(0xC33707D6,0x38,23,lr,r1,lr,r12,r0) //  c00
encpass2(0xF4D50D87,0x0c,18,r12,lr,r12,r0,r1)  // c28
encpass2(0x455A14ED,0x20,12,r0,r12,r0,r1,lr)   // c50

encpass2(0xA9E3E905,0x34,27,r1,r0,r1,lr,r12)  // c7c
encpass2(0xFCEFA3F8,0x08,23,lr,r1,lr,r12,r0) //  ca0
encpass2(0x676F02D9,0x1c,18,r12,lr,r12,r0,r1)  // cc8
encpass2(0x8D2A4C8A,0x30,12,r0,r12,r0,r1,lr)   // cec

//----------------------------------------------

#define encpass3(hconst,nbyte,shift,rsum,ra,rb,rc) \
   rsum=ra+rotr32(rsum+inthash[nbyte/4]+(ra^(rb^rc))+hconst,shift); 

   
//r1=r0+rotr32(r1+inthash[0x14/4]+(r0^(lr^r12))+0xFFFA3942,28);
//rs ra        rs                  ra  rb  rc 
//r3=r12^r0;

encpass3(0xFFFA3942,0x14,28,r1,r0,lr,r12);   // 0x50d88d10
encpass3(0x8771F681,0x20,21,lr,r1,r12,r0)    // d2c
encpass3(0x6D9D6122,0x2c,16,r12,lr,r0,r1)    // d48
encpass3(0xFDE5380C,0x38,9,r0,r12,r1,lr)    // d64

encpass3(0xA4BEEA44,0x04,28,r1,r0,lr,r12);   // d84
encpass3(0x4BDECFA9,0x10,21,lr,r1,r12,r0)    // da0
encpass3(0xF6BB4B60,0x1c,16,r12,lr,r0,r1)    // dc4
encpass3(0xBEBFBC70,0x28,9,r0,r12,r1,lr)    // de0

encpass3(0x289B7EC6,0x34,28,r1,r0,lr,r12);   // e00
encpass3(0xEAA127FA,0x00,21,lr,r1,r12,r0)    // e24
encpass3(0xD4EF3085,0x0c,16,r12,lr,r0,r1)    // e40
encpass3(0x4881D05,0x18,9,r0,r12,r1,lr)      // e60

encpass3(0xD9D4D039,0x24,28,r1,r0,lr,r12);   // e84
encpass3(0xE6DB99E5,0x30,21,lr,r1,r12,r0)    // e9c
encpass3(0x1FA27CF8,0x3c,16,r12,lr,r0,r1)    // ebc
encpass3(0xC4AC5665,0x08,9,r0,r12,r1,lr)      // edc

//------------------------------------------------------

// r1=r0+rotr32(r1+inthash[0/4]+(r12^(r0|(~lr)))+0xF4292244,26);
// rs ra        rs               rb   ra   rc 

#define encpass4(hconst,nbyte,shift,rsum,ra,rb,rc) \
   rsum=ra+rotr32(rsum+inthash[nbyte/4]+(rb^(ra|(~rc)))+hconst,shift); 

encpass4(0xF4292244,0x00,26,r1,r0,r12,lr) // 50d88f00
encpass4(0x432AFF97,0x1c,22,lr,r1,r0,r12) // f24
encpass4(0xAB9423A7,0x38,17,r12,lr,r1,r0)  // f44
encpass4(0xFC93A039,0x14,11,r0,r12,lr,r1)  // f68

encpass4(0x655B59C3,0x30,26,r1,r0,r12,lr) // f88
encpass4(0x8F0CCC92,0x0c,22,lr,r1,r0,r12) // fac
encpass4(0xFFEFF47D,0x28,17,r12,lr,r1,r0)  // fd0
encpass4(0x85845DD1,0x04,11,r0,r12,lr,r1)  // ff4

encpass4(0x6FA87E4F,0x20,26,r1,r0,r12,lr) // 50d89018
encpass4(0xFE2CE6E0,0x3c,22,lr,r1,r0,r12) // 03c
encpass4(0xA3014314,0x18,17,r12,lr,r1,r0)  // 060
encpass4(0x4E0811A1,0x34,11,r0,r12,lr,r1)  // 084

encpass4(0xF7537E82,0x10,26,r1,r0,r12,lr) // 0a4
encpass4(0xBD3AF235,0x2c,22,lr,r1,r0,r12) // 0c4
encpass4(0x2AD7D2BB,0x08,17,r12,lr,r1,r0)  // 0f0

// В этой точке:
// R-здесь  R-в прошивке значение
//   R0          R4       4606f40d 
//   R1          r10      c4863aae 
//   R12         R12      5747f475
//   LR          R7       3e1096a1

//encpass4(0xEB86D391,0x24,11,r0,r12,lr,r1)  // 124
// переходим на новые регистры
r4=r0;
r10=r1;
r7=lr;
// последний проход хеша и сохранение результата

hash[0]+=r10;
hash[1]+=r12+rotr32(inthash[0x24/4]+r4+((~r10|r12)^r7)+0xEB86D391,11);
hash[2]+=r12;
hash[3]+=r7;

}


void enc4_sub_2(unsigned int* hash,char* hbuf,int hlen) {

int r0,r2,r3,r4,r5,r12;


r2=hash[4];
r3=r2;
r12=hlen<<3;
r3+=r12;
hash[4]=r3;
r0=r3;
r2>>=3;
if (r12 > r0) hash[5]++;
r2&=0x3f;
r5=0x40-r2;

r3=hash[5];
r3+=hlen>>29;
hash[5]=r3;


if (hlen < r5) {
   memcpy((unsigned char*)hash+24+r2,hbuf,hlen);
   return;
}
memcpy((unsigned char*)hash+24+r2,hbuf,r5);
rehash4(hash,hash+6);

if (hlen>(r5+0x3f)) {
  r4=r5;  // индекс в буфере
  do {
    r5+=0x40;
    rehash4(hash,(unsigned int*)(hbuf+r4));
    r4+=0x50;
    printf("\n iter r5=%08x  r4=%08x",r5,r4);
  } while (hlen > (r5+0x3f));
}
memcpy((unsigned char*)hash,hbuf+r5,hlen-r5);

}


void enc4_sub_1(char* hbuf, int* zvar) {
  
int r2,r3;
unsigned int hc[]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476};
unsigned char hdata[]={0x80,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
                 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,0 };

int hlen;
unsigned int hash[30];  // на самом деле юзаются 22 слова
char buf26[40];

hlen=strlen(hbuf);
memset(hash,0,88);

hash[0]=hc[0];
hash[1]=hc[1];
hash[2]=hc[2];
hash[3]=hc[3];
hash[4]=0;
hash[5]=0;
enc4_sub_2(hash,hbuf,hlen);   // hash=r0  hbuf=r1 hlen=r2
memcpy(buf26,hash+4,8);

r3=(hash[4]>>3)&0x3f;
if (r3>0x37) r2=0x78-r3;
       else  r2=0x38-r3;

enc4_sub_2(hash,(char*)hdata,r2);
enc4_sub_2(hash,buf26,8);
memcpy(zvar,hash,16);

}


void encrypt_4(char* imei,char* resbuf,int version) {

int i;
int r0,r1,r2,r3;
int zvar[5];

char buf12[20];
char buf256[256];
char buf44[100];

memset(buf12,0,20);
if (version==2) strcpy(buf12,"hwideadatacard");
else strcpy(buf12,"dfkdkfllekkodk");

memset(buf256,0,256);
memset(zvar,0,20);
enc4_sub_1(buf12,zvar);

strcpy(buf256,imei);
memcpy(buf256+strlen(imei),zvar,16); // buf256 - это imei + вычисленный zvar
memset(resbuf,0,8); //  очищаем приемник результата
enc4_sub_1(buf256,(int*)buf12);

for (i=0;i<4;i++) {
  r2=buf12[i];
  r0=buf12[i+4];
  r3=buf12[i+8];
  r1=buf12[i+12];
  r2=(r2^r0)^(r3^r1);
  buf44[i]=r2;
}

r2=0;
for(i=0;i<4;i++) {
  r2=(r2<<8)|(buf44[i]&0xff);
}
r2|=0x2000000;
r2=r2&(~0xfc000000);
sprintf(resbuf,"%i",r2);
}



