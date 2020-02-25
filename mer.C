#include "headers.h"

// Classe mer qui genere les mer, algorithme de TuxSaver (koen muylkens)

Mer::Mer()
{
  s = 35;
  hauteurvague=0.5f;
  tempsdernierevague = 0;
  int b, c, d;
  int NumFaces = 2025;
  //Initialisation de la matrice primaire des vagues
  float float_x, float_z; 
  for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )      {
    for(float_z = 0.0f; float_z < 9.0f; float_z += 0.2f)            {
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][0] = float_x - 4.4f;
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][1] = (float) (sin( ( (float_x*80)/360 ) * 3.14159 * 2 ));
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][2] = float_z - 4.4f; 
    }
  }

  float Faces[NumFaces][4][3];

  // On genere nos faces
  for(int x=0; x<45; x++) {
    for (int z=0; z<45; z++) {
      Faces[45*x + z][0][0] = s* points[x][z][0];
      Faces[45*x + z][0][1] = hauteurvague*points[x][z][1];
      Faces[45*x + z][0][2] = s*points[x][z][2] -0.5f;
      Faces[45*x + z][1][0] = s*points[x][z+1][0];
      Faces[45*x + z][1][1] = hauteurvague*points[x][z+1][1];
      Faces[45*x + z][1][2] = s*points[x][z+1][2]-0.5f;
      Faces[45*x + z][2][0] = s*points[x+1][z+1][0];
      Faces[45*x + z][2][1] = hauteurvague*points[x+1][z+1][1];
      Faces[45*x + z][2][2] = s*points[x+1][z+1][2] - 0.5f;
      Faces[45*x + z][3][0] = s*points[x+1][z][0];
      Faces[45*x + z][3][1] = hauteurvague*points[x+1][z][1];
      Faces[45*x + z][3][2] = s*points[x+1][z][2] -0.5f;

      /*cout << Faces[45*x + z][0][0] << " " << Faces[45*x + z][0][1] << " " << Faces[45*x + z][0][2] << endl;
	cout << Faces[45*x + z][1][0] << " " << Faces[45*x + z][1][1] << " " << Faces[45*x + z][1][2] << endl;
	cout << Faces[45*x + z][2][0] << " " << Faces[45*x + z][2][1] << " " << Faces[45*x + z][2][2] << endl;
	cout << Faces[45*x + z][3][0] << " " << Faces[45*x + z][3][1] << " " << Faces[45*x + z][3][2] << endl << endl;*/
    }
  }
	
  // Calcul des normals des faces
  float NormalsFaces[NumFaces][3];
  float NormalsFacesTemps[NumFaces][3];
  float VecA[3], VecB[3], Temp[3], magnitude;
  
  for(d = 0; d < NumFaces; d++)
    {
      // Vecteurs Vert10 et Vert30
      VecA[0] = Faces[d][1][0] - Faces[d][0][0];
      VecA[1] = Faces[d][1][1] - Faces[d][0][1];
      VecA[2] = Faces[d][1][2] - Faces[d][0][2];
      VecB[0] = Faces[d][3][0] - Faces[d][0][0];
      VecB[1] = Faces[d][3][1] - Faces[d][0][1];
      VecB[2] = Faces[d][3][2] - Faces[d][0][2];
	  
      // Produit scalaire
      Temp[0] = ((VecA[1] * VecB[2]) - (VecA[2] * VecB[1]));
      Temp[1] = ((VecA[2] * VecB[0]) - (VecA[0] * VecB[2]));
      Temp[2] = ((VecA[0] * VecB[1]) - (VecA[1] * VecB[0]));
		  
      NormalsFacesTemps[d][0] = Temp[0];
      NormalsFacesTemps[d][1] = Temp[1];
      NormalsFacesTemps[d][2] = Temp[2];

      //cout << Temp[0] << " " << Temp[1] << " " << Temp[2] << "   ";
      //cout << Temp[2] << " ";

      // On normalise
      magnitude = sqrt(Temp[0]*Temp[0] + Temp[1]*Temp[1] + Temp[2]*Temp[2]);
      Temp[0] /= (float)magnitude;
      Temp[1] /= (float)magnitude;
      Temp[2] /= (float)magnitude;

      NormalsFaces[d][0] = Temp[0];
      NormalsFaces[d][1] = Temp[1];
      NormalsFaces[d][2] = Temp[2];

      //cout << Temp[0] << " " << Temp[1] << " " << Temp[2] << "   ";
    }
  
  // Calcul des normals des vertices cette fois
  //  float NormalsVertices[45][45][3];
  float Somme[3];
  Somme[0] = 0;
  Somme[1] = 0;
  Somme[2] = 0;
  int partages = 0;
  
  for(b = 1; b < 44; b++)
    for(c = 1; c < 44; c++)
      {
	// On genere les normals de nos vertex
	// Le milieu
	Somme[0] += NormalsFacesTemps[45*(b-1) + (c-1)][0] + NormalsFacesTemps[45*(b) + (c-1)][0] + NormalsFacesTemps[45*(b-1) + (c)][0] + NormalsFacesTemps[45*(b) + (c)][0];
	Somme[1] += NormalsFacesTemps[45*(b-1) + (c-1)][1] + NormalsFacesTemps[45*(b) + (c-1)][1] + NormalsFacesTemps[45*(b-1) + (c)][0] + NormalsFacesTemps[45*(b) + (c)][1];
	Somme[2] += NormalsFacesTemps[45*(b-1) + (c-1)][2] + NormalsFacesTemps[45*(b) + (c-1)][2] + NormalsFacesTemps[45*(b-1) + (c)][2] + NormalsFacesTemps[45*(b) + (c)][2];
	partages = 4;
	  	  
	// Divions par le nombre de partages
	NormalsVertices[b][c][0] = Somme[0] / (float)(partages);
	NormalsVertices[b][c][1] = Somme[1] / (float)(partages);
	NormalsVertices[b][c][2] = Somme[2] / (float)(partages);
  
	//cout << Somme[0] << " " << Somme[1] << " " << Somme[2] << " " << partages << "    ";
	  
	// Normalisation
	magnitude = sqrt(NormalsVertices[b][c][0]*NormalsVertices[b][c][0] + 
			 NormalsVertices[b][c][1]*NormalsVertices[b][c][1] + 
			 NormalsVertices[b][c][2]*NormalsVertices[b][c][2]);
	NormalsVertices[b][c][0] /= (float)magnitude;
	NormalsVertices[b][c][1] /= (float)magnitude;
	NormalsVertices[b][c][2] /= (float)magnitude;

	// On reset
	partages = 0;
	Somme[0] = 0;
	Somme[1] = 0;
	Somme[2] = 0;
      }

  // colone droite et gauche
  for(b = 0; b < 45; b+=44)
    for(c = 0; c < 44; c++)
      {
	Somme[0] += NormalsFacesTemps[45*(b) + (c-1)][0] + NormalsFacesTemps[45*(b) + (c)][0];
	Somme[1] += NormalsFacesTemps[45*(b) + (c-1)][1] + NormalsFacesTemps[45*(b) + (c)][1];
	Somme[2] += NormalsFacesTemps[45*(b) + (c-1)][2] + NormalsFacesTemps[45*(b) + (c)][2];
	partages = 2;

	// Divions par le nombre de partages
	NormalsVertices[b][c][0] = Somme[0] / (float)(partages);
	NormalsVertices[b][c][1] = Somme[1] / (float)(partages);
	NormalsVertices[b][c][2] = Somme[2] / (float)(partages);
  
	  	  
	// Normalisation
	magnitude = sqrt(NormalsVertices[b][c][0]*NormalsVertices[b][c][0] + 
			 NormalsVertices[b][c][1]*NormalsVertices[b][c][1] + 
			 NormalsVertices[b][c][2]*NormalsVertices[b][c][2]);
	NormalsVertices[b][c][0] /= (float)magnitude;
	NormalsVertices[b][c][1] /= (float)magnitude;
	NormalsVertices[b][c][2] /= (float)magnitude;

	// On reset
	partages = 0;
	Somme[0] = 0;
	Somme[1] = 0;
	Somme[2] = 0;
      }

