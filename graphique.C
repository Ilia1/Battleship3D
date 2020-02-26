#include "headers.h"
//Added by qt3to4:
#include <QTimerEvent>
#include <QKeyEvent>
#include <Q3PopupMenu>
#include <QMouseEvent>

/**
 * @fn  Graphique::Graphique( void )
 *
 *
 *
 * @return void
 * @exception
 *
 */
Graphique::Graphique( QWidget* parent, const char* name, QStatusBar * status , Q3MainWindow * fenetreP)
  : QGLWidget( parent, name )
{
#ifdef DBG_MODE
  cout << "Constructeur de Graphique\n";
#endif

  startTimer( 5 );
  temps = 15.0f;
  tempsincr = 0.005f;
  pause = false;
  Edit = true;
  end = false;
  tour = true;

  trans = new Transformation( this, -20.0, 20.0, -20.0, 20.0 );
  solmarin = new Terrain;
  leModele = new CarteNavale(this);
   
#ifdef DBG_MODE
  cout << "Creation des models\n";
#endif
  lesModeles3D = new Models3D(leModele->GetTextures());
#ifdef DBG_MODE
  cout << "Fin Creation des models\n";
#endif
   
  CameraGlobale = new ClasseCamera(leModele->GetSky());
  // Permettre a l'usager d'utiliser le clavier dans la fenetre graphique
  setFocusPolicy( Qt::StrongFocus );

  // Initialiser la Camera
  CameraGlobale->mode = 1;
  CameraGlobale->Refresh();

  setMouseTracking(true);

  statusbar = status;

  fenetrePrincipale = fenetreP;


  // Construire le menu popup
  menuPopup = new Q3PopupMenu();
  menuPopup->insertItem( "&Deplacer", this, SLOT( Deplacer_Objet() ), 0, 1 );
  menuPopup->insertItem( "&Eliminer", this, SLOT( Delete_Objet() ), 0, 2 );
  menuPopup->insertItem( "&Proprietes...", this, SLOT( slotProprietes() ), 0, 3 );

#ifdef USE_SKIN
  QPalette p( QColor( 75, 123, 130 ) );
  p.setColor( QPalette::Active, QColorGroup::Base, QColor( SKIN1_, SKIN2_, SKIN3_ ) );
  p.setColor( QPalette::Inactive, QColorGroup::Base, QColor(SKIN1_ ,SKIN2_ , SKIN3_ ) );
  p.setColor( QPalette::Disabled, QColorGroup::Base, QColor(SKIN1_ ,SKIN2_ ,SKIN3_  ) );
  p.setColor( QPalette::Active, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::HighlightedText, QColor(SKIN1_ ,SKIN2_ ,SKIN3_  ) );
  p.setColor( QPalette::Inactive, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::HighlightedText, QColor( SKIN1_,SKIN2_ ,SKIN3_  ) );
  p.setColor( QPalette::Disabled, QColorGroup::Highlight, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::HighlightedText, QColor( SKIN1_,SKIN2_ ,SKIN3_  ) );
  p.setColor( QPalette::Active, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Active, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Foreground, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::Text, Qt::white );
  p.setColor( QPalette::Inactive, QColorGroup::ButtonText, Qt::white );
  p.setColor( QPalette::Disabled, QColorGroup::Foreground, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::Text, Qt::lightGray );
  p.setColor( QPalette::Disabled, QColorGroup::ButtonText, Qt::lightGray );
  menuPopup->setPalette( p, TRUE );
#endif

#ifdef DBG_MODE
  cout << "Fin du constructeur de Graphique\n";
#endif
}


/**
 * @fn  Graphique::~Graphique( void )
 *
 *
 *
 * @return void
 * @exception
 *
 */
Graphique::~Graphique( void )
{
  if(trans) delete trans;
  if(leModele) delete leModele;
  if(CameraGlobale) delete CameraGlobale;
  if(statusbar) delete statusbar;
  if(lesModeles3D) delete lesModeles3D;
  if(menuPopup) delete menuPopup;
  if(solmarin) delete solmarin;
}

