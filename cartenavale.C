#include "headers.h"

#include <GL/glext.h>

/**
 * @fn  CarteNavale::CarteNavale( void )
 *
 * Fonction d'initialisation d'une nouvelle scène
 *
 * @return void
 * @exception
 *
 */
CarteNavale::CarteNavale( Graphique *PtrGraph )
{
  LeGraph = PtrGraph;
  NbreBateaux =0;
  //solmarin = new Terrain;
  solmarin = LeGraph->GetTerrain();
  ciel = new SkyDome;
  //soleil = new SkyDome;
  saMere = new Mer;
  ListTextures = new Textures;

  BateauxCoulesAllie = NULL;
  BateauxCoulesEnnemi = NULL;
  gamma = 2;
  detail = 4;
  Messages = new ClasseText;
  pObj = gluNewQuadric();                // Get a new Quadric off the stack

  gluQuadricTexture(pObj, true);                        // This turns on texture coordinates for our Quadrics

}

/**
 * @fn  const CarteNavale& CarteNavale::operator=( const Scene& b )
 *
 * operator=
 *
 * @param const CarteNavale& b :
 * @return void
 * @exception
 *
 
 const CarteNavale& CarteNavale::operator=( const CarteNavale& b )
 {
 return( *this );
 }*/

/**
 * @fn  CarteNavale::~CarteNavale( void )
 *
 * Destructeur.
 *
 * @return void
 * @exception
 *
 */
CarteNavale::~CarteNavale( void )
{

  // On suppose qu'un Objet n'est pas dans plusieurs scènes,
  // donc on efface tous les Objets
  while(!objets.empty())
    {
      delete objets.front();
      objets.pop_front();
    }
  if(BateauxCoulesAllie) delete BateauxCoulesAllie;
  if(BateauxCoulesEnnemi) delete BateauxCoulesEnnemi;

  if(ciel) delete ciel;
  //if(solmarin) delete solmarin;
  if(Messages) delete Messages;
  if(saMere) delete saMere;

}

Models3D * CarteNavale::GetModels()
{ 
  return LeGraph->GetModele3D(); 
};

/**
 * @fn  void CarteNavale::afficher( const Temps &t ) const
 *
 * Afficher la scène et son contenu
 *
 * @param t : temps courant.
 * @return void
 * @exception
 *
 */
