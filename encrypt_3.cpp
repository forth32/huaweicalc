//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 2
//

#include "encrypt.h"

#define imeilen 15;

void encrypt_3(char* imei,char* resbuf,int version) {

int i;
int r0,r1,r2,r3,r4,r5,r6,r12,lr;
unsigned int u1;
unsigned long long cx;
unsigned int arg;

char imeibuf[500];
unsigned int* imeiptr=(unsigned int*)imeibuf;
unsigned int hash2[4]={0x67452301,0xefcdab89,0x98badcfe,0x10325476};
unsigned int copyhash[4];

unsigned char*  hashptr;

unsigned char buf104[120];

resbuf[0]=0;

memset(imeibuf,0,500);
strcpy(imeibuf,imei);
imeibuf[15]=0x80;
imeibuf[0x38]=0x78;

r2=hash2[0];
r4=hash2[1];
r12=hash2[2];
lr=hash2[3];

arg=r12^lr;

#define encpass1(hconst,nbyte,shift,rsum,ra,rb,rc) \
  rsum=ra+rotr32(rsum+imeiptr[nbyte/4]+((unsigned int)hconst)+((arg&ra)^rb),shift); \
  arg=ra^rc;   
   
#define encpass1_25(hconst,nbyte) encpass1(hconst,nbyte,25,r2, r4, lr, r12)  
#define encpass1_20(hconst,nbyte) encpass1(hconst,nbyte,20,lr, r2, r12,r4 )  
#define encpass1_15(hconst,nbyte) encpass1(hconst,nbyte,15,r12,lr, r4, r2 )  
#define encpass1_10(hconst,nbyte) encpass1(hconst,nbyte,10,r4, r12,r2, lr )  
  
encpass1_25(0xD76AA478,0)
encpass1_20(0xE8C7B756,4)
encpass1_15(0x242070DB,8)
encpass1_10(0xC1BDCEEE,0xc)

encpass1_25(0xF57C0FAF,0x10)   // 50d8769c
encpass1_20(0x4787C62A,0x14)   // 50D876C0
encpass1_15(0xA8304613,0x18)   // 50D876E4
encpass1_10(0xFD469501,0x1c)   // 50D87708

encpass1_25(0x698098D8,0x20)   // RAM:50D8772C
encpass1_20(0x8B44F7AF,0x24)   // RAM:50D87750
encpass1_15(0xffff5bb1,0x28)   // RAM:50D87774
encpass1_10(0x895CD7BE,0x2c)   // 50D87798

encpass1_25(0x6B901122,0x30)   // RAM:50D877BC
encpass1_20(0xFD987193,0x34)   // RAM:50D877E0
encpass1_15(0xA679438E,0x38)   // RAM:50D87804
encpass1_10(0x49B40821,0x3c)   // RAM:50D87828

// смена алгоритма

#define encpass2(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum+=imeiptr[nbyte/4]+(((rb^ra)&rc)^rb)+hconst;     \
 rsum=ra+rotr32(rsum,shift);
 
// r2=r2+imeiptr[4/4]+(((r12^r4)&lr)^r12)+0xF61E2562;
// rsum                   rb ra  rc   rb
// r2  =  r4+rotr32(r2,27);
//rsum    ra 

#define encpass2_27(hconst,nbyte) encpass2(hconst,nbyte,27,r2, r4, r12,lr )
#define encpass2_23(hconst,nbyte) encpass2(hconst,nbyte,23,lr, r2, r4 ,r12)
#define encpass2_18(hconst,nbyte) encpass2(hconst,nbyte,18,r12,lr, r2 ,r4 )
#define encpass2_12(hconst,nbyte) encpass2(hconst,nbyte,12,r4, r12,lr ,r2 )

encpass2_27(0xF61E2562,4)
encpass2_23(0xC040B340,0x18)  // 50D87870
encpass2_18(0x265E5A51,0x2c)  // RAM:50D87894
encpass2_12(0xE9B6C7AA,0)   // 50d878b8

encpass2_27(0xD62F105D,0x14)  // 50d878dc
encpass2_23(0x02441453,0x28)   // RAM:50D87900
encpass2_18(0xD8A1E681,0x3c) // 50D87924
encpass2_12(0xE7D3FBC8,0x10) // RAM:50D87948

encpass2_27(0x21E1CDE6,0x24) //50d8796c
encpass2_23(0xC33707D6,0x38) //50d87990
encpass2_18(0xF4D50D87,0x0c) // RAM:50D879B4	
encpass2_12(0x455A14ED,0x20) // 50D879d8

encpass2_27(0xA9E3E905,0x34) // 50d879fc
encpass2_23(0xFCEFA3F8,0x08) //50d87a20
encpass2_18(0x676F02D9,0x1c) // 50d87a44
encpass2_12(0x8D2A4C8A,0x30) // 50d87a68

// смена алгоритма

// r2=r4+rotr32(r2+imeiptr[0x14/4]+((lr^r12)^r4)+0xFFFA3942,28);        // 50d87a84
// rs ra        rs                   rb  rc  ra    hconst   shift                  

#define encpass3(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+imeiptr[nbyte/4]+((rb^rc)^ra)+hconst,shift); 

#define encpass3_28(hconst,nbyte) encpass3(hconst,nbyte,28,r2, r4, lr, r12)
#define encpass3_21(hconst,nbyte) encpass3(hconst,nbyte,21,lr, r2, r12,r4 )
#define encpass3_16(hconst,nbyte) encpass3(hconst,nbyte,16,r12,lr, r4, r2 )
#define encpass3_9(hconst,nbyte) encpass3(hconst,nbyte,9 ,r4, r12,r2, lr )

encpass3_28(0xFFFA3942,0x14)  // 50d87a84
encpass3_21(0x8771F681,0x20)  // 50d87aa4
encpass3_16(0x6D9D6122,0x2c)  // 50d87ac4
encpass3_9 (0xFDE5380C,0x38)  // 50d87ae4

encpass3_28(0xA4BEEA44,0x04)  // 50d87b04
encpass3_21(0x4BDECFA9,0x10)  // 50d87b24
encpass3_16(0xF6BB4B60,0x1c)  // 50d87b44
encpass3_9 (0xBEBFBC70,0x28)  // 50d87b64

encpass3_28(0x289B7EC6,0x34)  // 50d87b84
encpass3_21(0xEAA127FA,0x00)  // 50d87ba4
encpass3_16(0xD4EF3085,0x0c)  // 50d87bc4
encpass3_9 (0x04881D05,0x18)  // 50d87be4

encpass3_28(0xD9D4D039,0x24)  // 50d87c04
encpass3_21(0xE6DB99E5,0x30)  // 50d87c24
encpass3_16(0x1FA27CF8,0x3c)  // 50d87c44
encpass3_9 (0xC4AC5665,0x08)  // 50d87c64
  
// алгоритм 4

#define encpass4(hconst,nbyte,shift,rsum,ra,rb,rc) \
 rsum=ra+rotr32(rsum+imeiptr[nbyte/4]+(((~rb)|ra)^rc)+hconst,shift);

#define encpass4_26(hconst,nbyte)  encpass4(hconst,nbyte,26,r2, r4, lr, r12) 
#define encpass4_22(hconst,nbyte)  encpass4(hconst,nbyte,22,lr, r2, r12, r4) 
#define encpass4_17(hconst,nbyte)  encpass4(hconst,nbyte,17,r12,lr, r4,  r2) 
#define encpass4_11(hconst,nbyte)  encpass4(hconst,nbyte,11,r4, r12,r2,  lr) 


//  r2=r4+rotr32(r2+imeiptr[0/4]+(((~lr)|r4)^r12)+0xF4292244,26);
//  rs ra        rs                  rb  ra  rc

encpass4_26(0xF4292244,0x00)   // 50d87c88
encpass4_22(0x432AFF97,0x1c)   // 50d87cac
encpass4_17(0xAB9423A7,0x38)   // 50d87cd0
encpass4_11(0xFC93A039,0x14)   // 50d87cf4

encpass4_26(0x655B59C3,0x30)   // 50d87d18
encpass4_22(0x8F0CCC92,0x0c)   // 50d87d3c
encpass4_17(0xFFEFF47D,0x28)   // 50d87d60
encpass4_11(0x85845DD1,0x04)   // 50d87d84
  
encpass4_26(0x6FA87E4F,0x20)   // 50d87da8
encpass4_22(0xFE2CE6E0,0x3c)   // 50d87dcc
encpass4_17(0xA3014314,0x18)   // 50d87df0
encpass4_11(0x4E0811A1,0x34)   // 50d87e14

encpass4_26(0xF7537E82,0x10)   // 50d87e38
encpass4_22(0xBD3AF235,0x2c)   // 50d87e5c
encpass4_17(0x2AD7D2BB,0x08)   // 50d87e80

// 50d87eb4 - алгоритм обработки немного другой
hash2[1]=hash2[1]+r12+rotr32(r4+imeiptr[0x24/4]+(((~r2)|r12)^lr)+0xEB86D391,11);
hash2[0]+=r2;
hash2[2]+=r12;
hash2[3]+=lr;

memcpy(copyhash,hash2,16);
hash2[0]=0;
memset(buf104,0,110);

hashptr=(unsigned char*)copyhash;
if (version == 201) hashptr+=5;  // пказываем на байт 5

memcpy(buf104,hashptr,8);

r2=buf104[0];
cx=(unsigned long long)r2*(unsigned long long)0xcccccccd;
r3=(cx>>32)&0xffffffff;
r3>>=3;
r1=r3<<3;
r3<<=1;
r3=r3+r1;   
r2=r2-r3;

if (r2 != 0) {
  buf104[0]=r2;
}
else {
  for(i=8;i<14;i++) {
    r3=buf104[i];
    cx=(unsigned long long)0xcccccccd*(unsigned long long)r3;   // r2:r7
    r2=(cx>>32)&0xffffffff;
    r2>>=3;
    r1=r2<<3;
    r2<<=1;
    r2+=r1;
    r3=r3-r2;
    r2=r3;
    if (r2 != 0) break;
  }
  if (r2 == 0) buf104[0]=5;
  else         buf104[0]=r2;
}  

for (i=0;i<8;i++) {
  r1=buf104[i];
  r3=(r1-0x30)&0xff;
  cx=(unsigned long long)0xcccccccd*(unsigned long long)r1;   // r2:r7
  r2=(cx>>32)&0xffffffff;
  if (r3>9) {
    r3=r2>>3;
    r2=r3<<3;
    r3<<=1;
    r3+=r2;
    r3=r1-r3;
    r3+=0x30;
    buf104[i]=r3;
  }
}
memcpy(resbuf,buf104,8);
resbuf[8]=0;
  

}