/**
 * @fn  void Graphique::initializeGL()

 * @return void
 *
 */
void Graphique::initializeGL()
{
  // Initialiser la couleur de fond
  glClearColor( 1.0, 1.0, 1.0, 1.0 );

  // Initialiser les lumieres
  ambience[0] = 0.7f;
  ambience[1] = 0.7f;
  ambience[2] = 0.7f;
  ambience[3] = 1.0f;
  diffuse[0] = 1.0f;
  diffuse[1] = 1.0f;
  diffuse[2] = 1.0f;
  diffuse[3] = 1.0f;
  specular[0] = 1.0f;
  specular[1] = 1.0f;
  specular[2] = 1.0f;
  specular[3] = 1.0f;
  light_position[0] = 0.0f;
  light_position[1] = 0.0f;
  light_position[2] = 5.0f;
  light_position[3] = 1.0f;
  spotlight_position[0] = 11.0f;
  spotlight_position[1] = 66.25f;
  spotlight_position[2] = 19.0f;
  spotlight_position[3] = 1.0f;
  spot_direction[0] = 0.5f;
  spot_direction[1] = 0.0f;
  spot_direction[2] = -1.0f;

  glLightfv( GL_LIGHT0, GL_AMBIENT, ambience );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv( GL_LIGHT0, GL_POSITION, light_position);
  glEnable( GL_LIGHT0 );

  glLightfv( GL_LIGHT1, GL_SPECULAR, specular );
  glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv( GL_LIGHT1, GL_POSITION, spotlight_position);
  glLightfv( GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
  glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f );
  glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 128.0f );
  glEnable( GL_LIGHT1);
   
  glEnable( GL_LIGHTING );
  glEnable( GL_COLOR_MATERIAL );
   
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  // Initialiser le modèle d'ombrage
  glShadeModel( GL_SMOOTH );
   
  // Initialiser l'utilisation de la coordonnée Z
  //glDepthFunc( GL_LEQUAL );
  glEnable( GL_DEPTH_TEST );
   
  // Textures on
  glEnable(GL_TEXTURE_2D);
   
  // Initialiser le viewport et un frustum
  glViewport(0, 0, 1024, 768 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0f, 1.0f, 0.5f, 550.0f );
      
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  modifier( leModele );

  lesModeles3D->LoadModel("./models/sub.3ds");
  lesModeles3D->LoadModel("./models/porte.3ds");
  lesModeles3D->LoadModel("./models/light.3ds");
  lesModeles3D->LoadModel("./models/croiseur.3ds");
  lesModeles3D->LoadModel("./models/contretor.3ds");
  lesModeles3D->LoadModel("./models/cuirasse.3ds");
  lesModeles3D->LoadModel("./models/Palmtree.3ds");
  lesModeles3D->LoadModel("./models/skull.3ds");
  lesModeles3D->LoadModel("./models/bomb.3ds");

  // Generation du landscape
  solmarin->Init("./images/Terrain.raw", RAW_SIZE, 8);

  leModele->InitialiserCarte();
}

/**
 * @fn  void Graphique::paintGL()

 * @return void
 *
 */
