// Routines de la classe Camera

#include "headers.h"

//Constructeur de la classe Camera
ClasseCamera::ClasseCamera(SkyDome * s)
{
  CVector3 PosInit = { 0.0, 0.0, 0.0 };
  CVector3 VueInit = { 0.0, 0.0, 0.0 };
  CVector3 UpInit = { 0.0, 0.0, 1.0 };

  Position = PosInit;
  Vue = VueInit;
  UpVecteur = UpInit;
	
  phi = 0.0f;
  teta = 0.0f;
  rayon = 0.0f;
  sky = s;
}

ClasseCamera::~ClasseCamera()
{
	
}

// Placement initial de la camera durant un changement de mode
void ClasseCamera::Refresh()
{
  switch ( mode )
    {		
    case 0:
      Changer( 0.0f, 0.0f, 26.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);
	  
      phi = 0.0f;
      teta = 0.0f;
      rayon = 0.0f;
      break;
    case 1:
      Changer( 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f);
	  
      phi = 1.21f;
      teta = -2.21f;
      rayon = 24.0f;
      Position.x = rayon * (float)sin(phi) * (float)cos(teta);
      Position.y = rayon * (float)sin(phi) * (float)sin(teta);
      Position.z = rayon * (float)cos(phi);
      break;
    case 2:
      Changer( 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f);
	  
      phi = 1.00f;
      teta = -1.57f;
      rayon = 25.0f;
      Position.x = rayon * (float)sin(phi) * (float)cos(teta);
      Position.y = rayon * (float)sin(phi) * (float)sin(teta);
      Position.z = rayon * (float)cos(phi);
      phi = -2.14f;
      teta = -1.57f;
      rayon = 25.0f;
      break;
    }
  RefreshSky();
}	


void ClasseCamera::RefreshSky()
{
  //sky->setXY(Position.x, Position.y);
}

void ClasseCamera::Write(ostream & out)
{
  out << Position.x << " " << Position.y << " " << Position.z << " "
      << Vue.x << " " << Vue.y << " " << Vue.z << " " << UpVecteur.x
      << " " << UpVecteur.y << " " << UpVecteur.z << " " << phi << " "
      << teta << " " << rayon << " " << mode << endl;
}


void ClasseCamera::Read(istream & in)
{
  in >> Position.x  >> Position.y  >> Position.z >> Vue.x >> Vue.y
     >> Vue.z >> UpVecteur.x >> UpVecteur.y >> UpVecteur.z >> phi 
     >> teta >> rayon >> mode;
}

// Fonction pour modifier la position, vue et upvecteur de la camera
void ClasseCamera::Changer(     float posX, float posY, float posZ, 
				float vueX, float vueY, float vueZ, 
				float upX, float upY, float upZ         )
{
  CVector3 PosInit = { posX, posY, posZ };
  CVector3 VueInit = { vueX, vueY, vueZ };
  CVector3 UpInit = { upX, upY, upZ };

  Position = PosInit;
  Vue = VueInit;
  UpVecteur = UpInit;
  RefreshSky();
}

