//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 5 и 6 - они одинаковые и отличаются только номерами выбираемых числе из хеша
//

#include "encrypt.h"

void rehash5(unsigned int* hash) {

unsigned int r0,r1,r2,r3,r4,r5,r6,r7,r12,lr;
int i;

int sbuf[88];  // буфер sp+00

char* chash=(char*)hash+0x1f;

for(i=0;i<16;i++) {

 r1=*(chash-3)&0xff;
 r3=*(chash-2)&0xff;
 r0=*(chash-1)&0xff;
 r2=*(chash-0)&0xff;

 chash+=4;
 r3<<=16;
 r3|=(r1<<24);
 r3|=r2;
 r3|=(r0<<8);
 
 sbuf[i]=r3; 
}



for(i=13;i<77;i++) {
  
 r3=sbuf[i];
 r0=sbuf[i-5];
 r2=sbuf[i-11];
 r1=sbuf[i-13];
 r3=r3^r0;
 r2=r2^r1;
 r3=r3^r2;
 r3=rotr32(r3,31);
 sbuf[i+3]=r3;
} 

r6=hash[0];
lr=hash[1];
r4=hash[2];
r7=hash[3];
r0=hash[4];

for(i=0;i<20;i++) {
  if (i != 0) {
   r6=r1;
   r7=r3;
  }  
  r1=lr&r4;
  r12=sbuf[i];
  r3=~lr;
  r3&=r7;
  r1|=r3;
  r0+=rotr32(r6,27);
  r1+=r12;
  r12=rotr32(lr,2);
  r2=r0+0x5A827999;
  r3=r4;
  r1+=r2;
  r4=r12;
  r0=r7;
  lr=r6;
}
// 50d89714
r5=r1;
r1=r7;
r4=r6;
r6=r3;


for(i=0;i<20;i++){
  if (i != 0) {
    r5=r3;
    r12=lr;
    r6=r2;
  }
  r3=r4^r12;
  r0=sbuf[i+20];
  r1+=rotr32(r5,27);
  r3^=r6;
  r2=r1+0x6ED9EBA1;
  r3+=r0;
  r3+=r2;
  lr=rotr32(r4,2);
  r2=r12;
  r1=r6;
  r4=r5;
}  

// 50d89774

r7=r3;
r4=r12;
for(i=0;i<20;i++) {
  if (i != 0) {
    r7=r3;
    r4=r2;
  }
  r3=lr|r4;
  r3&=r5;
  r0=lr&r4;
  r12=sbuf[i+40];
  r1+=rotr32(r7,27);
  r6=rotr32(r5,2);
  r3|=r0;
  r2=r1+0x8F1BBCDC;
  r3+=r12;
  r3+=r2;
  r1=r4;
  r2=lr;
  r5=r7;
  lr=r6;
}  

// 50d897d4
lr=r3;
r12=r7;
r5=r2;

for(i=0;i<20;i++) {
  if (i != 0) {
    lr=r2;
    r6=r0;
    r5=r3;
  }
  r0=sbuf[i+60];
  r3=r12^r6;
  r1+=rotr32(lr,27);
  r3^=r5;
  r3+=r0;
  r2=r1+0xCA62C1D6;
  r2+=r3;
  r0=rotr32(r12,2);
  r3=r6;
  r1=r5;
  r12=lr;
}

//50d89830

hash[0]+=r2;
hash[1]+=lr;
hash[2]+=r0;
hash[3]+=r6;
hash[4]+=r5;
hash[23]=0;

}  
  
// mode:
//  2 - Ветка 6 алгоритма 2
//  5 - Ветка 5 алгоритам 201
//  6 - Ветка 6 алгоритма 201  
//
//

void encrypt_6(char* imei,char* resbuf, int mode) {

int i;
unsigned int r0,r1,r2,r3,r4,r5,r6,r7,r12,lr;
unsigned int u1;
unsigned long long cx;

unsigned int hash[26];
unsigned char* chash;
unsigned char* phash;

char varstr[30];

chash=(unsigned char*)hash+0x1c;  // тот самый buf40-0xac
phash=(unsigned char*)hash;

memset(hash,0,26*4);

hash[0]=0x67452301;
hash[5]=0;
hash[6]=0;
hash[23]=0;
hash[1]=0xEFCDAB89;
hash[2]=0x98BADCFE;
hash[3]=0x10325476;
hash[4]=0xC3D2E1F0;
hash[24]=0;
hash[25]=0;

for (i=0;i<15;i++) {
 r2=hash[23];

 r3=imei[i];
 
 chash[r2]=r3;
 r2++;
 hash[23]=r2;

 r3=hash[5];
 r3+=8;
 hash[5]=r3;
 r2=r3;

 if (r3 == 0) {
   r3=hash[6];
   r3++;
   hash[6]=r3;
   r2=r3;
   if (r3 == 0) {
     r3++;
     hash[25]=r3;
   }
 }

 r3=hash[23];
 if (r3 == 0x40) rehash5(hash);
 if (hash[25] != 0) break;
}

if (hash[25] != 0) {
  printf("\nERROR-- could not compute message digest");
  return;
}

r0=hash[24];
if (r0 != 0) goto bypass1;  //---------------- 50d89cb4, не проверить никак!

//r3=hash[23];
//if (r3<=0x37) ;    // 50d89bc0, продолжение кода, странное, пока не стал делать. Далее следует переход на 50d89db4

r3=hash[23];
chash[r3]=0x80;
r3++;
hash[23]=r3;
r2=r3;

if (r2 <=0x37) {
  r1=r0;
  do { 
   r3=hash[23];
   chash[r3]=r1;
   r3++;
   hash[23]=r3;
   r2=r3;
  } while (r2 <= 0x37);
}

r2=hash[6];
r2>>=24;
phash[0x54]=r2&0xff;
r3=hash[6];
r3>>=16;
phash[0x55]=r3&0xff;
r2=hash[6];
r2>>=8;
phash[0x56]=r2&0xff;

r1=hash[6];
phash[0x57]=r1&0xff;

r3=hash[5];
r3>>=24;
phash[0x58]=r3&0xff;

r2=hash[5];
r2>>=16;
phash[0x59]=r2&0xff;

r3=hash[5];
r3>>=8;
phash[0x5a]=r3&0xff;

r2=hash[5];
phash[0x5b]=r2&0xff;

rehash5(hash);
hash[24]=1;

//*****************
bypass1:

switch(mode) {
  case 2:
    sprintf(varstr,"%u",hash[0]);
    break;
    
  case 5:
    sprintf(varstr,"%u",hash[1]);
    break;
    
  case 6:  
    sprintf(varstr,"%u",hash[2]);
    break;
}
r0=strlen(varstr);

if (strlen(varstr)>7) {
  strncpy(resbuf,varstr,8);
  resbuf[8]=0;
  return;
}  
strcpy(resbuf,varstr);

switch(mode) {
  case 2:
    sprintf(varstr,"%u",hash[1]);
    break;
    
  case 5:
    sprintf(varstr,"%u",hash[4]);
    break;
    
  case 6:  
    sprintf(varstr,"%u",hash[3]);
    break;
}

strcat(resbuf,varstr);
resbuf[8]=0;

}




