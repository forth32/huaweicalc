#include <QApplication>
#include "calcdialog.h"
#include "encrypt.h"
     
int main(int argc, char* argv[]) {

  char codebuf[40];

if (argc == 1) {  
   QApplication app(argc, argv);
   CalcDialog *dialog = new CalcDialog;
   dialog->show();
   return app.exec();
}

if (strlen(argv[1]) != 15) {
  printf("\n Invalid IMEI\n");
  return 0;
}

encrypt_v1(argv[1],codebuf,"e630upgrade");
printf("\n Flash code        = %s",codebuf);

encrypt_v1(argv[1],codebuf,"hwe620datacard");
printf("\n Encrypt_v1 code   = %s",codebuf);

calc2(argv[1],codebuf);
printf("\n Encrypt_v2 code   = %s",codebuf);

calc201(argv[1],codebuf);
printf("\n Encrypt_v201 code = %s\n\n",codebuf);
return 0;
}
