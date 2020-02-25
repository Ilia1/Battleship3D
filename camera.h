// Definitions des Classes pour la manipulation de la camera

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "headers.h"


// Classe de la Camera elle meme
class ClasseCamera 
{
 public:
  SkyDome *sky;
  CVector3 Position;
  CVector3 Vue;
  CVector3 UpVecteur;
  float phi, teta, rayon;
  int mode;		// 0 = 2D, 1 = Perspective 3D, 2 = straffing
  
  void Write(ostream & out);
  void Read(istream & in);
  ClasseCamera(SkyDome *);
  ~ClasseCamera();
  void Refresh();
  void RefreshSky();
  //int GetMode() { return mode; };
  //void ChangerMode(int nvmode) { mode = nvmode; };
  void Changer(	float posX, float posY, float posZ, 
		float vueX, float vueY, float vueZ, 
		float upX, float upY, float upZ		);
  void Deplacer( int direction, float vitesse );
  void DeplacerAvecVueFixe ( int direction, float vitesse );
  void AvancerVersVue ( float vitesse );
  //	void TournerVue ( float angle, float axeX, float axeY, float axeZ );
  void DeplacerSurSphere ( int direction, float vitesse );
  void DeplacerOrigine (int direction, float vitesse);
  void Afficher(){cout << phi << " " << teta << endl;};
};

#endif