#ifdef DBG_MODE
  for(b = 0; b < 44; b++)
    for(c = 0; c < 44; c++)
      {
	cout << NormalsVertices[b][c][0] << " " << NormalsVertices[b][c][1] << " " << NormalsVertices[b][c][2] << "     ";
      }
#endif

}

Mer::~Mer()
{
}

float Mer::GetHeight(float x, float y)
{
  x = (x / 20) + 4.4f;
  y = (y / 20) + 4.4f;
  return (points[int(x*5)][int(y*5)][1]*hauteurvague);
}

void Mer::Afficher(Textures *ptrTextures, float hautvague, float tempsvague, float time)
{
  hauteurvague = hautvague;
  glPushMatrix();
  glRotatef(90, 1.0f, 0.0f, 0.0f);
  //glTranslatef(-35*(time - tempsdernierevague), 0.0f, 0.0f);

  int x, z;
  float float_x, float_z, float_xb, float_zb;
	
  glEnable(GL_BLEND);
	
  glColor4f(1.0f,1.0f,1.0f, 0.75f);

  glBegin(GL_QUADS);
  for (x=0; x<44; x++) {
    for (z=0; z<44; z++) {
      float_x  = (float) (x)/11;
      float_z  = (float) (z)/11;
      float_xb = (float) (x+1)/11;
      float_zb = (float) (z+1)/11;
      glNormal3f(NormalsVertices[x][z][0], NormalsVertices[x][z][1], NormalsVertices[x][z][2]);
      glTexCoord2f(float_x, float_z);
      glVertex3f(s* points[x][z][0], hauteurvague*points[x][z][1],s*points[x][z][2] -0.5f);

      glNormal3f(NormalsVertices[x][z+1][0], NormalsVertices[x][z+1][1], NormalsVertices[x][z+1][2]);
      glTexCoord2f(float_x, float_zb );
      glVertex3f(s*points[x][z+1][0], hauteurvague*points[x][z+1][1], s*points[x][z+1][2]-0.5f );

      glNormal3f(NormalsVertices[x+1][z+1][0], NormalsVertices[x+1][z+1][1], NormalsVertices[x+1][z+1][2]);
      glTexCoord2f( float_xb, float_zb );
      glVertex3f(s*points[x+1][z+1][0], hauteurvague*points[x+1][z+1][1], s*points[x+1][z+1][2] - 0.5f );

      glNormal3f(NormalsVertices[x+1][z][0], NormalsVertices[x+1][z][1], NormalsVertices[x+1][z][2]);
      glTexCoord2f( float_xb, float_z );
      glVertex3f( s*points[x+1][z][0], hauteurvague*points[x+1][z][1], s*points[x+1][z][2] -0.5f );
    }
  }
  glEnd();

  glDisable(GL_BLEND);

  /*      glBegin( GL_LINES );
	  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	  glVertex3d(0.0f, 0.0f, 0.0f);
	  glVertex3d(-0.0253796f, 0.999678f, 0.0f);
	  for(x = 0; x < 44; x++)
	  for(z = 0; z < 44; z++)
	  {
	  glVertex3d(s*points[x][z][0], hauteurvague*points[x][z][1], s*points[x][z][2]-0.5f);
	  glVertex3d(s*points[x][z][0] + NormalsVertices[x][z][0], hauteurvague*points[x][z][1] + NormalsVertices[x][z][1], s*points[x][z][2] - 0.5f + NormalsVertices[x][z][2]);
	  glVertex3d(0, 0, 0);
	  glVertex3d(NormalsVertices[x][z][0], NormalsVertices[x][z][1], NormalsVertices[x][z][2]);
	  }*/
  glEnd();
      
            
  if ((time - tempsdernierevague) > 0.025f)
    {
      tempsdernierevague=time;
	  
      for (z = 0; z < 45; z++) {
	NormalsVertices[44][z][1] = NormalsVertices[0][z][1];
	points[44][z][1] = points[0][z][1];
      }
	  
      for( x = 0; x < 44; x++ ) {
	for( z = 0; z < 45; z++) {
	  NormalsVertices[x][z][1] = NormalsVertices[x+1][z][1];
	  points[x][z][1] = points[x+1][z][1];
	}
      }
    }
  glPopMatrix();
}


      

	
