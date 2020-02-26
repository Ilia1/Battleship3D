#ifndef _BATEAU_H_
#define _BATEAU_H_


#include "headers.h"
//Added by qt3to4:
#include <QMouseEvent>


class Bateau : public Objet
{
 public:
  Bateau(){};
  Bateau(Models3D *, Mer *);
  Bateau(double, double, int, Models3D *, Mer *, bool = false);
  ~Bateau();

  void afficher();

  // impression des attributs sur le ostream
  ostream& imprimer( ostream& out ) const ;
  virtual void Rotate();
  virtual void RotateSurPlace(CarteNavale *);
  virtual void MoveBoat(CarteNavale *, int);
  //void SetXY(double x, double y, double _z){m_cPosI = x; m_cPosJ = y; z = _z;};
  virtual int GetLength() { return m_cLen; };
  virtual int GetDeg() { return deg; };
  virtual void DiminuerTaille(CarteNavale *);
  virtual void AugmenterTaille(CarteNavale *);
  virtual double GetLargeur_x ();
  virtual double GetLargeur_y ();
  virtual int GetType(){return type;}
  virtual void SetType(CarteNavale *, int t);
  bool VerifierCoule(CarteNavale*);

  virtual void Edit() { edition = true; };
  virtual void UnEdit() { edition = false; };
  virtual int GetL0(){return liste2[0];};
  virtual int GetLX(){return liste2[m_cLen-1];};

  virtual bool VerifierPlacement(CarteNavale*);
  virtual void CalculerListes(int);
  virtual void Placer(CarteNavale*);
  virtual void ArrangerPosition(int, int &, double &, double &);
  virtual bool Edition() { return edition; };
  virtual void XYfromgrid(int gridid);

  void Read(istream &);
  void Write(ostream &);


  virtual void MouseReleaseEvent1(Graphique *, double, double);
  virtual void MouseReleaseEvent2(Graphique *);
  virtual void MouseMotionEvent(QMouseEvent *, Graphique *);



 private:
  // Longueur du bateau
  int m_cLen;

  static int static_id;
  int deg;
  int type;
  int touches;

  bool ennemi,
    coule,
    edition;

  int gridid, gridtemp, gridtemp2, gridtemp3;

  int liste[22];	// Liste des cases occupes avec peripherie
  int liste2[5];	// Liste des cases occupes sans peripherie

  Models3D *lesModeles;
  Mer *laMer;

};

#endif /* _BATEAU_H_ */
