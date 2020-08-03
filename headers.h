#ifndef HEADERS_H
#define HEADERS_H


#define TGA_RGB      2      
#define TGA_A        3      
#define TGA_RLE     10    

#define RAW_SIZE 512

typedef unsigned char  byte;
typedef unsigned short WORD;

#include "config"

#ifdef FR
#include "Francais.lng"
#endif

#ifdef EN
#include "English.lng"
#endif

// Chargement des librairies standard
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <GL/gl.h>                                  // Header File For The OpenGL32 Library
#include <GL/glu.h>                                 // Header File For The GLu32 Library

// Chargement des librairies qt
#include <qgl.h>
#include <qcursor.h>    
#include <QMenu>
#include <QListWidget>  
#include <qnamespace.h>   
#include <qvariant.h>  
#include <qdialog.h>
#include <qpoint.h>
#include <qlineedit.h>   
#include <qcombobox.h>   
#include <qpushbutton.h>  
#include <qradiobutton.h>
#include <QGroupBox>      
#include <qlayout.h>   
#include <qtooltip.h>   
#include <QWhatsThis>   
#include <qimage.h>  
#include <qapplication.h>  
#include <qmessagebox.h>   
#include <QToolBar>   
#include <QToolButton>  
#include <qstatusbar.h> 
#include <QMenuBar>
#include <QMainWindow>
#include <qwidget.h>
#include <QFileDialog>
#include <QMouseEvent>
#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QAction>
#include <QIcon>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QObject>

// Declaration des classes
class Principale;
class Graphique;
class CarteNavale;
class Objet;
class Bateau;
class Case;
class ClasseCamera;
class Models3D;
class SkyDome;
class Terrain;
class Mer;
class Textures;
class Transformation;
class CLoad3DS;
class PropertiesD;
class ClasseText;

// Chargement des fichiers headers du programme
#include "principale.h"
#include "transf.h"
#include "3dsModel.h"
#include "camera.h"
#include "texture.h"
#include "classetext.h"
#include "mer.h"
#include "cartenavale.h"
#include "objet.h"
#include "bateau.h"
#include "case.h"
#include "skydome.h"
#include "terrain.h"
#include "3ds.h"
#include "model.h"
#include "graphique.h"
#include "tree.h"
#include "PD.h"









// prototypes des fonctions

bool RemoveSelected(Objet * );
bool VerifierPlay(CarteNavale *);
bool VerifierBateaux(CarteNavale * LaCarte);
bool JeuOrdi(CarteNavale *);
void CalculFPS(Graphique *);
void NouveauBateau( CarteNavale *, int);

void ExtDrawModel(t3DModel &);

int * Grid2coord(int grid);

void CalculFPS(float tempscourant);


#endif
