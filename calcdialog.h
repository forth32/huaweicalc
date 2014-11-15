#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "ui_calc.h"
     
class CalcDialog: public QDialog, public Ui_CalcDialog {
      Q_OBJECT
   public:
      CalcDialog(QWidget *parent = 0);
   public slots: 
      void calc();
      void reverse();
};

    