void Graphique::paintGL()
{
  temps += tempsincr;
  glGetIntegerv(GL_RENDER_MODE,&mode);
 
  resizeGL(trans->GetWidth(), trans->GetHeight());

  // nettoyer l'écran
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  // night, day, lever, couche, une chance qu'on fait des maths :P
  glClearColor( (cosf((temps+15.0f) / 5.0f) + 1) / 2.5f, 0.0, (cosf((temps / 10.0f)) + 1) / 5, 1.0f );
   
  ambience[0] = 0.25f*cosf(0.1f*temps) + 0.4f;
  ambience[1] = 0.25f*cosf(0.1f*temps) + 0.4f;
  ambience[2] = 0.25f*cosf(0.1f*temps) + 0.4f;
  diffuse[0] = cosf(2.7f*(0.4347826087f*cosf(0.1f*temps+2)+0.55f)*(0.4347826087f*cosf(0.1f*temps-2)+0.55f));
  diffuse[1] = 0.4347826087f*cosf(0.1f*temps)+ 0.55f;
  diffuse[2] = 0.4347826087f*cosf(0.1f*temps)+ 0.55f;
  //light_position[0] = 0.0f;
  //light_position[1] = 5.0f;
  //light_position[2] = 5.0f;
  //light_position[3] = 1.0f;

  glLightfv( GL_LIGHT0, GL_AMBIENT, ambience );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );

  // Placer la camera
  gluLookAt(	CameraGlobale->Position.x, CameraGlobale->Position.y, CameraGlobale->Position.z,
		CameraGlobale->Vue.x, CameraGlobale->Vue.y, CameraGlobale->Vue.z,
		CameraGlobale->UpVecteur.x, CameraGlobale->UpVecteur.y, CameraGlobale->UpVecteur.z	);


  glPushMatrix();
  glTranslatef(spotlight_position[0], spotlight_position[1], spotlight_position[2]);
  glRotatef(temps * 120, 0.0f, 0.0f, 1.0f);
  glLightfv( GL_LIGHT1, GL_POSITION, spotlight_position );
  glLightfv( GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction );
  glPopMatrix();

  /*glPushMatrix();	
    glBegin( GL_LINES );
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(spotlight_position[0], spotlight_position[1], spotlight_position[2]);
    glEnd();
    glPopMatrix();*/

  glInitNames();
  glPushName(0);
   

  if ( mode != GL_SELECT )
    {
      glColor3f(1.0, 1.0, 1.0);
#ifndef NO_TEXT
      if(!Edit)
	{
	  renderText(10, 20, "Computer -> ", QFont("flexure", 14));
	  renderText(145, 20, leModele->BateauxEnnemi(), QFont("flexure", 14));
	  renderText(trans->GetWidth() - 125, 20, "Player -> ", QFont("flexure", 14));
	  renderText(trans->GetWidth() -30, 20, leModele->BateauxAllie(), QFont("flexure", 14));
	}
#endif
      //renderText(10, trans->GetHeight()- 10, "FPS : " ,  QFont("Arial Black", 10));
      //fpsstring.setNum(fpsec);
      //renderText(50, trans->GetHeight()- 10, fpsstring ,  QFont("Arial Black", 10));
      //fpsstring.setNum(fpsec);
      //statusbar->message(fpsstring);
    }

  fpsstring.setNum(fpsec);
  //statusbar->message(fpsstring);

  fpsstring.setNum(fpsec);

  //statusbar->message(fpsstring);

  if(fenetrePrincipale->caption().contains(QString("FPS"))) 
    {
      QString C = fenetrePrincipale->caption();
      C.truncate(C.find("FPS") - 5);
      fenetrePrincipale->setCaption(C);
    }

  fenetrePrincipale->setCaption(fenetrePrincipale->caption() + QString("     FPS : ") + fpsstring);

  // dessine le modele et son contenu
  leModele->afficher(temps);

  glPopName();

  // Fonction de calcul du FPS
  CalculFPS(this);
  if(end) 
    {
      if(CameraGlobale->mode == 1)
	CameraGlobale->DeplacerSurSphere(4, 0.01f);
    }
}

/**
 * @fn  void Graphique::resizeGL( int w, int h )

 * @return void
 *
 */
void Graphique::resizeGL( int w, int h )
{
  // initialiser la cloture
  trans->changerCloture(0, w, 0, h);
  trans->mettreAJourCloture( true );
  trans->ajusterFenetre( true );
}