// Fonction pour deplacer la camera en fonction de la direction et de la vitesse
// direction : 
// 1 = haut 
// 2 = droite 
// 3 = bas 
// 4 = gauche 
// 5 = zoom in 
// 6 = zoom out
void ClasseCamera::Deplacer( int direction, float vitesse )
{
  switch (direction) {
  case 1:
    if ( Position.y < 21 ) {
      Position.y += vitesse;
      Vue.y += vitesse;
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 2:
    if ( Position.x < 15.5) {
      Position.x += vitesse;
      Vue.x += vitesse;
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 3:
    if ( Position.y > -21 ) {
      Position.y += (-vitesse);
      Vue.y += (-vitesse);
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 4:
    if ( Position.x > -15.5 ) {
      Position.x += (-vitesse);
      Vue.x += (-vitesse);
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 5:
    if ( Position.z > 0 )
      Position.z += (-vitesse);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 6:
    if ( Position.z < 30 ) 
      Position.z += vitesse;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
  }
  RefreshSky();
}

// Fonction pour deplacer la camera en fonction de la direction et de la vitesse en gardant le regard fix
// direction : 
// 1 = haut 
// 2 = droite 
// 3 = bas 
// 4 = gauche 
// 5 = zoom in 
// 6 = zoom out
void ClasseCamera::DeplacerAvecVueFixe( int direction, float vitesse )
{
  switch (direction) {
  case 1:
    Position.y += vitesse;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 2:
    Position.x += vitesse;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 3:
    Position.y += (-vitesse);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 4:
    Position.x += (-vitesse);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 5:
    Position.z += (-vitesse);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    break;
  case 6:
    Position.z += vitesse;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
  }
  RefreshSky();
}

// Mode de camera qui deplace celle ci sur la surface d'une demi sphere
// en utilisant l'equation parametrique des spheres
// Direction :
// 1 = up
// 2 = droite
// 3 = down
// 4 = gauche
void ClasseCamera::DeplacerSurSphere ( int direction, float vitesse )
{
  switch (direction) {
  case 1:
    if ( phi > 0.1 ) {
      phi += (-vitesse);
      Position.x = rayon * (float)sin(phi) * (float)cos(teta);
      Position.y = rayon * (float)sin(phi) * (float)sin(teta);
      Position.z = rayon * (float)cos(phi);
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 2:
    teta += vitesse;
    Position.x = rayon * (float)sin(phi) * (float)cos(teta);
    Position.y = rayon * (float)sin(phi) * (float)sin(teta);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 3:
    if ( phi < 1.47 ) {
      phi += (vitesse);
      Position.x = rayon * (float)sin(phi) * (float)cos(teta);
      Position.y = rayon * (float)sin(phi) * (float)sin(teta);
      Position.z = rayon * (float)cos(phi);
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 4:
    teta += (-vitesse);
    Position.x = rayon * (float)sin(phi) * (float)cos(teta);
    Position.y = rayon * (float)sin(phi) * (float)sin(teta);
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
  }
  RefreshSky();
}

// Avancer vers le vecteur de vue et diminuer le rayon de sphere
void ClasseCamera::AvancerVersVue ( float vitesse )
{
  switch(mode)
    {
    case 1:
      
      if ( (rayon > 1 && vitesse > 0) || ( rayon < 27 && vitesse < 0) ) 
	{
	  CVector3 VecteurVue = {0, 0, 0};
	  
	  VecteurVue.x = Vue.x - Position.x;
	  VecteurVue.y = Vue.y - Position.y;
	  VecteurVue.z = Vue.z - Position.z;
	  
	  Position.x += VecteurVue.x * vitesse;
	  Position.y += VecteurVue.y * vitesse;
	  Position.z += VecteurVue.z * vitesse;
	  
	  rayon = sqrt( Position.x * Position.x + Position.y * Position.y + Position.z * Position.z );
	}
      break;
    case 2:
      CVector3 VecteurVue = {0, 0, 0};
	  
      VecteurVue.x = Vue.x - Position.x;
      VecteurVue.y = Vue.y - Position.y;
      VecteurVue.z = Vue.z - Position.z;
      
      Position.x += VecteurVue.x * vitesse;
      Position.y += VecteurVue.y * vitesse;
      Position.z += VecteurVue.z * vitesse;
      
      Vue.x += VecteurVue.x * vitesse;
      Vue.y += VecteurVue.y * vitesse;
      Vue.z += VecteurVue.z * vitesse;
      break;
    }
  RefreshSky();   
}	


void ClasseCamera::DeplacerOrigine ( int direction, float vitesse )
{
  /*
    double x = rayon, y =rayon, z = rayon;
    switch (direction) {
    case 1:
    //	if ( phi > 0.1 ) {

    y = rayon * (float)cos(vitesse);
    z = rayon * (float)sin(vitesse);

    //	}
    //cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //cout << phi << " " << teta << endl;
    break;
    case 2:

    x = rayon * (float)cos(90 - vitesse);
    y = rayon * (float)sin(90 - vitesse);

    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
    case 3:
    //	if ( phi < 1.47 ) {
    y = rayon * (float)cos(vitesse);
    z = -rayon * (float)sin(vitesse);

    //	}
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
    case 4:
    x = rayon * (float)sin(vitesse);
    y = rayon * (float)cos(vitesse);

    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    }

    Vue.x += rayon - x;
    Vue.y -= rayon - y;
    Vue.z += rayon - z;
  */
  switch (direction) {
  case 1:
    if ( phi < 0.0 - vitesse) {
      phi += vitesse;
      Vue.x = rayon * (float)sin(phi) * (float)cos(teta) + Position.x;
      Vue.y = rayon * (float)sin(phi) * (float)sin(teta) + Position.y;
      Vue.z = rayon * (float)cos(phi) + Position.z;
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 2:
    teta -= vitesse;
    Vue.x = rayon * (float)sin(phi) * (float)cos(teta) + Position.x;
    Vue.y = rayon * (float)sin(phi) * (float)sin(teta) + Position.y;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 3:
    if ( phi > -3.14 + vitesse ) {
      phi -= vitesse;
      Vue.x = rayon * (float)sin(phi) * (float)cos(teta) + Position.x;
      Vue.y = rayon * (float)sin(phi) * (float)sin(teta) + Position.y;
      Vue.z = rayon * (float)cos(phi) + Position.z;
    }
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
    break;
  case 4:
    teta += vitesse;
    Vue.x = rayon * (float)sin(phi) * (float)cos(teta) + Position.x;
    Vue.y = rayon * (float)sin(phi) * (float)sin(teta) + Position.y;
    //			cout << Position.x << " " << Position.y << " " << Position.z << "\n";
    //			cout << phi << " " << teta << endl;
  }
  RefreshSky();
}
