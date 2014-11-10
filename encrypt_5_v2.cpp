//
//  Калькулятор nlock-кодов для модемов Huawei с новым алгоритмом v2
//
//  Автор - forth32  
//  2014 год
//
//  Ветка для вычисления кодов с индексом 3
//

#include "encrypt.h"

void GetEncrySStr(char* buf, char* phash, int off) {
  
int i;
char c;
for(i=0;i<2;i++) {
 c=buf[off+i*8];
 phash[i]=c;
}
}

int rexor(char* phash) {
  
char c;
int i,len;

len=strlen(phash);
c=phash[0];
if (len == 1) return (c^'Z');
for(i=1;i<len;i++) {
  c^=phash[i];
}
return (unsigned int)c;
}

//====================================================================================

void encrypt_5_v2(char* imei,char* resbuf) {

int r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r12,lr;
int i;
char PW_table[]="5739146280098765432112345678905\000";

char buf[140];
int hash[4];
char* phash=(char*)hash;

memset(buf,0,140);
strcpy(buf,imei);
buf[15]='Z';

for(i=0;i<8;i++) {
  memset(hash,0,16);
  GetEncrySStr(buf,phash,i);
  r0=rexor(phash)&0xff;
  resbuf[i]=r0;
}

for(i=0;i<8;i++) {
  r3=resbuf[i]&0xff;
  r2=r3&0xf;
  r1=PW_table[(r3>>4)+r2];  
  resbuf[i]=r1;
}

if (resbuf[0]=='0') {
  for(i=1;i<8;i++){
    if (resbuf[i] != '0') break;
  }
  resbuf[0]=i+'0';
}  
resbuf[8]=0;
  
}



