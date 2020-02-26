/****************************************************************************
 ** Form implementation generated from reading ui file 'proprieted.ui'
 **
 ** Created: Mon Mar 10 05:40:21 2003
 **      by: The User Interface Compiler ($Id: PD.cpp,v 1.1.1.1 2003/07/19 06:03:37 kakaroto Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "headers.h"

// Chargement des pixmap
#include "./images/icon1.xpm"
#include "./images/icon2.xpm"
#include "./images/icon3.xpm"
#include "./images/icon4.xpm"
#include "./images/icon5.xpm"
#include "./images/cam1.xpm"
//Added by qt3to4:
#include <Q3Frame>
#include <QPixmap>
#include <QLabel>

/* 
 *  Constructs a PD as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
PropertiesD::PropertiesD( CarteNavale * c, QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
  : QDialog( parent, name, modal, fl )

{
  int *HV = NULL;

  QString  temp;
    
  carte = c;
    
  if ( !name )
    setName( "Properties Dialog" );

  Appliquer = new QPushButton( this, CLOSE );
  Appliquer->setGeometry( QRect( 120, 520, 100, 40 ) );
  Appliquer->setDefault( TRUE );

  pixmap_Label = new QLabel( this, "pixmap_Label" );
  pixmap_Label->setGeometry( QRect( 10, 10, 100, 100 ) );
  pixmap_Label->setScaledContents( TRUE );

  Type = new QComboBox( FALSE, this, "Type" );
  Type->setGeometry( QRect( 130, 60, 181, 21 ) );
  Type->setMaxCount( 5 );

  type_label = new QLabel( this, "type_label" );
  type_label->setGeometry( QRect( 130, 20, 181, 21 ) );

  Orientation = new Q3GroupBox( this, "Orientation" );
  Orientation->setGeometry( QRect( 20, 120, 291, 50 ) );

  Vertical = new QRadioButton( Orientation, VERTICAL );
  Vertical->setGeometry( QRect( 150, 20, 111, 20 ) );

  Horizontal = new QRadioButton( Orientation, HORIZONTAL );
  Horizontal->setGeometry( QRect( 30, 20, 111, 21 ) );
  Horizontal->setChecked( FALSE );

  Position_label = new QLabel( this, "Position" );
  Position_label->setGeometry( QRect( 70, 220, 221, 16 ) );

  frame_Pos = new Q3Frame( this, "frame_Pos" );
  frame_Pos->setGeometry( QRect( 60, 240, 240, 260 ) );
  frame_Pos->setFrameShape( Q3Frame::StyledPanel );
  frame_Pos->setFrameShadow( Q3Frame::Raised );

  Pos = new QLineEdit( frame_Pos, "Pos" );
  Pos->setGeometry( QRect( 10, 230, 201, 21 ) );

  J = new QLabel( frame_Pos, "J" );
  J->setGeometry( QRect( 220, 10, 16, 21 ) );

  G = new QLabel( frame_Pos, "G" );
  G->setGeometry( QRect( 220, 70, 16, 21 ) );

  H = new QLabel( frame_Pos, "H" );
  H->setGeometry( QRect( 220, 50, 16, 21 ) );

  A = new QLabel( frame_Pos, "A" );
  A->setGeometry( QRect( 220, 190, 16, 21 ) );

  B = new QLabel( frame_Pos, "B" );
  B->setGeometry( QRect( 220, 170, 16, 21 ) );

  F = new QLabel( frame_Pos, "F" );
  F->setGeometry( QRect( 220, 90, 16, 21 ) );

  E = new QLabel( frame_Pos, "E" );
  E->setGeometry( QRect( 220, 110, 16, 21 ) );

  D = new QLabel( frame_Pos, "D" );
  D->setGeometry( QRect( 220, 130, 16, 21 ) );

  I = new QLabel( frame_Pos, "I" );
  I->setGeometry( QRect( 220, 30, 16, 21 ) );

  C= new QLabel( frame_Pos, "C_" );
  C->setGeometry( QRect( 220, 150, 16, 21 ) );
  _1 = new QLabel( frame_Pos, "_1" );
  _1->setGeometry( QRect( 16, 210, 20, 20 ) );

  _2 = new QLabel( frame_Pos, "_2" );
  _2->setGeometry( QRect( 36, 210, 20, 20 ) );

  _3 = new QLabel( frame_Pos, "_3" );
  _3->setGeometry( QRect( 56, 210, 20, 20 ) );

  _4 = new QLabel( frame_Pos, "_4" );
  _4->setGeometry( QRect( 76, 210, 20, 20 ) );

  _5 = new QLabel( frame_Pos, "_5" );
  _5->setGeometry( QRect( 96, 210, 20, 20 ) );

  _6 = new QLabel( frame_Pos, "_6" );
  _6->setGeometry( QRect( 116, 210, 20, 20 ) );

  _7 = new QLabel( frame_Pos, "_7" );
  _7->setGeometry( QRect( 136, 210, 20, 20 ) );

  _8 = new QLabel( frame_Pos, "_8" );
  _8->setGeometry( QRect( 156, 210, 20, 20 ) );

  _9 = new QLabel( frame_Pos, "_9" );
  _9->setGeometry( QRect( 176, 210, 20, 20 ) );

  _10 = new QLabel( frame_Pos, "_10" );
  _10->setGeometry( QRect( 196, 210, 20, 20 ) );


  languageChange();

  Position = new QPushButton*[100];
    
  for(int i = 0; i < 100 ; i++)
    {
      if(HV) delete []HV;
      HV = Grid2coord(i+1);
	
      Position[i] = new QPushButton( frame_Pos, temp.setNum(i+1) );
      Position[i]->setGeometry( QRect((20 * HV[0]) + 10, 200 - (20 * HV[1]) - 10, 20, 20 ) );
	
      if(carte->GetObjet(i+1)->GetEtat() == 1 || carte->GetObjet(i+1)->GetEtat() == 3) 
	Position[i]->setPixmap(QPixmap(cam1_xpm ));
	
      connect( Position[i], SIGNAL( clicked() ), this, SLOT( ChangePos() ) );
    }
    
  Type->setCurrentItem(carte->GetSelectedObject()->GetType() - 1 );
  Set_PixMap(Type->currentItem());
    
  if(carte->GetSelectedObject()->GetDeg() == 0) 
    Horizontal->setChecked(true);
  else
    Vertical->setChecked(true);
    
  temp.setNum(carte->GetSelectedObject()->GetL0());
  Pos->setText(temp);

#ifdef USE_SKIN
  // Load the skin
  QPalette p( QColor( 75, 123, 130 ) );
  p.setColor( QPalette::Active, QColorGroup::Base, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Inactive, QColorGroup::Base, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Disabled, QColorGroup::Base, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Active, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::HighlightedText, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Inactive, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::HighlightedText, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Disabled, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::HighlightedText, QColor( SKIN1, SKIN2, SKIN3 ) );
  p.setColor( QPalette::Active, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::Foreground, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::Text, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::ButtonText, Qt::lightGray );
  setPalette( p, TRUE );
  //setFont( QFont( "times", QApplication::font().pointSize() ), TRUE );
#endif

  resize( QSize(356, 587).expandedTo(minimumSizeHint()) );

  // signals and slots connections
  connect( Appliquer, SIGNAL( clicked() ), this, SLOT( accept() ) );
  connect( Horizontal, SIGNAL( clicked() ), this, SLOT( Rotate() ) );
  connect( Vertical, SIGNAL( clicked() ), this, SLOT( Rotate() ) );
  connect( Type, SIGNAL( activated(int) ), this, SLOT( ChangeSize(int) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
PropertiesD::~PropertiesD()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PropertiesD::languageChange()
{
  setCaption( tr( CAPTION ) );
  Appliquer->setText( tr( CLOSE ) );
  pixmap_Label->setText( QString::null );
  Type->clear();
  Type->insertItem( tr( BAT1 ) );
  Type->insertItem( tr( BAT2 ) );
  Type->insertItem( tr( BAT3 ) );
  Type->insertItem( tr( BAT4 ) );
  Type->insertItem( tr( BAT5 ) );
  Type->setCurrentItem( 0 );
  type_label->setText( tr( TYPE ) );
  Orientation->setTitle( tr( DIRECTION ) );
  Vertical->setText( tr( VERTICAL ) );
  Horizontal->setText( tr( HORIZONTAL ) );
  Position_label->setText( tr( POSITION ) );
  Type->setCurrentItem( 0 );
  Pos->setText( QString::null );
  J->setText( tr( "J" ) );
  G->setText( tr( "G" ) );
  H->setText( tr( "H" ) );
  A->setText( tr( "A" ) );
  B->setText( tr( "B" ) );
  F->setText( tr( "F" ) );
  E->setText( tr( "E" ) );
  D->setText( tr( "D" ) );
  I->setText( tr( "I" ) );
  C->setText( tr( "C" ) );
  _1->setText( tr( "1" ) );
  _2->setText( tr( "2" ) );
  _3->setText( tr( "3" ) );
  _4->setText( tr( "4" ) );
  _5->setText( tr( "5" ) );
  _6->setText( tr( "6" ) );
  _7->setText( tr( "7" ) );
  _8->setText( tr( "8" ) );
  _9->setText( tr( "9" ) );
  _10->setText( tr( "10" ) );
}

void PropertiesD::accept()
{
  close();
}

void PropertiesD::ChangeSize(int i)
{
  carte->GetSelectedObject()->SetType(carte, i + 1);
  Type->setCurrentItem(carte->GetSelectedObject()->GetType() - 1 );
  Set_PixMap(Type->currentItem());
  RefreshMap();
}


void PropertiesD::Rotate()
{
  carte->GetSelectedObject()->RotateSurPlace(carte);
  RefreshMap();
  if(carte->GetSelectedObject()->GetDeg() == 0) 
    {
      Horizontal->setChecked(true);
      Vertical->setChecked(false);
    }
  else
    {
      Vertical->setChecked(true);
      Horizontal->setChecked(false);
    }
}

void PropertiesD::RefreshMap(void)
{
  for(int i = 0; i < 100 ; i++)
    {
      if(carte->GetObjet(i+1)->GetEtat() == 1 || carte->GetObjet(i+1)->GetEtat() == 3) 
	Position[i]->setPixmap(QPixmap(cam1_xpm ));
      else
	Position[i]->setPixmap(0);
    }
}

void PropertiesD::ChangePos(void)
{
  QString tempstring = sender()->name();
  int gridid = tempstring.toInt();
  carte->GetSelectedObject()->MoveBoat(carte, gridid);
  RefreshMap();

  tempstring.setNum(carte->GetSelectedObject()->GetL0());
  Pos->setText(tempstring);
#ifdef DEBUG_
  cout << "called change pos on : " << gridid;
#endif
}

void PropertiesD::Set_PixMap( int i)
{

 
  if(i == 0)
    pixmap_Label->setPixmap(QPixmap( (const char **) icon1_xpm ));
  if(i == 1)
    pixmap_Label->setPixmap(QPixmap((const char **)  icon2_xpm ));
  if(i == 2)
    pixmap_Label->setPixmap(QPixmap( (const char **) icon3_xpm ));
  if(i == 3)
    pixmap_Label->setPixmap(QPixmap( (const char **) icon4_xpm ));
  if(i == 4)
    pixmap_Label->setPixmap(QPixmap((const char **)  icon5_xpm ));
}


int * Grid2coord(int i)
{
  int *HV = new int[2];

  HV[0] = i%10 -1;
  if(HV[0] == -1 ) HV[0] = 9;

  HV[1] = (i - HV[0] -1) / 10;
  if(HV[1] == -1) HV[1] = 9;

  return HV;
}

