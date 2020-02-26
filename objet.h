#ifndef _HEADER_OBJET_H_
#define _HEADER_OBJET_H_

#include "headers.h"
//Added by qt3to4:
#include <QMouseEvent>


class Objet
{
 public:
  Objet(void) {}
  virtual ~Objet(void) {}

  //affichage graphique a l'écran
  virtual void afficher() = 0;
  virtual void Rotate() {};
  virtual void RotateSurPlace(CarteNavale *) {};
  virtual void MoveBoat(CarteNavale *, int) {};
  virtual int GetType(){return 0;};
  virtual int GetL0(){return 0;}
  virtual int GetLX(){return 0;}

  virtual void Read(istream &) = 0;
  virtual void Write(ostream &) = 0;


  virtual int GetLength() { return 0; };
  virtual int GetDeg() { return 0; };

  virtual void DiminuerTaille(CarteNavale *) {};
  virtual void AugmenterTaille(CarteNavale *) {};
  virtual double GetLargeur_x () {return 0.0;};
  virtual double GetLargeur_y () {return 0.0;};

  virtual void SetGridTextures(unsigned int , unsigned int , unsigned int) {};

  virtual int GetEtat() { return 0; };
  virtual void SetEtat(int) {};
  virtual void SetEtatJeu(int) {};
  virtual int GetEtatJeu() { return 0;};
  virtual bool VerifierCoule(CarteNavale *) { return false;};
  virtual int GetBateau() {return 0;};
  virtual void Touche(){};
  virtual void UnEdit(){};
  virtual void RemoveTouche() {};
  virtual bool GetTouche() {return 0;};
  virtual void SetBateau(int ) {};
  virtual void SetType(CarteNavale *, int ){};

  virtual bool VerifierPlacement(CarteNavale *) {return 0;};
  virtual void CalculerListes(int) {};
  virtual void Placer(CarteNavale *) {};
  virtual void ArrangerPosition(int, int &, double &, double &) {};
  virtual bool Edition() { return 0;};
  virtual void Edit() {};
  virtual void XYfromgrid(int) {};
  virtual void MouseReleaseEvent1(Graphique *, double, double) {};
  virtual void MouseReleaseEvent2(Graphique *) {};
  virtual void MouseMotionEvent(QMouseEvent *, Graphique *) {};


  // impression des attributs sur le ostream
  virtual ostream& imprimer( ostream& out ) const = 0;
  friend ostream& operator<<( ostream& out, const Objet& s )
    { s.imprimer(out); return out; }
   
  void Selected() { select = 1; };
  void UnSelect() { select = 0; };
  bool GetSelect() { return select; };

  
  void SetID ( int Newid ) { id = Newid; };
  int GetID () { return id; };
   
  virtual void SetXY(double _x, double _y, double _z) { x = _x; y = _y; z = _z; };
  virtual double GetX() { return x; };
  virtual double GetY() { return y; };
  virtual double GetZ() { return z; };

 private:
  double masse;    // masse de l'objet
  double friction; // coefficient de friction lorsqu'en mouvement
        
 protected:
  int id; // Numero d'ID de l'objet
  bool select;
  double x, y, z;
};

 

#endif /* _HEADER_OBJET_H_ */
