/****************************************************************
 ** Definition des methodes associees a la classe PRINCIPALE
 ****************************************************************/

#include "headers.h"

// Chargement des pixmap
#include "./images/filesave.xpm"
#include "./images/fileopen.xpm"
#include "./images/file_new.xpm"
#include "./images/icon1.xpm"
#include "./images/icon2.xpm"
#include "./images/icon3.xpm"
#include "./images/icon4.xpm"
#include "./images/icon5.xpm"
#include "./images/x.xpm"
#include "./images/prop.xpm"
#include "./images/cam1.xpm"
#include "./images/cam2.xpm"
#include "./images/cam3.xpm"

/*---------------------------------------------------------------------------
 * FONCTION: Principale
 * CLASSE  : Principale
 *
 * Constructeur
 *
 * entrees : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
Principale::Principale( void )
{
#ifdef DBG_MODE
  cout << "Constructeur de Principale\n";
#endif

  QPixmap openIcon, saveIcon, newIcon, boat1, boat2, boat3, boat4, boat5, x, prop, cam1, cam2, cam3;


  // chargement des pixmaps
#ifdef DBG_MODE
  cout << "Chargement des pixmaps\n";
#endif
  openIcon = QPixmap( fileopen );
  saveIcon = QPixmap( filesave );
  newIcon = QPixmap( file_new );
  boat1 = QPixmap( icon1_xpm );
  boat2 = QPixmap( icon2_xpm );
  boat3 = QPixmap( icon3_xpm );
  boat4 = QPixmap( icon4_xpm );
  boat5 = QPixmap( icon5_xpm );
  x = QPixmap( x_xpm );
  prop = QPixmap ( prop_xpm);
  cam1 = QPixmap( cam1_xpm);
  cam2 = QPixmap( cam2_xpm);
  cam3 = QPixmap( cam3_xpm);
    	
#ifdef DBG_MODE
  cout << "Creation d'une nouvelle fenetre\n";
#endif
  // Creer une fenetre principale
  fenetrePrincipale = new QMainWindow;
#ifdef DBG_MODE
  cout << "Fin Creation d'une nouvelle fenetre\n" << &fenetrePrincipale;
#endif


  // Si la configuration specifie l'utilisation d'un skin pour l'application,
  // definir la palette de couleur et l'incorpoer a la fenetre principale
#ifdef USE_SKIN
#ifdef DBG_MODE
  cout << "Construction de la palette pour le skin\n";
#endif
  QPalette p( QColor( 75, 123, 130 ) );
  p.setColor( QPalette::Active, QColorGroup::Base, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Inactive, QColorGroup::Base, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Disabled, QColorGroup::Base, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Active, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::HighlightedText, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Inactive, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::HighlightedText, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Disabled, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::HighlightedText, QColor( 55, 77, 78 ) );
  p.setColor( QPalette::Active, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::Foreground, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::Text, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::ButtonText, Qt::lightGray );
  fenetrePrincipale->setPalette( p, TRUE );
  //fenetrePrincipale->setFont( QFont( "times", QApplication::font().pointSize() ), TRUE );
#endif
    


  // Creation de la barre de status
#ifdef DBG_MODE
  cout << "Creation d'une status bar\n";
#endif
  QStatusBar* barreStatut = new QStatusBar( fenetrePrincipale );

  // Construire le widget pour la fenetre graphique
  graphique = new Graphique( fenetrePrincipale, "graphique", barreStatut, fenetrePrincipale );

  if ( !graphique->isValid() )
    {
      // Essayer sans double-buffering
      QGLFormat fmt( FALSE );
      graphique->setFormat( fmt );
      if ( !graphique->isValid() )
	fatal("Impossible de creer un contexte de rendu OpenGL sur cette station");
    }
  graphique->setMinimumSize( 1024, 768 );
  fenetrePrincipale->setCentralWidget( graphique );

#ifdef DBG_MODE
  cout << "Construction des items\n";
#endif

  // Creer trois menus
  // Menu Fichier:
  menuFichier = new QPopupMenu;
  menuFichier->insertItem( newIcon, "&Nouveau", this, SLOT(slotNouveau()), CTRL+Key_N);
  menuFichier->insertItem( openIcon, "&Lire", this, SLOT(slotLire()), CTRL+Key_L );
  menuFichier->insertSeparator();
  menuFichier->insertItem( saveIcon, "&Enregistrer", this, SLOT(slotSave()), CTRL+Key_S );
  menuFichier->insertItem( "Enregistrer &Sous", this, SLOT(slotSaveAs()) );
  menuFichier->insertSeparator();
  menuFichier->insertItem( "&Terminer", qApp, SLOT(quit()), Key_Q );
#ifdef USE_SKIN
  menuFichier->setPalette( p, TRUE );
#endif

  // Menu Aide:
  menuAide = new QPopupMenu;
  menuAide->insertItem( "&A propos du tp2" );
  menuAide->insertItem( "A propos de &Qt", this, SLOT( slotAproposQt() ) );
#ifdef USE_SKIN
  menuAide->setPalette( p, TRUE );
#endif

  // Menu Ajout de bateau
  QPopupMenu * bateaux = new QPopupMenu;
  bateaux->insertItem(boat1, "Contre-Torpilleur", this, SLOT(Nv_Bat1()), Key_1);
  bateaux->insertItem(boat2, "Sous-Marin", this, SLOT(Nv_Bat2()), Key_2);
  bateaux->insertItem(boat3, "Croiseur", this, SLOT(Nv_Bat3()), Key_3);
  bateaux->insertItem(boat4, "Cuirasse", this, SLOT(Nv_Bat4()), Key_4);
  bateaux->insertItem(boat5, "Porte-Avion", this, SLOT(Nv_Bat5()), Key_5);
#ifdef USE_SKIN
  bateaux->setPalette( p, TRUE );
#endif
    
  // Menu Edition:
  menuEdition = new QPopupMenu;
  menuEdition->insertItem("&Ajouter un bateau", bateaux);
  menuEdition->insertItem(x, "&Eliminer", graphique, SLOT(Delete_Objet()), Key_Delete);
  menuEdition->insertSeparator();
  menuEdition->insertItem(prop, "&Proprietes", graphique, SLOT(slotProprietes()));
#ifdef USE_SKIN
  menuEdition->setPalette( p, TRUE );
#endif

  //Menu Jouer:
  menuJouer = new QPopupMenu;
  menuJouer->insertItem("&Jouer!", this, SLOT(CommencerJeu()), Key_Return);
#ifdef USE_SKIN
  menuJouer->setPalette( p, TRUE );
#endif

  // Menu Camera:
  menuCamera = new QPopupMenu;
  menuCamera->insertItem(cam1, "&Camera 2D", this, SLOT(Cam_Mode1()), Key_H);
  menuCamera->insertItem(cam2, "&Orbiter en 3D", this, SLOT(Cam_Mode2()), Key_P);
  menuCamera->insertItem(cam3, "&Libre en 3D", this, SLOT(Cam_Mode3()), Key_S);
#ifdef USE_SKIN
  menuCamera->setPalette( p, TRUE );
#endif

#ifdef DBG_MODE
  cout << "Construction du menu\n";
#endif

  // Ajouter les sous-menus dans la barre de menu
  barreMenu = fenetrePrincipale->menuBar();

  //    barreMenu->setItemChecked(ID_CDE,TRUE);

  barreMenu->insertItem( "&Fichier", menuFichier );

  barreMenu->insertSeparator();
  menuEditionID = barreMenu->insertItem( "&Edition", menuEdition );

  barreMenu->insertSeparator();
  menuJeuID = barreMenu->insertItem( "&Jouer", menuJouer );

  barreMenu->insertSeparator();
  barreMenu->insertItem( "&Camera", menuCamera );

  barreMenu->insertSeparator();
  barreMenu->insertItem( "&Aide", menuAide );

  // Barre d'outils
  QToolBar* barreOutils = new QToolBar( fenetrePrincipale, "Fonctions Principales" );
  barreOutils->setLabel( "Fonctions Principales" );

  QToolButton* bouton1;
  bouton1 = new QToolButton(newIcon, "Nouvelle Partie", QString::null,
			    this, SLOT(slotNouveau()), barreOutils);
  QToolButton* bouton2;
  bouton2 = new QToolButton(openIcon, "Charger Partie", QString::null,
			    this, SLOT(slotLire()), barreOutils);
  QToolButton* bouton3;
  bouton3= new QToolButton(saveIcon, "Sauvergarder Partie", QString::null,
                           this, SLOT(slotSave()), barreOutils);


  QToolBar* barreEdition;
  barreEdition  = new QToolBar( fenetrePrincipale, "Ajout de bateaux" );
  barreEdition->setLabel( "Ajout de bateaux" );


  bouton11 = new QToolButton(boat1, "Contre-Torpilleur", QString::null,
			     this, SLOT(Nv_Bat1()), barreEdition);

  bouton12 = new QToolButton(boat2, "Sous-Marin", QString::null,
			     this, SLOT(Nv_Bat2()), barreEdition);

  bouton13 = new QToolButton(boat3, "Croiseur", QString::null,
			     this, SLOT(Nv_Bat3()), barreEdition);

  bouton14  = new QToolButton(boat4, "Cuirasse", QString::null,
			      this, SLOT(Nv_Bat4()), barreEdition);

  bouton15 = new QToolButton(boat5, "Porte-Avion", QString::null,
			     this, SLOT(Nv_Bat5()), barreEdition);

  bouton16 = new QToolButton(x, "Effacer Bateau", QString::null,
			     this, SLOT(Delete_Objet()), barreEdition);

  bouton17 = new QToolButton(prop, "Proprietes du Bateau", QString::null,
			     graphique, SLOT(slotProprietes()), barreEdition);

  QToolBar* barreCam = new QToolBar( fenetrePrincipale, "Mode de Camera" );
  barreCam->setLabel( "Mode de Camera" );

  QToolButton* camera1;
  camera1 = new QToolButton(cam1, "Mode 2D", QString::null,
			    this, SLOT(Cam_Mode1()), barreCam);
  QToolButton* camera2;
  camera2 = new QToolButton(cam2, "Mode 3D sur Sphere", QString::null,
			    this, SLOT(Cam_Mode2()), barreCam);
  QToolButton* camera3;
  camera3 = new QToolButton(cam3, "Mode 3D Libre", QString::null,
			    this, SLOT(Cam_Mode3()), barreCam);

  fenetrePrincipale->setCaption(QString("TuxBattleship 3d "));

#ifdef DBG_MODE
  cout << "Fin du constructeur de Principale\n";
#endif
}

/*---------------------------------------------------------------------------
 * FONCTION: Principale
 * CLASSE  : Principale
 *
 * Destructeur
 *
 * entrees : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/

Principale::~Principale()
{
  // Destruction de tous les objet de la classe
  if(fenetrePrincipale) delete fenetrePrincipale;
  if(menuFichier) delete menuFichier;
  if(menuEditer) delete menuEditer;
  if(menuAide) delete menuAide;
  if(menuEdition) delete menuEdition;
  if(menuCamera) delete menuCamera;
  if(menuJouer) delete menuJouer;
  if(bouton11) delete bouton11;
  if(bouton12) delete bouton12;
  if(bouton13) delete bouton13;
  if(bouton14) delete bouton14;
  if(bouton15) delete bouton15;
  if(bouton16) delete bouton16;
  if(bouton17) delete bouton17;
  if(barreMenu) delete barreMenu;
  if(graphique) delete graphique;
}

/*---------------------------------------------------------------------------
 * FONCTION: slotNouveau
 * CLASSE  : Principale
 *
 * Cree une nouvelle partie
 *
 * ENTREES : AUCUN
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotNouveau( void )
{
  // Appel New de graphique et efface le nom du fichier courant et reinitialise le titre de la fenetre
  graphique->New();
  QString s;
  File = s;
  fenetrePrincipale->setCaption(QString("TuxBattleship 3d"));
  UpdateButtons();

  // cout << "Passe dans Nouveau" << endl;
}

/*---------------------------------------------------------------------------
 * FONCTION: slotLire
 * CLASSE  : Principale
 *
 * Charge une partie
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotLire( void )
{
 

  // Une fenetre d'ouverture de fichier apparait et retourne le nom du fichier selectione
  QString s = QFileDialog::getOpenFileName(
					   "./",
					   "Save files (*.sav)",
					   this,
					   "Open Saved Game",
					   "Open Saved Game" );

  // Verifie si l'usager a choisi un fichier ou a mis annule
  if(!s.isEmpty())
    {
      // Lecture du fichier et reconfigure le titre de la fenetre
      File = s;
      graphique->Read(File);

      fenetrePrincipale->setCaption(QString("TuxBattleship 3d : [") + File + QString("]"));
    }

  // Selectionne ou deselectione les boutons selon le mode de jeu
  UpdateButtons();
}

/*---------------------------------------------------------------------------
 * FONCTION: slotSave
 * CLASSE  : Principale
 *
 * Sauvegarde une partie
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotSave( void )
{
    
  // S'il n'y a pas de fichier courant
  if(File.isEmpty())
    {

      // Demande le nom du fichier pour la sauvegarde
      QString s = QFileDialog::getSaveFileName(
					       "./",
					       "Save files (*.sav)",
					       this,
					       "Save Game as",
					       "Save Game as" );

      // Si un nom de fichier a ete entre 
      if(!s.isEmpty())
	{
	  // concatener l'extension si le nom entre ne contient pas l'extension .sav
	  if(s.contains(".sav") == false) s.append(".sav");
	  File = s;
	  // Ecriture dans le fichier et reconfiguration du titre de la fenetre
	  graphique->Write(File);
	  fenetrePrincipale->setCaption(QString("TuxBattleship 3d : [") + File + QString("]"));
	  QMessageBox::information( this, "TuxBattleship 3d",
				    "Your game was saved succesfully.\n");
	}
    }
  else
    graphique->Write(File);      // Sinon ecrire dans le fichier courant
}


/*---------------------------------------------------------------------------
 * FONCTION: slotSaveAs
 * CLASSE  : Principale
 *
 * Sauvegarde une partie sous un nouveau nom
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotSaveAs( void )
{
    
  // Demande le nom du fichier pour la sauvegarde
  QString s = QFileDialog::getSaveFileName(
					   "./",
					   "Save files (*.sav)",
					   this,
					   "Save Game as",
					   "Save Game as" );
  
  // Si un nom de fichier a ete entre 
 
  if(!s.isEmpty())
    {
      // concatener l'extension si le nom entre ne contient pas l'extension .sav
      if(s.contains(".sav") == false) s.append(".sav");
      File = s;
      // Ecriture dans le fichier et reconfiguration du titre de la fenetre
      graphique->Write(File);
      fenetrePrincipale->setCaption(QString("TuxBattleship 3d : [") + File + QString("]"));
      QMessageBox::information( this, "TuxBattleship 3d",
				"Your game was saved succesfully.\n");
    }
    
}



/*---------------------------------------------------------------------------
 * FONCTION: slotApropos
 * CLASSE  : Principale
 *
 *
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotApropos( void )
{
  
}

/*---------------------------------------------------------------------------
 * FONCTION: slotAproposQt
 * CLASSE  : Principale
 *
 *
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::slotAproposQt( void )
{
  QMessageBox::aboutQt( this, "About Qt" );
}

/*---------------------------------------------------------------------------
 * FONCTION: Nv_Bat1
 * CLASSE  : Principale
 *
 * Cree un nouveau bateau de type 1
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Nv_Bat1(void)
{
  if(graphique->GetEdit())
    NouveauBateau(graphique->obtenirCarte(), 1);
}

/*---------------------------------------------------------------------------
 * FONCTION: Nv_Bat3
 * CLASSE  : Principale
 *
 * Cree un nouveau bateau de type 3
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Nv_Bat2(void)
{
  if(graphique->GetEdit())
    NouveauBateau(graphique->obtenirCarte(), 2);
}

/*---------------------------------------------------------------------------
 * FONCTION: Nv_Bat3
 * CLASSE  : Principale
 *
 * Cree un nouveau bateau de type 3
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Nv_Bat3(void)
{
  if(graphique->GetEdit())
    NouveauBateau(graphique->obtenirCarte(), 3);
}


/*---------------------------------------------------------------------------
 * FONCTION: Nv_Bat4
 * CLASSE  : Principale
 *
 * Cree un nouveau bateau de type 4
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Nv_Bat4(void)
{
  if(graphique->GetEdit())
    NouveauBateau(graphique->obtenirCarte(), 4);
}

/*---------------------------------------------------------------------------
 * FONCTION: Nv_Bat5
 * CLASSE  : Principale
 *
 * Cree un nouveau bateau de type 5
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Nv_Bat5(void )
{
  if(graphique->GetEdit())
    NouveauBateau(graphique->obtenirCarte(), 5);
}

/*---------------------------------------------------------------------------
 * FONCTION: Delete_OBjet
 * CLASSE  : Principale
 *
 * Efface l'objet selectione si on est en mode d'edition
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Delete_Objet(void)
{
  if(graphique->GetEdit())
    graphique->obtenirCarte()->DeleteObject();
}

/*---------------------------------------------------------------------------
 * FONCTION: Cam_Mode1
 * CLASSE  : Principale
 *
 * Change le mode de camera au mode vue 2D
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Cam_Mode1(void)
{
  graphique->GetCam()->mode = 0;
  graphique->GetCam()->Refresh();
}

/*---------------------------------------------------------------------------
 * FONCTION: Cam_Mode2
 * CLASSE  : Principale
 *
 * Change le mode de camera au mode vue centree
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Cam_Mode2(void)
{
  graphique->GetCam()->mode = 1;
  graphique->GetCam()->Refresh();
}

/*---------------------------------------------------------------------------
 * FONCTION: Cam_Mode3
 * CLASSE  : Principale
 *
 * Change le mode de camera au mode vue a la premiere personne
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::Cam_Mode3(void)
{
  graphique->GetCam()->mode = 2;
  graphique->GetCam()->Refresh();
}

/*---------------------------------------------------------------------------
 * FONCTION: CommenrJeu
 * CLASSE  : Principale
 *
 * Quitte le mode d'edition pour passer en mode jeu
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/

void Principale::CommencerJeu()
{
  bool newEdit;
  if (graphique->GetEdit())
    {
      // Verifie si la partie peut commencer
      newEdit = !VerifierPlay(graphique->obtenirCarte());
      if (!newEdit)
	{
	  // Si la partie peut commencer, passer en mode de jeu et metttre a jour les boutons
	  graphique->SetEdit(newEdit);
	  UpdateButtons();
	}
    }
}

/*---------------------------------------------------------------------------
 * FONCTION: UpdateButtons
 * CLASSE  : Principale
 *
 * Active ou desactive les boutons selon le mode de jeu
 *
 * ENTREES :  :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Principale::UpdateButtons()
{
  // Si on est en mode d'edition, activation les menus et les boutons de la barre d'outil
  if(graphique->GetEdit())
    {
      bouton11->setEnabled(true);
      bouton12->setEnabled(true);
      bouton13->setEnabled(true);
      bouton14->setEnabled(true);
      bouton15->setEnabled(true);
      bouton16->setEnabled(true);
      bouton17->setEnabled(true);
      barreMenu->setItemEnabled(menuEditionID, true);
      barreMenu->setItemEnabled(menuJeuID, true);
      graphique->setMouseTracking(true);
    } else {    // Sinon desactiver ces memes elements
      bouton11->setEnabled(false);
      bouton12->setEnabled(false);
      bouton13->setEnabled(false);
      bouton14->setEnabled(false);
      bouton15->setEnabled(false);
      bouton16->setEnabled(false);
      bouton17->setEnabled(false);
      barreMenu->setItemEnabled(menuEditionID, false);
      barreMenu->setItemEnabled(menuJeuID, false);
      graphique->setMouseTracking(false);
    }
}