void CarteNavale::afficher( float temps )
{
  glActiveTextureARB(GL_TEXTURE0_ARB);
  glEnable(GL_TEXTURE_2D);
  ListTextures->BindTexture("./images/Terrain.tga");
  
  // Activate the second texture ID and bind the fog texture to it
  glActiveTextureARB(GL_TEXTURE1_ARB);
  glEnable(GL_TEXTURE_2D);
  
  // Here we turn on the COMBINE properties and increase our RGB
  // gamma for the detail texture.  2 seems to work just right.
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLenum) GL_COMBINE_EXT );
  glTexEnvi(GL_TEXTURE_ENV, (GLenum)GL_RGB_SCALE_EXT, GL_DOT3_RGB_EXT);
  
  // Bind the detail texture
  ListTextures->BindTexture("./images/sand.tga");
  
  // Now we want to enter the texture matrix.  This will allow us
  // to change the tiling of the detail texture.
  glMatrixMode(GL_TEXTURE);
  
  // Reset the current matrix and apply our chosen scale value
  glLoadIdentity();
  glScalef(detail, detail, 1);
  
  // Leave the texture matrix and set us back in the model view matrix
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glScalef(0.4, 0.4, 0.4); 
  //glScalef(0.09, 0.09, 0.15); 
  glTranslatef(-RAW_SIZE*0.75f, -RAW_SIZE/2, -45.0);
  solmarin->Afficher();
  
  // Turn the second multitexture pass off
  glActiveTextureARB(GL_TEXTURE1_ARB);
  glDisable(GL_TEXTURE_2D);
  
  // Turn the first multitexture pass off
  glActiveTextureARB(GL_TEXTURE0_ARB);        
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glPopMatrix();

  glEnable(GL_BLEND);
  ListTextures->BindTexture("./images/sky.tga");

  glColor3f( (cosf((temps+15.0f) / 5.0f) + 1) / 2.5f, (cosf((temps / 10.0f)) + 1) / 4, (cosf((temps / 10.0f)) + 1) / 2 );
  

  ciel->Afficher(temps);

  /*  glDisable(GL_LIGHTING);
      glPushMatrix();
      glTranslatef(-60.0f, 0.0, 0.0f);

      glRotatef((temps/0.005)*0.05f, 0.0, 0.0, 1.0); 
      glRotatef(90.0, 0.0, 1.0, 0.0); 
      gluSphere(pObj, 160, 500, 500);

      glPopMatrix();

      glEnable(GL_LIGHTING);*/

  glDisable(GL_BLEND);

  glEnable(GL_BLEND);

  
  ListTextures->BindTexture("./images/sun.tga");


  glPushMatrix();

  glColor3f((cosf((temps+15.0f) / 5.0f) + 1) / 2.5f , (cosf((temps / 10.0f)) + 1) / 2, 0.0);

  glTranslatef(-60.0f, 0.0, 0.0f);

  //glColor3f(1.0, 1.0, 0.0);
  glRotatef(170.0, 0.0, 1.0, 0.0); 
  glRotatef(180.0, 0.0, 0.0, 1.0); 
  glRotatef(6*temps , 1.0, 0.0, 0.0); 

  gluSphere(pObj, 150, 500, 500);


  glPopMatrix();  
 
  glDisable(GL_BLEND);

  if(((int)(6*temps))%360 < 110 || ((int)(6 * temps))%360 > 240)
    glDisable(GL_LIGHT1);
  else
    glEnable(GL_LIGHT1);

  //Placer les objets < 200 (donc tout sauf le grid)
  list<Objet*>::const_iterator premier = objets.begin();
  list<Objet*>::const_iterator obj ;
  for(obj = objets.end(), obj--; obj != premier; --obj)
    {
      if((*obj)->GetID() == 200)
	break;
      (*obj)->afficher();
    }

  glLoadName(0);

  /*
    ListTextures->BindTexture("./images/water.tga");
    glColor4f(1.0, 1.0, 1.0, 0.75f);
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-95.0,  95.0,  -0.6);
    glTexCoord2f(0.0f, 4.0f);
    glVertex3d(95.0,  95.0, -0.6);
    glTexCoord2f(4.0f, 4.0f);
    glVertex3d(95.0, -95.0, -0.6);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3d(-95.0, -95.0,  -0.6);
    glEnd();
    glDisable(GL_BLEND);*/

  glPushMatrix();
  glTranslatef(14.0f, 66.0f, 3.0f);
  glScalef(0.1f, 0.1f, 0.1f);
  glRotatef(-180, 0.0f, 0.0f, 1.0f);
  LeGraph->GetModele3D()->DrawModel("./models/light.3ds");
  glPopMatrix();

  ListTextures->BindTexture("./images/water.tga");

  saMere->Afficher(ListTextures, 0.5, 0.1f, LeGraph->GetTemps());


  glEnd();

  //Placer le grid
  for(; obj != premier; --obj)
    {
      (*obj)->afficher();
    }
  (*obj)->afficher();

  Messages->afficher(LeGraph);  

}

Objet * CarteNavale::GetObjet(int ID)
{
  list<Objet*>::const_iterator dernier = objets.end();
  for(list<Objet*>::const_iterator obj = objets.begin(); obj != dernier; ++obj)
    {
      if((*obj)->GetID() == ID) return *obj;
    }
  return NULL;
}

Objet * CarteNavale::GetSelectedObject()
{
  list<Objet*>::const_iterator dernier = objets.end();
  for(list<Objet*>::const_iterator obj = objets.begin(); obj != dernier; ++obj)
    {
      if((*obj)->GetSelect()) return *obj;
    }
  return NULL;
}


void CarteNavale::RotateObjet(int ID)
{
  Objet *obj;
  obj = GetObjet(ID);
  if(obj != NULL) obj->Rotate();
}

