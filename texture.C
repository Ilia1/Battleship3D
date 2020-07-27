#include "headers.h"


// Fonction qui lit et load le fichier TGA (header data)
ImageTGA * Textures::LoadTGA(const char *nomfichier)
{
  ImageTGA *InfoImage = NULL;
  WORD width = 0, height = 0;
  byte length = 0;
  byte TypeImage = 0;
  byte bits = 0;
  FILE *pFile = NULL;
  int channels = 0;
  int stride = 0;		// Stride = channels * width
  int i = 0;
	
  // On essaie d'ouvrir le fichier
  if( (pFile = fopen(nomfichier, "rb") ) == NULL)
    {
      QString withdir = "./images/";
      withdir.append(nomfichier);
      if( (pFile = fopen(withdir.toUtf8().constData(), "rb") ) == NULL)
	{
	  cout << "erreur d'ouverture du fichier" << endl;
	  return NULL;
	}
    }

  // On trouve l'espace requis pour mettre notre image
  InfoImage = (ImageTGA*) malloc(sizeof(ImageTGA));

  // Maintenant on lit le header
  fread(&length, sizeof(byte), 1, pFile);
  fseek(pFile, 1, SEEK_CUR);
  fread(&TypeImage, sizeof(byte), 1, pFile);
  fseek(pFile, 9, SEEK_CUR);
  fread(&width,  sizeof(WORD), 1, pFile);
  fread(&height, sizeof(WORD), 1, pFile);
  fread(&bits,   sizeof(byte), 1, pFile);
  fseek(pFile, length + 1, SEEK_CUR); 
	
  // On est maintenant rendu au data, on verifie si c compresse RLE, is oui on sort, pas supporte
  if(TypeImage != TGA_RLE)
    {
      //On verifie si c en 24 ou 32 bits, sinon on sort	
      if(bits == 24 || bits == 32)
	{
	  channels = bits / 8;
	  stride = channels * width;
	  InfoImage->data = new unsigned char[stride * height];

	  // On load les lignes de pixels
	  for(int y = 0; y < height; y++)
	    {
	      unsigned char *pLine = &(InfoImage->data[stride * y]);
	      fread(pLine, stride, 1, pFile);
	      for(i = 0; i < stride; i += channels)
		{
		  int temp     = pLine[i];
		  pLine[i]     = pLine[i + 2];
		  pLine[i + 2] = temp;
		}
	    }
	}
      else
	return NULL;
    }
  else
    return NULL;

  fclose(pFile);
  InfoImage->channels = channels;
  InfoImage->sizeX = width;
  InfoImage->sizeY = height;

  return InfoImage;
}


// Fonction qui creer une texture OPENGL a partir de notre image
void Textures::CreerTexture(char *NomFichier)
{
  if(!NomFichier)
    return;

  if(textureIDs[NomFichier])
    {
      cout << "Texture already loaded\n";
      return;
    }
		
  unsigned int tabTexture[1];
#ifdef DBG_MODE
  cout << "Loading TGA : " << NomFichier << endl;	
#endif
  ImageTGA *image = LoadTGA(NomFichier);
#ifdef DBG_MODE
  cout << "Finished loading\n";
#endif
  if(image == NULL)
    {
      cerr << "Erreur lors de l'ouverture du fichier : " << NomFichier << endl;
      exit(0);
    }
#ifdef DBG_MODE
  cout << "GenTexture + BindTexture\n";
#endif
  // Generation, bind et creation de la texture
  glGenTextures(1, &tabTexture[0]);
  glBindTexture(GL_TEXTURE_2D, tabTexture[0]);

#ifdef DBG_MODE
  cout << "Finished GenText...\n";
#endif

  textureIDs[NomFichier] = tabTexture[0];

  int textureType = GL_RGB;

  if(image->channels == 4)
    textureType = GL_RGBA;
		
  // On creer des mipmaps pour permetre une plus belle image de texture durant les zooms

#ifdef DBG_MODE
  cout << "Build2DMipMaps " << image->channels << " " << image->sizeX << " "
       << image->sizeY << " " << textureType << " " << &image->data << endl;
#endif
  gluBuild2DMipmaps(GL_TEXTURE_2D, image->channels, image->sizeX, 
		    image->sizeY, (GLenum)textureType, GL_UNSIGNED_BYTE, image->data);

#ifdef DBG_MODE
  cout <<"glTex\n";
#endif
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

#ifdef DBG_MODE
  cout << "freeing \n";
#endif
  // On libere l'espace que l'image prend durant le loadTGA
  if (image)
    {
      if(image->data)
	free(image->data);
      free(image);
    }
#ifdef DBG_MODE
  cout << "end free\n";
#endif
}


void Textures::BindTexture(char *NomFichier)
{
  unsigned int tex = textureIDs[NomFichier];
  glBindTexture(GL_TEXTURE_2D, tex);
}
