#ifndef _MODEL_H_
#define _MODEL_H_

#include "headers.h"

class Models3D
{
 public:
  Models3D(Textures *);
  ~Models3D();
  //void DrawSub(double, double);
  //void DrawCarrier(double, double);
  void MakeList(t3DModel&, char *);
  //void Init(void);
  void LoadModel(char *);
  void DrawModel(char *);

 private:
  map<char *, GLuint> ListIDs;
  //t3DModel Sub, Carrier;
  //CLoad3DS g_Load3ds, g_Load3ds2;
  CLoad3DS g_Load3ds[10];
  t3DModel Models[20];
  Textures *lesTextures;
  int i;
};	

#endif
