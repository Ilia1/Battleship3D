#ifndef _CARTENAVALE_H_
#define _CARTENAVALE_H_

#include "headers.h"


class CarteNavale
{
 public:
  CarteNavale(Graphique *);
  ~CarteNavale();
  // CarteNavale( const CarteNavale& b ) { *this = b; }
  const CarteNavale& operator=( const CarteNavale& b );

  // Methodes pour la gestion des objets
  void ajouterObjet( Objet* obj ) { objets.push_back(obj); }
  void eliminerDernierObjet( void );
  void eliminerTousObjets( void );
  void RotateObjet(int);
  Objet * GetObjet(int ID);
  Objet * GetSelectedObject();
  std::vector<int> GetObjectTypes();
  int GetNbreBateaux() { return NbreBateaux; };
  void afficher(float temps);
  void NextObject();
  void PreviousObject();
  void DeleteObject();
  SkyDome * GetSky(){return ciel;}
  void AddBoat(){NbreBateaux++;};
  void DelBoat(){NbreBateaux--;};
  bool* VerifierBateaux();
  void RefreshBoats();
  void CommencerJeu(int);
  void CreerTableau();
  void InitialiserCarte();
  void Read(istream & in);
  void Write(ostream &out);
  int GetNbreObjets();
   
  bool VerifierGagnant();
  void BateauCouleEnnemi();
  void BateauCouleAllie();

  void AugmenterGamma(){gamma++;};
  void DiminuerGamma(){gamma--;};
  void AugmenterDetail(){if(detail < 128)detail *=2;};
  void DiminuerDetail(){if(detail > 1)detail /=2;};

  void imprimer( ostream& out = cout ) ;
  friend ostream& operator <<( ostream& out,CarteNavale& s )
    { s.imprimer(out); return out; }
  QString BateauxEnnemi();
  QString BateauxAllie();

  ClasseText* GetText() { return Messages; };

  Models3D * GetModels();

  
  Textures * GetTextures(){ return ListTextures; };
  Mer * GetMer() { return saMere; };
  //
   
 private:
  Graphique *LeGraph;	// Pointeur vers graphique qui a creer cette CarteNavale
  list<Objet*> objets;  // liste chainee (STL) de bateaux (eventuellement rocher, phare, etc..)
  int NbreBateaux;
  bool *BateauxCoulesAllie;
  bool *BateauxCoulesEnnemi;

  Textures *ListTextures;
  int gamma;

  float detail;
  //GLUquadricObj *quadobj;
  SkyDome *ciel;
  Terrain *solmarin;
  //t3DModel LightHouse;
  ClasseText *Messages;
  Mer *saMere;
  GLUquadricObj *pObj;

};


#endif /* _CARTENAVALE_H_ */