void Graphique::timerEvent(QTimerEvent*)
{
  if(!pause)
    {
      //temps += tempsincr;
      updateGL();
      //CalculFPS(this);
      if(!Edit && !end)       
	end = leModele->VerifierGagnant();
          
      if(!tour && !Edit && !end)
	{
	  end = JeuOrdi(leModele);
	  tour = true;
	}

    }
}

void Graphique::mousePressEvent( QMouseEvent* ev )
{
  if (!pause)
    {
      if(end == false)
	{
	  if(Edit)
	    {
	      if( leModele->GetSelectedObject() == NULL ) return;
	      if( leModele->GetSelectedObject()->Edition() )
		{
		  if(ev->button() == Qt::MidButton)
		    leModele->GetSelectedObject()->MouseReleaseEvent1(this, ev->x(), ev->y());
		  else if (ev->button() == Qt::LeftButton)
		    leModele->GetSelectedObject()->MouseReleaseEvent2(this);
		}
	      else
		{
		  PriseEnChargeMouseEdit(ev);
		  if(ev->button() == Qt::RightButton)
		    menuPopup->exec( QCursor::pos() );
		}
	    }
	  else
	    PriseEnChargeMousePlay(ev);
	}
    }
}

void Graphique::mouseMoveEvent( QMouseEvent* ev )
{
  updateGL();
  if (!pause)
    {
      if(end == false)
	{
	  if( leModele->GetSelectedObject() == NULL)
	    return;
	  if(Edit && leModele->GetSelectedObject()->Edition() )
	    leModele->GetSelectedObject()->MouseMotionEvent(ev, this);
	}
    }
}



void Graphique::Write(QString File)
{
  cout << "Saving...\n";
  ofstream out(File, ios::out);

  if(out.fail())
    {
      cerr << "Error opening file for writing\n";
      perror("write ");
    }
  else
    {
      out << Edit << " " << tour << " " << end << " " 
	  << pause << " " << temps <<  " " << tempsincr << " " 
	  << (const char *) fpsstring  << " " << fpsec << " " << endl;
      CameraGlobale->Write(out);
      leModele->Write(out);
      
      out.close();
      
      cout << "Save completed successfully\n";
    }

  
}

void Graphique::Read(QString File)
{
  ifstream in(File);

  string temp;
  in >> Edit >> tour >> end >> pause
     >> temps >> tempsincr
     >> temp >> fpsec;
  fpsstring = temp.c_str();

  if(leModele) delete leModele;

  leModele = new CarteNavale(this);

  CameraGlobale->Read(in);

  leModele->Read(in);

  in.close();
}

void Graphique::New()
{
  Edit = true;
  tour = true;
  end = false;
  pause = false;
  temps = 0;
  
  if(leModele) delete leModele;

  leModele = new CarteNavale(this);

  leModele->InitialiserCarte();

  CameraGlobale->mode = 1;
  CameraGlobale->Refresh();

}


void Graphique::keyPressEvent( QKeyEvent* ev )
{
  if (!pause)
    {
	
      if (Edit)
	{
	  if(ev->key() == Qt::Key_Return)
	    {
	      return;
	    }
	}
        
      if(end == false)
        {
	  if (Edit)
	    PriseEnChargeKeysEdit(ev);
	  else
	    PriseEnChargeKeys(ev);
        }
      else
        {
	  PriseEnChargeKeys(ev);
        }
	
    }
  if ( ev->key() == Qt::Key_Space)
    pause = !pause;
}

