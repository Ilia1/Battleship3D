#ifndef _TREE_H_
#define _TREE_H_


#include "headers.h"


class Tree : public Objet
{
 public:
  Tree(Models3D * ptrModels = NULL);
  Tree(double, double, double, Models3D *, float, float, float);
  ~Tree();

  void afficher();
  
  ostream& imprimer( ostream& out ) const {return out;};
  void Read(istream &);
  void Write(ostream &);
  
 private:
  Models3D * lesModeles;
  float xscale, yscale, zscale;
};

#endif
