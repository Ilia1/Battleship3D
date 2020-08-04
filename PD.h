#ifndef PROPERTIESD_H
#define PROPERTIESD_H

#include "headers.h"

class PropertiesD : public QDialog
{
  Q_OBJECT

    public:
  PropertiesD( CarteNavale * carte, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
  ~PropertiesD();


  CarteNavale * carte;

  QPushButton ** Position;
  QPushButton* Appliquer;

  QGroupBox* Orientation;

  QRadioButton* Vertical;
  QRadioButton* Horizontal;

  QFrame* frame_Pos;
  QLineEdit* Pos;
  QComboBox* Type;

  QLabel* pixmap_Label;
  QLabel* type_label;
  QLabel* Position_label;

  QLabel* A;
  QLabel* B;
  QLabel* C;
  QLabel* D;
  QLabel* E;
  QLabel* F;
  QLabel* G;
  QLabel* H;
  QLabel* I;
  QLabel* J;

  QLabel* _1;
  QLabel* _2;
  QLabel* _3;
  QLabel* _4;
  QLabel* _5;
  QLabel* _6;
  QLabel* _7;
  QLabel* _8;
  QLabel* _9;
  QLabel* _10;


  protected slots:
    virtual void languageChange();
  virtual void Set_PixMap( int i );
  virtual void accept ();
  virtual void ChangeSize(int i);
  virtual void Rotate();
  virtual void ChangePos(void);
  void RefreshMap(void);

};

#endif // PD_H