bool Graphique::PriseEnChargeKeys(QKeyEvent* ev)
{
  switch( ev->key() )
    {
    case Qt::Key_Right:
      //      cout << "right" << endl;
      if (int(CameraGlobale->mode) == 0)
	CameraGlobale->Deplacer(2, 0.5f);
      else 
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->DeplacerSurSphere(2, 0.03f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->DeplacerOrigine(2, 0.05f);
	}
      return true;
    case Qt::Key_Left:
      //      cout << "left" << endl;
      if (CameraGlobale->mode == 0)
	CameraGlobale->Deplacer(4, 0.5f);
      else 
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->DeplacerSurSphere(4, 0.03f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->DeplacerOrigine(4, 0.05f);
	}
      return true;
    case Qt::Key_Down:
      //      cout << "down" << endl;
      if (CameraGlobale->mode == 0)
	CameraGlobale->Deplacer(3, 0.5f);
      else
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->DeplacerSurSphere(3, 0.03f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->DeplacerOrigine(3, 0.05f);
	}
      return true;
    case Qt::Key_Up:
      //      cout << "up" << endl;
      if (CameraGlobale->mode == 0)
	CameraGlobale->Deplacer(1, 0.5f);
      else
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->DeplacerSurSphere(1, 0.03f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->DeplacerOrigine(1, 0.05f);
	}
      return true;
    case Qt::Key_Plus:
    case Qt::Key_Equal:
      //      cout << "zoomin" << endl;
      if (CameraGlobale->mode == 0)
	CameraGlobale->Deplacer(5, 0.5f);
      else 
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->AvancerVersVue(0.02f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->AvancerVersVue(0.05f);
	}
      return true;
    case Qt::Key_Minus:
    case Qt::Key_Underscore:
      //      cout << "zoomout" << endl;
      if (CameraGlobale->mode == 0)
	CameraGlobale->Deplacer(6, 0.5f);
      else
	{
	  if (CameraGlobale->mode == 1)
	    CameraGlobale->AvancerVersVue(-0.02f);
	  else if(CameraGlobale->mode == 2)
	    CameraGlobale->AvancerVersVue(-0.05f);
	}
      return true;
    case Qt::Key_T:
      if(tempsincr <= 5.0f)
	tempsincr += 0.005f;
      leModele->GetText()->addText("Temps acceleree", 0);
      break;
    case Qt::Key_R:
      if(tempsincr >= 0.0025f)
	tempsincr -= 0.0025f;
      leModele->GetText()->addText("Temps ralenti", 0);
      break;
      /*case Key_P:
	CameraGlobale->mode = 1;
	CameraGlobale->Refresh();
	return true;
	case Key_H:
	CameraGlobale->mode = 0;
	CameraGlobale->Refresh();
	return true;
	case Key_S:
	CameraGlobale->mode = 2;
	CameraGlobale->Refresh();
	return true;*/

    case Qt::Key_F:
      leModele->AugmenterGamma();
      break;
    case Qt::Key_G:
      leModele->DiminuerGamma();
      break;
    case Qt::Key_J:
      leModele->AugmenterDetail();
      break;
    case Qt::Key_K:
      leModele->DiminuerDetail();
      break;
      
    case Qt::Key_W:
      cout << "\nSaving...";
      Write();
      cout << "\nSave completed\n";
      break;
    case Qt::Key_L:
      cout << "\nLoading...";
      Read();
      cout << "\nLoad completed\n";
      break;

    case Qt::Key_E:
      cout << "checking error...\n";
      GLenum error;
      error = glGetError();
      if( error != GL_NO_ERROR)
	cout << "got error : " << gluErrorString(error) << endl;
      break;

    case Qt::Key_I:
      cout << *leModele;
      CameraGlobale->Afficher();
      return true;
    case Qt::Key_Greater:
      temps += 5;
      return true;
    case Qt::Key_Less:
      temps -= 5;
      return true;
      /*case Key_t:
	case Key_T:
	cout << "Temps : " << leModele->GetTemps();
	return true;*/
    }
  return false;
}

bool Graphique::PriseEnChargeKeysEdition(QKeyEvent * ev)
{ 
  if(PriseEnChargeKeys(ev)) 
    return true;
  if(leModele->GetSelectedObject() == NULL)
    return false;
  switch(ev->key())
    {
    case Qt::Key_BracketLeft:
      leModele->GetSelectedObject()->DiminuerTaille(leModele);
      return true;
    case Qt::Key_BracketRight:
      leModele->GetSelectedObject()->AugmenterTaille(leModele);
      return true;
    }
  return false;
}

