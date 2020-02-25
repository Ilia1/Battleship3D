#ifndef _MER_H_
#define _MER_H_

#include "headers.h"

class Mer 
{
 public:
  Mer();
  ~Mer();
  void Afficher(Textures *, float, float, float);
  float GetHeight(float, float);

 private:
  float points[45][45][3];
  float tempsdernierevague;
  float hauteurvague;
  float s;
  float NormalsVertices[45][45][3];
};

#endif
