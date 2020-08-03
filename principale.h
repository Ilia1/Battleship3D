/*------------------------------------------------------------------------
 *  Classe principale servant au programme
 *------------------------------------------------------------------------*/

#ifndef _PRINCIPALE_H_
#define _PRINCIPALE_H_

#include "headers.h"

class Principale : public QWidget
{
  Q_OBJECT
    public:
  Principale( void );
  ~Principale();
  QMainWindow* getFenetrePrincipale( void ) { return fenetrePrincipale; };

  private slots:
    void slotNouveau();
  void slotLire();
  void slotSave();
  void slotSaveAs();
  void slotApropos();
  void slotAproposQt();
  void Nv_Bat1();
  void Nv_Bat2();
  void Nv_Bat3();
  void Nv_Bat4();
  void Nv_Bat5();
  void Delete_Objet();
  void Cam_Mode1();
  void Cam_Mode2();
  void Cam_Mode3();
  void CommencerJeu();
  void UpdateButtons();


 protected:
  QMainWindow* fenetrePrincipale;
  QMenu* menuFichier;
  QMenu* menuEditer;
  QMenu* menuAide;
  QMenu* menuEdition;
  QMenu* menuCamera;
  QMenu* menuJouer;
  QToolBar* barreOutils; 
  QToolButton* bouton11;
  QToolButton* bouton12;
  QToolButton* bouton13;
  QToolButton* bouton14;
  QToolButton* bouton15;
  QToolButton* bouton16;
  QToolButton* bouton17;
  QMenuBar* barreMenu;
  //int menuEditionID, menuJeuID;
  class Graphique* graphique;
  QString File;
};

#endif
