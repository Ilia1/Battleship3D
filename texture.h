#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "headers.h"

struct ImageTGA
{
  int channels;           
  int sizeX;              
  int sizeY;
  unsigned char *data;
};

class Textures
{
 public:
  ImageTGA *LoadTGA(const char *nomfichier);
  void CreerTexture(const char *NomFichier);
  void BindTexture(const char *NomFichier);
  unsigned int GetTexture(const char *Nom) { return textureIDs[Nom]; };
  map<const char *, unsigned int> textureIDs;
};

#endif
