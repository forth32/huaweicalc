#include <stdio.h>
#include <stdlib.h>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include "calcdialog.h"
#include "encrypt.h"


CalcDialog::CalcDialog(QWidget *parent) : QDialog(parent) {
      setupUi(this);
      imei->setFocus();
}

void CalcDialog::calc() {
  
char imeibuf[30];
char codebuf[30];
QMessageBox errBox;


strcpy(imeibuf,imei->text().toAscii());
if (strlen(imeibuf) != 15) {
  errBox.setText("Incorrect IMEI");
  errBox.exec();
  return;
}

encrypt_v1(imeibuf,codebuf,"e630upgrade");
flashcode->setText(codebuf);

encrypt_v1(imeibuf,codebuf,"hwe620datacard");
v1code->setText(codebuf);

calc2(imeibuf,codebuf);
v2code->setText(codebuf);

calc201(imeibuf,codebuf);
v201code->setText(codebuf);
}
