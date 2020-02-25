#ifndef _CASE_H_
#define _CASE_H_

#include "headers.h"

class Case : public Objet
{
 public:
  Case(){};
  Case(int, Models3D *);
  ~Case();

  void Read(istream &);
  void Write(ostream &);
   
  void afficher();
  virtual void SetEtat(int etat) { etatprimaire = etat; };
  virtual void SetTouche() { etatjeu = 1; };
  virtual int GetEtat() { return etatprimaire; };
  virtual int GetEtatJeu() { return etatjeu;};
  bool GetTouche() {return touche;};
  int GetBateau() { return bateau;};
  virtual void Touche() { touche = true;};
  virtual void RemoveTouche() { touche = false;};
  virtual void SetBateau(int id) { bateau = id;};
  virtual void SetEtatJeu(int etat) { etatjeu = etat;};
  void SetGridTextures(unsigned int ngrid1, unsigned int ngrid2, unsigned int ngrid3) { grid1 = ngrid1; grid2 = ngrid2; grid3 = ngrid3; };
  // impression des attributs sur le ostream
  friend ostream& operator <<( ostream& out, const Case& s )
    { return s.imprimer(out); }

  virtual ostream & imprimer( ostream& out ) const {/*if(bateau) cout << id; out << "\nEtat de la case : " << id << " " << etatprimaire << " " << etatjeu << endl;*/ return out;};

  void incrRot(int incr) { rotation += incr; };

 private:
  int bateau;
  int etatprimaire;	// Etat apres l'edition des bateaux : 1-> vide 2-> bateau 3-> peripherie de bateau
  int etatjeu;	// Etat durant le jeu : 0-> non touche 1-> touche
  bool touche;
  unsigned int grid1, grid2, grid3;
  Models3D * lesModeles;
  int rotation;
};

#endif