bool Graphique::PriseEnChargeKeysEdit(QKeyEvent * ev)
{
  if(PriseEnChargeKeysEdition(ev))
    return true;

  switch(ev->key())
    {
      /*case Key_1:
	NouveauBateau( *&leModele, 1);
	return true;
	case Key_2:
	NouveauBateau( *&leModele, 2);
	return true;
	case Key_3:
	NouveauBateau( *&leModele, 3);
	return true;
	case Key_4:
	NouveauBateau( *&leModele, 4);
	return true;
	case Key_5:
	NouveauBateau( *&leModele, 5);
	return true;
	case Key_BackSpace:
	case Key_Delete:
	leModele->DeleteObject();
	return true;*/
    case Qt::Key_ParenRight:
    case Qt::Key_0:
      leModele->NextObject();
      return true;
    case Qt::Key_ParenLeft:
    case Qt::Key_9:
      leModele->PreviousObject();
      return true;
    }
  return false;
}

bool Graphique::PriseEnChargeMousePlay(QMouseEvent * ev)
{
  if(tour == false) 
    return false;
  
  double point_affichage[2] = { ev->x(), ev->y() };
  int Objet;
  
  Objet = ObtenirObjet ( point_affichage[0], point_affichage[1], 0.01, 0.01, 1);
  
  if(Objet > 200 || Objet < 101)
    return false;
  if(leModele->GetObjet(Objet)->GetEtatJeu() == 1)
    {
      leModele->GetText()->addText(MESSAGE_CASE_TESTED, 0);
      return false;
    }
  if(leModele->GetObjet(Objet)->GetEtat() == 2 && leModele->GetObjet(Objet)->GetEtatJeu() == 0)
    {
      tour = false;
      leModele->GetText()->addText(MESSAGE_TOUCH, 0);
      leModele->GetObjet(Objet)->SetEtatJeu(1);
      leModele->GetObjet(Objet)->Touche();
      if(leModele->GetObjet(leModele->GetObjet(Objet)->GetBateau())->VerifierCoule(leModele)) 
        leModele->GetText()->addText(MESSAGE_SINK, 0);
      return true;
    }
  if(leModele->GetObjet(Objet)->GetEtat() == 3 && leModele->GetObjet(Objet)->GetTouche() == 1)
    {
      leModele->GetText()->addText(MESSAGE_PERIPHERY_BOAT, 0);
      return false;
    }

  leModele->GetObjet(Objet)->SetEtatJeu(1);
  tour = false;
  return true;
}

void Graphique::PriseEnChargeMouseEdit(QMouseEvent * ev)
{
  double point_affichage[2] = { ev->x(), ev->y() };
  int Objet;
  Objet = ObtenirObjet ( point_affichage[0], point_affichage[1], 0.01, 0.01, 0);

#ifdef DBG_MODE
  cout << "point_affichage: " << point_affichage[0] << ", " << point_affichage[1] << endl;
  cout << "objet selectione: " << Objet << endl;
#endif

  if(Objet > 200 && Objet < 500)
    {
      menuPopup->setItemEnabled( 1, true );
      menuPopup->setItemEnabled( 2, true );
      menuPopup->setItemEnabled( 3, true );

      if(leModele->GetObjet(Objet)->GetSelect() && ev->button() == Qt::LeftButton)
	{
	  leModele->GetSelectedObject()->Edit();
	  leModele->RefreshBoats();
	}

        
      if(!(leModele->GetObjet(Objet)->GetSelect()))
        {
          leModele->GetSelectedObject()->UnSelect();
          leModele->GetObjet(Objet)->Selected();
        }
    } else {
      menuPopup->setItemEnabled( 1, false );
      menuPopup->setItemEnabled( 2, false );
      menuPopup->setItemEnabled( 3, false );
    }
}


