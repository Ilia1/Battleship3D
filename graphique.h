#ifndef _HEADER_GRAPHIQUE_H_
#define _HEADER_GRAPHIQUE_H_

#include "headers.h"
//Added by qt3to4:
#include <QMouseEvent>
#include <QTimerEvent>
#include <QKeyEvent>
//#include <Q3PopupMenu>


/**
 * @class  Graphique
 * @brief  Définition d'une classe de base contenant le `widget' graphique.

 * Définition de la classe principale permettant de tracer dans une fenêtre
 * OpenGL. Les principales fonctions de cette classe sont déjà implantées,
 * et le travail qu'il reste à faire concerne surtout l'interaction avec
 * l'usager et l'affichage des objets.
 */
class Graphique : public QGLWidget
{
  Q_OBJECT
    public:
  Graphique( QWidget* parent, const char* name, QStatusBar *status ,   QMainWindow* fenetrePrincipale );
  ~Graphique( void );

  // accesseurs et modificateurs
  inline void modifier( Transformation *t ) { trans = t; };
  inline void modifier( CarteNavale *s ) { leModele = s; };
  inline Transformation *obtenirTransf( void ) { return( trans ); };
  inline CarteNavale *obtenirCarte( void ) { return( leModele); };
  Transformation * GetTrans() { return trans; };

  void New();
  void Write(QString = QString("save.sav"));
  void Read(QString = QString("save.sav"));
  int GetWidth(){return width;}
  int GetHeight(){return height;}


  ClasseCamera * GetCam() { return CameraGlobale; };

  int ObtenirObjet ( double, double, double, double, bool );
  int GetGrid(int , int , double , double , double &,double &, bool &);
  void SetFPS(int fps) { fpsec = fps; };
  bool GetEdit() { return Edit; };
  void SetEdit(bool newEdit) { Edit = newEdit; };
  QStatusBar* GetStatus(void) { return statusbar; };

  Models3D * GetModele3D(void) { return lesModeles3D; };

  Terrain * GetTerrain(void) { return solmarin; };

  float GetTemps(void) { return temps; };
   


 protected:
  void initializeGL( void );
  void paintGL( void );
  void resizeGL( int w, int h );
  void timerEvent( QTimerEvent *);



  void mousePressEvent( QMouseEvent* );
  void mouseMoveEvent( QMouseEvent* );
  void keyPressEvent( QKeyEvent* );
   
  private slots:
    void Delete_Objet( void );
  void Deplacer_Objet( void );
  void slotProprietes( void );

 private:
  QMainWindow* fenetrePrincipale;
  bool PriseEnChargeKeys(QKeyEvent*);
  bool PriseEnChargeKeysEdition(QKeyEvent*);
  bool PriseEnChargeKeysEdit(QKeyEvent*);
  bool PriseEnChargeMousePlay(QMouseEvent*);
  void PriseEnChargeMouseEdit(QMouseEvent*);

  float light_position[4];
  float spotlight_position[4];
  float spot_direction[3];
  float ambience[4];
  float diffuse[4];
  float specular[4];
   
  Transformation  *trans;
  CarteNavale     *leModele;
  int   width, height, screen, mode;
  ClasseCamera *CameraGlobale;
  float temps;			// temps en secondes
  float tempsincr;
  bool pause;
  bool Edit, tour, end;
  int tmp;
  QString fpsstring;
  int fpsec;
  QStatusBar *statusbar;
  QMenu* menuPopup;
  Models3D * lesModeles3D;
  Terrain *solmarin;
};


#endif
