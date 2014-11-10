//
//  Калькулятор NCK-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calc201(char* imei, char* resbuf);
int calc2(char* imei, char* resbuf);
void encrypt_1(char* imei,char* resbuf,int version);
void encrypt_2(char* imei,char* resbuf,int version);
void encrypt_3(char* imei,char* resbuf,int version);
void encrypt_4(char* imei,char* resbuf,int version);
void encrypt_5_v2(char* imei,char* resbuf);
void encrypt_6(char* imei,char* resbuf,int mode);
void encrypt_7(char* imei,char* resbuf,int version);

void encrypt_v1(char* imei,char* resbuf,char* pass);

unsigned int  rotr32(unsigned int val, int n);