// Fonction qui prend le clique de la souris
int Graphique::ObtenirObjet ( double x, double y, double larg_x, double larg_y, bool mode )
{
  int NombreObjets = 0;		// Le nombre d'objets selectionnes
  int ViewPort[4] = {0};
  unsigned int Selections[40] = {0};		// Infos des objets selectionnes

  glSelectBuffer(40, Selections);

  glGetIntegerv(GL_VIEWPORT, ViewPort);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();		// Sauvegarde pour restorer a la fin

  glRenderMode(GL_SELECT);
	
  glLoadIdentity();

  gluPickMatrix(x, ViewPort[3] - y, larg_x, larg_y, ViewPort);	// Creation du volume de vue autour du clique

  double width, height;

  width = GetTrans()->GetWidth();
  height = GetTrans()->GetHeight();

  gluPerspective( 45.0f, (width/height), 0.5f, 550.0f );

  glMatrixMode(GL_MODELVIEW);
	
  paintGL();

  NombreObjets = glRenderMode(GL_RENDER);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();		// Restoration

  glMatrixMode(GL_MODELVIEW);

  // Si des objets sont selectiones on determine celui le plus proche de l'ecran
  if ( NombreObjets > 0 )
    {
      if (!mode)
	{
	  unsigned int Zmin = Selections[1];

	  int CodeObjet;
	  CodeObjet = Selections[3];

	  for(int i = 1; i < NombreObjets; i++)
	    {
	      if(Selections[(i * 4) + 1] < Zmin)
		{
		  Zmin = Selections[(i * 4) + 1];
		  CodeObjet = Selections[(i * 4) + 3];
		}
	    }
		
	  return CodeObjet;
	  
	} else if ( mode ) {
	  int CodeObjet;
	  CodeObjet = Selections[3];

	  for(int i = 1; i < NombreObjets; i++)
	    {
	      if(Selections[(i * 4) + 3] < 201 && Selections[(i * 4) + 3] > 0 )
		{
		  CodeObjet = Selections[(i * 4) + 3];
		}
	    }
	  return CodeObjet;
	}
	    
    }

  // on retourne 0 si rien n'est selectione
  return 0;
}




// 
// GetGrid
//


int Graphique::GetGrid(int i, int j, double larg_x, double larg_y, double &x, double &y, bool &Allie)
{
  int cases;
  cases = ObtenirObjet ( i, j, larg_x, larg_y, 1 );
  
  if(( cases > 200) || (cases < 1) ) return -1;

  if ( cases <= 100 ) {
    Allie = true;
    x = cases % 10;
    if ( x == 0 ) {
      x = 10;
      y = int(cases/10);
    } else {
      y = int((cases / 10) + 1);
    }
    
    // On transforme en coordonnes du monde virtuel, on a le coin inferieur gauche
    x -= 6;
    y -= 11.5;
		  
  } else if ( cases >= 101 ) {
    int temp;

    Allie = false;

    temp = cases - 100;
    
    x = temp % 10;
    if ( x == 0 ) {
      x = 10;
      y = int(temp/10);
    } else {
      y = int((temp / 10) + 1);
    }
    
    // On transforme en coordonnes du monde virtuel, on a le coin inferieur gauche
    x -= 6;
    y -= 0.5;
    
  }

  return cases;
}

void Graphique::Delete_Objet(void)
{
  if(Edit)
    obtenirCarte()->DeleteObject();
}

void Graphique::Deplacer_Objet(void)
{
  if(Edit)
    {
      leModele->GetSelectedObject()->Edit();
      leModele->RefreshBoats();
    }
}

void Graphique:: slotProprietes(void)
{

  if(leModele->GetSelectedObject() != NULL )
    {
      PropertiesD * dlg = new PropertiesD(leModele);
      dlg->exec();
      delete dlg;
    }
}