void CarteNavale::NextObject()
{

  int ID = 0;

  bool Trouve = false;

  if (NbreBateaux < 2 ) return;

  list<Objet*>::const_iterator dernier = objets.end();
  list<Objet*>::const_iterator obj;
  for(obj = objets.begin(); obj != dernier; ++obj)
    {
      if(!GetSelectedObject())break;
      if((*obj)->GetSelect())
	{
	  ID = (*obj)->GetID();
	  continue;
	}
      if (ID != 0 && (*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	{
	  GetSelectedObject()->UnSelect();
	  (*obj)->Selected();
	  Trouve = true;
	  break;
	}
    }

  if(ID == 0 || !Trouve)
    {
      for(obj = objets.begin(); obj != dernier; ++obj)
	{
	  if ((*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	    {
	      if(GetSelectedObject()) 
		GetSelectedObject()->UnSelect();
	      (*obj)->Selected();
	      break;
	    }
	}
    }

}

void CarteNavale::PreviousObject()
{
  int ID = 0;
  bool Trouve = false;

  if (NbreBateaux < 2 ) return;

  list<Objet*>::const_iterator premier = objets.begin();
  list<Objet*>::const_iterator obj;
  for(obj = objets.end(), obj--; obj != premier; --obj)
    {
      if(!GetSelectedObject())break;
      if((*obj)->GetSelect())
	{
	  ID = (*obj)->GetID();
	  continue;
	}
      if (ID != 0 && (*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	{
	  GetSelectedObject()->UnSelect();
	  (*obj)->Selected();
	  Trouve = true;
	  break;
	}
    }
  
  if(ID == 0 || !Trouve)
    {
      for(obj = objets.end(), obj--; obj != premier; --obj)
	{
	  if ((*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	    {
	      if(GetSelectedObject()) 
		GetSelectedObject()->UnSelect();
	      (*obj)->Selected();
	      break;
	    }
	}
    }
}


/**
 * @brief  imprimer la scène
 *
 */
void CarteNavale::imprimer( ostream& out )
{
  out << "\nCarte navale Alliee : \nContient "
      << NbreBateaux << " Bateaux.\n";

  list<Objet*>::const_iterator dernier = objets.end();
  for(list<Objet*>::const_iterator obj = objets.begin(); obj != dernier; ++obj)
    out << **obj;
  
}


void CarteNavale::DeleteObject()
{
  if(NbreBateaux > 0)
    {
      objets.remove_if(RemoveSelected );
      
      NextObject();
      DelBoat();
    }
  RefreshBoats();
}


bool *CarteNavale::VerifierBateaux()
{
  bool * Bateaux =  new bool[5];
  for (int i = 0 ; i < 5 ; i++)  Bateaux[i] = false;

  list<Objet*>::const_iterator dernier = objets.end();
  list<Objet*>::const_iterator obj;
  for(obj = objets.begin(); obj != dernier; ++obj)
    {
      if ((*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	Bateaux[(*obj)->GetType() - 1] = true;
    }
  return Bateaux;

}

void CarteNavale::RefreshBoats()
{
  for(int m = 1; m < 101; m++)
    GetObjet(m)->SetEtat(1);
	
  list<Objet*>::const_iterator dernier = objets.end();
  list<Objet*>::const_iterator obj;
  for(obj = objets.begin(); obj != dernier; ++obj)
    {
      if ((*obj)->GetID() > 200 && (*obj)->GetID() < 500 && (*obj)->Edition() == false )
	(*obj)->Placer(this);
    }
  /*	
    for(int m = 1; m < 101; m++)
    {
    cout << GetObjet(m)->GetEtat() << " ";
    if ( m % 10 == 0 )
    cout << endl;
    }
    cout << endl;
    for(int m = 101; m < 201; m++)
    {
    cout << GetObjet(m)->GetEtat() << " ";
    if ( m % 10 == 0 )
    cout << endl;
    }
    cout << endl;*/
}

std::vector<int> CarteNavale::GetObjectTypes()
{
  std::vector<int> bateaux;
  list<Objet*>::const_iterator dernier = objets.end();
  list<Objet*>::const_iterator obj;
  for(obj = objets.begin(); obj != dernier; ++obj)
    {
      if ((*obj)->GetID() > 200 && (*obj)->GetID() < 500 )
	bateaux.push_back( (*obj)->GetType() );
    }

  return bateaux;
}

void CarteNavale::CommencerJeu(int size)
{
  BateauxCoulesAllie = new bool[size];
  BateauxCoulesEnnemi = new bool[size];

  for(int i = 0 ; i < size ; i++)
    {
      BateauxCoulesAllie[i] = false;
      BateauxCoulesEnnemi[i] = false;
    }
}

bool CarteNavale::VerifierGagnant()
{
  bool Allie = true;
  bool Ennemi = true;
  
  for (int i = 0 ; i < NbreBateaux ; i++)
    {
      if ( BateauxCoulesAllie[i] == false) Allie = false;
      if ( BateauxCoulesEnnemi[i] == false) Ennemi = false;
      
    }
  if(Allie == false && Ennemi == false) return false;
  
  
  if(Ennemi)
    Messages->addText("Vous avez GAGNE!!", 1);
  else
    Messages->addText("Vous avez PERDU!!", 1);


  return true;
}

void CarteNavale::BateauCouleEnnemi()
{
  for (int i = 0 ; i < NbreBateaux ; i++)
    {
      if ( BateauxCoulesEnnemi[i] == false)
	{
	  BateauxCoulesEnnemi[i] = true;
	  break; 
	}
    }

}


void CarteNavale::BateauCouleAllie()
{
  for (int i = 0 ; i < NbreBateaux ; i++)
    {
      if ( BateauxCoulesAllie[i] == false)
	{
	  BateauxCoulesAllie[i] = true;
	  break;
	}
      
    }
}


void CarteNavale::CreerTableau()
{
  Case **Tableau;
  Tableau = new Case*[200];
  
  // On load les textures du grid
  ListTextures->CreerTexture("./images/grid1.tga");
  ListTextures->CreerTexture("./images/grid2.tga");
  ListTextures->CreerTexture("./images/grid3.tga");

  for( int i = 1; i < 201; i++)
    {
      Tableau[i-1]= new Case(i, LeGraph->GetModele3D());
      ajouterObjet(Tableau[i-1]);
      Tableau[i-1]->SetGridTextures(ListTextures->GetTexture("./images/grid1.tga"), ListTextures->GetTexture("./images/grid2.tga"),ListTextures->GetTexture("./images/grid3.tga"));
    }
}


unsigned int g_Texture[MAX_TEXTURES] = {0}; 

void  CarteNavale::InitialiserCarte()
{

  CreerTableau();
    
  ListTextures->CreerTexture("./images/water.tga");
  ListTextures->CreerTexture("./images/sky.tga");
  ListTextures->CreerTexture("./images/Detail.tga");
  ListTextures->CreerTexture("./images/Terrain.tga");
  ListTextures->CreerTexture("./images/sand.tga");
  ListTextures->CreerTexture("./images/sun.tga");

  ciel->GenDome(16, 150.0f, 300.0f, 1.0f, 1.0f);
  //soleil->GenDome(16, 150.0f, 200.0f, 1.0f, 1.0f);
  //solmarin->Init("./images/Terrain.raw", RAW_SIZE, 8);

  // Aller un peu de palmiers places au hasard sur l'ile
  srand ( time(NULL) );
  Tree ** trees;
  trees = new Tree*[20];
  int x, y;
  double z;
  float xscale, yscale, zscale;
  for(int i = 0; i < 20; i++)
    {
      x = (-90 - (rand()% 20));
      y = (20 - (rand()% 60));
      z = solmarin->GetHauteur((int)(x*2.5f) + RAW_SIZE*0.75f, (int)(y*2.5f) + RAW_SIZE/2);
      z = (double)(z*0.4 - 45*0.4f);
      xscale = 0.1f + (float)((rand()% 1000)/10000.0f);
      yscale = 0.1f + (float)((rand()% 1000)/10000.0f);
      zscale = 0.1f + (float)((rand()% 1000)/10000.0f);
      trees[i] = new Tree( (double)x, (double)y, (double)z, LeGraph->GetModele3D(), xscale, yscale, zscale);
      ajouterObjet(trees[i]);
    }
}

/**
 * @fn void Graphique::incrementerTemps( void )
 *
 * @brief Incrémenter le temps courant
 *
 * Avancer l'horloge
 *
 *
 * @retval none
 * @return void description
 * @exception none
 */

/*
  void CarteNavale::incrementerTemps( void )
  {
  tempsCourant.Incrementer();
  }
*/
/*
 * @fn void Graphique::decrementerTemps( void )
 *
 * @brief Décrémenter le temps courant
 *
 * Reculer l'horloge
 *
 *
 * @retval none
 * @return void description
 * @exception none
 */
/*
  void CarteNavale::decrementerTemps( void )
  {
  //   --tempsCourant;
  }

*/

QString CarteNavale::BateauxEnnemi()
{

  QString c;

  int nbre = 0,
    i;

  if(BateauxCoulesAllie)
    {
      for (i = 0 ; i < NbreBateaux ; i++)
	{
	  if(BateauxCoulesAllie[i] == true) 
	    nbre ++;
	}
    }
    
 
  
  //sprintf(c, "%d", nbre);

  c.setNum(nbre);
  return c;
}


QString CarteNavale::BateauxAllie()
{
  QString c;

  int nbre = 0,
    i;

  if(BateauxCoulesAllie)
    {
      for (i = 0 ; i < NbreBateaux ; i++)
	{
	  if(BateauxCoulesEnnemi[i] == true) 
	    nbre ++;
	}
    }

  c.setNum(nbre);
  return c;
}


void CarteNavale::Write(ostream & out)
{
  int i, n;

  out  << NbreBateaux << " " << gamma << " " << detail << " ";
  if(BateauxCoulesAllie) 
    {
      out << "1 ";
      for(i = 0 ; i < NbreBateaux ; i++) 
	out << BateauxCoulesAllie[i] << " " << BateauxCoulesEnnemi[i] << " ";
    }
  else
    out << "0 ";
  
  n = GetNbreObjets();

  out << n << endl;

  list<Objet*>::const_iterator dernier = objets.end();
  for(list<Objet*>::const_iterator obj = objets.begin(); obj != dernier; ++obj)
    (*obj)->Write(out);



}

void CarteNavale::Read(istream & in)
{
  int i, n, temp;
  Objet** obj = NULL;

  ListTextures->CreerTexture("./images/grid1.tga");
  ListTextures->CreerTexture("./images/grid2.tga");
  ListTextures->CreerTexture("./images/grid3.tga");
  ListTextures->CreerTexture("./images/water.tga");
  ListTextures->CreerTexture("./images/sky.tga");
  ListTextures->CreerTexture("./images/Detail.tga");
  ListTextures->CreerTexture("./images/Terrain.tga");
  ListTextures->CreerTexture("./images/sand.tga");
  ListTextures->CreerTexture("./images/sun.tga");

  ciel->GenDome(16, 150.0f, 300.0f, 1.0f, 1.0f);

  srand ( time(NULL) );
   
  in >> NbreBateaux >> gamma >> detail;


  if(BateauxCoulesAllie) delete []BateauxCoulesAllie;
  if(BateauxCoulesEnnemi) delete []BateauxCoulesEnnemi;

  in >> temp;
  if(temp)
    {
  
      BateauxCoulesAllie = new bool[NbreBateaux];
      BateauxCoulesEnnemi = new bool[NbreBateaux];
      for(i = 0 ; i < NbreBateaux ; i++)
	in >> BateauxCoulesAllie[i] >> BateauxCoulesEnnemi[i];
    }
  else
    BateauxCoulesAllie = BateauxCoulesEnnemi = NULL;
  
  in >> n;

  if(n)
    obj = new Objet*[n];

  for(i = 0 ; i < n ; i++)
    {
      in >> temp;
      if(temp == 0)
	{
	  obj[i] = new Case;
	  obj[i]->SetGridTextures(ListTextures->GetTexture("./images/grid1.tga"), ListTextures->GetTexture("./images/grid2.tga"),ListTextures->GetTexture("./images/grid3.tga")); 
	}
      if(temp == 1) obj[i] = new Bateau(LeGraph->GetModele3D(), saMere);
      if(temp == 2) obj[i] = new Tree(LeGraph->GetModele3D());


      obj[i]->Read(in);

      ajouterObjet(obj[i]);
    }
}


int CarteNavale::GetNbreObjets()
{
  int i = 0;
  list<Objet*>::const_iterator dernier = objets.end();
  for(list<Objet*>::const_iterator obj = objets.begin(); obj != dernier; ++obj)
    i++;

  return i;
}

