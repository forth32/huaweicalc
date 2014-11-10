//
//  Калькулятор NCK-кодов для модемов Huawei с новым алгоритмом v201
//
//  Автор - forth32  
//  2014 год
//
#include "encrypt.h"


// Вычисление индекса обработчика по хешу IMEI, и вызов его
//
// На входе - буфер с imei и буфер для записи результата
// Возвращает индекс обработчика
//************************************************************************
// Вычисление индекса обработчика по хешу IMEI для алгоритма v201
//
// version=2 для v2 и 201 для v201

int proc_index(char* imeibuf,int version) {

int i;
int csum=0; // хеш IMEI
int c1,ch;
long long cx;
int index;
  
  
for(i=0;i<strlen(imeibuf);i++)  {
   ch=imeibuf[i];
   if (version==201) csum+=((ch+i+1)*ch)*(ch+0x139);
   else              csum+=((ch+i+1)*(i+1));
}

cx=((long long)-0x6db6db6d*(long long)csum)>>32;
c1=((cx+csum)>>2)-(csum>>31);
index=csum-((c1<<3)-c1);
return index;
}


//**************************
// циклический сдвиг вправо
//**************************

unsigned int  rotr32(unsigned int val, int n) {
   return ((val>>n)&0x7fffffff)|(val<<(32-n));
}   

//****************************************
// Вычисление кода по алгоритму 201 
//****************************************

int calc201(char* imeibuf, char* resbuf) {

  
int index;

//
// Вычисляем хеш IMEI
//
index=proc_index(imeibuf,201);

switch (index) {
  case 0:
    encrypt_1(imeibuf,resbuf,201);
    break;
  case 1:
    encrypt_2(imeibuf,resbuf,201);
    break;
  case 2:
    encrypt_3(imeibuf,resbuf,201);
    break;
  case 3:
    encrypt_4(imeibuf,resbuf,201);
    break;
  case 4:
    encrypt_6(imeibuf,resbuf,5);
    break;
  case 5:
    encrypt_6(imeibuf,resbuf,6);
    break;
  case 6:
    encrypt_7(imeibuf,resbuf,201);
    break;
  default:
    strcpy (resbuf," - N/A -");
    break;
}

return index;
}


//****************************************
// Вычисление кода по алгоритму 2
//****************************************

int calc2(char* imeibuf, char* resbuf) {

  
int index;

//
// Вычисляем хеш IMEI
//
index=proc_index(imeibuf,2);

switch (index) {
  case 0:
    encrypt_1(imeibuf,resbuf,2);
    break;
  case 1:
    encrypt_2(imeibuf,resbuf,2);
    break;
  case 2:
    encrypt_3(imeibuf,resbuf,2);
    break;
  case 3:
    encrypt_4(imeibuf,resbuf,2);
    break;
  case 4:
    encrypt_5_v2(imeibuf,resbuf);
    break;
  case 5:
    encrypt_6(imeibuf,resbuf,2);
    break;
  case 6:
    encrypt_7(imeibuf,resbuf,2);
    break;
  default:
    strcpy (resbuf," - N/A -");
    break;
}



return index;
}


