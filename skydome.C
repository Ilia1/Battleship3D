#include "headers.h"


// SkyDome Classe to display sky, mostly inspired from Luis R. Sempe's tutorial.

SkyDome::SkyDome()
{
  x = 0;
  y = 0;

}

void SkyDome::GenDome(int divisions, float rayonplanet, float rayonatmosphere, float hres, float vres)
{
  // On clear notre tab de sommets et tab d'indices
  /*if(SommetsDome)
    {
    delete SommetsDome;
    SommetsDome = NULL;
    }
    if(Indices)
    {
    delete Indices;
    Indices = NULL;
    }*/

  // On s'assure d'avoir entre 1 et 256 divisions
  if(divisions < 1)
    divisions = 1;
  else if(divisions > 256)
    divisions = 256;

  rayonp = rayonplanet;

  // Initialisations des tableaux de sommets et indices
  nbrSommets = (divisions + 1) * (divisions + 1);
  nbrIndices = divisions * divisions * 2 * 3;

  SommetsDome = new sommet[nbrSommets];
  Indices = new WORD[nbrIndices];

  // On calcul maintenant nos sommets
  float taille_dome = 2.0f * (float)sqrt((SQR(rayonatmosphere)-SQR(rayonplanet)));
  float taille_div = taille_dome / (float)divisions;
  float tex_div = 2.0f / (float)divisions;

  float x_dist = 0.0f;
  float z_dist = 0.0f;
  float x_height = 0.0f;
  float z_height = 0.0f;
  float height = 0.0f;
	
  sommet temp;

  for(int i = 0; i <= divisions; i++)
    {
      for(int j = 0; j <= divisions; j++)
	{
	  x_dist = (-0.5f * taille_dome) + ((float)j*taille_div);
	  z_dist = (-0.5f * taille_dome) + ((float)i*taille_div);

	  x_height = (x_dist*x_dist) / rayonatmosphere;
	  z_height = (z_dist*z_dist) / rayonatmosphere;
	  height = x_height + z_height;

	  temp.x = x_dist;
	  temp.z = 0.0f - height;
	  temp.y = z_dist;

	  temp.u = hres*((float)j * tex_div*0.5f);
	  temp.v = vres*(1.0f - (float)i * tex_div*0.5f);

	  SommetsDome[i * (divisions + 1) + j] = temp;
	}
    }

  // Et nos indices
  int index = 0;
  for (int i=0; i < divisions;i++)
    {
      for (int j=0; j < divisions; j++)
	{
	  int startvert = (i*(divisions+1) + j);

	  // tri 1
	  Indices[index++] = startvert;
	  Indices[index++] = startvert+1;
	  Indices[index++] = startvert+divisions+1;

	  // tri 2
	  Indices[index++] = startvert+1;
	  Indices[index++] = startvert+divisions+2;
	  Indices[index++] = startvert+divisions+1;
	}
    }
  listid = glGenLists(1);
  cout << "listid : " << listid << endl;
  glNewList(listid, GL_COMPILE);
  glBegin(GL_TRIANGLES);
  for(int i=0; i < nbrIndices; i++)
    {
      //glColor3f(1.0f, 0.5f, 0.0f);
      glTexCoord2f(SommetsDome[Indices[i]].u, SommetsDome[Indices[i]].v);
      glVertex3f(SommetsDome[Indices[i]].x, SommetsDome[Indices[i]].y, SommetsDome[Indices[i]].z);
    }
  glEnd();
  glEndList();
}


SkyDome::~SkyDome()
{
  if(SommetsDome)
    {
      delete SommetsDome;
      SommetsDome = NULL;
    }
  if(Indices)
    {
      delete Indices;
      Indices = NULL;
    }
}

void SkyDome::Afficher(float temps)
{
	
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glTranslatef(x-60.0f,y, 175.0f);
  glRotatef((temps/ 0.005) * 0.05, 0.0f, 0.0f, 1.0f);
  glCallList(listid);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}
	
