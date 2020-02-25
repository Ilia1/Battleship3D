#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "headers.h"


class Terrain
{
 public:
  Terrain();
  ~Terrain(){ if(terr) delete []terr;};
  void Init(char *, int, int );
  void Afficher(){glCallList(listid);};
  int GetHauteur(int x, int y) { return terr[(x%size) + ((y%size) * size)]; };

 private:
  BYTE * terr;
  int size, step;
  GLuint listid;
};

#endif
