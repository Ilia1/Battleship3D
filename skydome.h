#ifndef _SKYDOME_H_
#define _SKYDOME_H_

#include "headers.h"

#define SQR(x) (x*x)

typedef unsigned short WORD;
typedef struct {
  float x, y, z;
  unsigned int color;
  float u, v;
} sommet;

class SkyDome
{
 public:
  SkyDome();
  ~SkyDome();
  void GenDome(int divisions, float rayonplanet, float rayonatmosphere, float hres, float vres);
  void Afficher(float);
  void setXY(float x_, float y_){x = x_; y = y_;}

 private:
  sommet *SommetsDome;
  int nbrSommets;
  WORD *Indices;
  int nbrIndices;
  float rayonp;
  float x, y;
  GLuint listid;
};

#endif
