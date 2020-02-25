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
  void CreerTexture(char *NomFichier);
  void BindTexture(char *NomFichier);
  unsigned int GetTexture(char *Nom) { return textureIDs[Nom]; };
  map<char *, unsigned int> textureIDs;
};

#endif
