#include "headers.h"


// Terrain Classe to display underwater soil, mostly inspired from Luis R. Sempe's tutorial.

Terrain::Terrain()
{
  terr = NULL;
  size = 0;
  step = 0;
  listid =0;

}


void Terrain::Init(char * file, int si, int st)
{

  double x,
    y,
    z;

  int NumVerts = ((si -8)/8) * ((si + 8)/8) * 2;
  int NumFaces = NumVerts - 2;
  int d, v, c;

  double Verts[NumVerts][3];
  double Faces[NumFaces][3][3];
  int q = 0;
    
  size = si;
  step = st;
  if(terr) delete []terr;
  terr = NULL;

  terr = new BYTE[size * size];
  FILE *pFile = fopen( file, "rb" ) ;

  if(! pFile)
    {
      perror("Opening file :");
      exit(-1);
    }

  fread( terr, 1, size * size, pFile );
  if(ferror( pFile )) 
    {
      perror("Reading data :");
      exit(-1);
    }

  fclose(pFile);
  cout << "File opened\n";


  // Generate la matrice du terrain

  //listid = glGenLists(1);
  //cout << "listid : " << listid << endl;
  //glNewList(listid, GL_COMPILE);

  //glBegin( GL_TRIANGLE_STRIP );
  for(int i = 0 ; i < size-8; i +=step)
    {
      if((i/step)%2)
	{
	  for(int j = size ; j >= 0 ; j -=step)
	    {
	      
	      x=i;
	      y=j;
	      z=terr[(i%size) + ((j%size) * size)];

	      // Give OpenGL the current terrain texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x/size, -y/size);
	      
	      // Give OpenGL the current detail texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE1_ARB, x/size, -y/size);

	      //glVertex3d(x, y, z);

	      Verts[q][0] = x;
	      Verts[q][1] = y;
	      Verts[q][2] = z;
	      q++;

	      x=i+step;
	      y=j;
	      z=terr[(i + step)%size + ((j%size) * size)]; 


	      // Give OpenGL the current terrain texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x/size, -y/size);
	      
	      // Give OpenGL the current detail texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE1_ARB, x/size, -y/size);


	      //glVertex3d(x, y, z);
	      Verts[q][0] = x;
	      Verts[q][1] = y;
	      Verts[q][2] = z;
	      q++;

	    }

	}
      else
	{
	  for(int j = 0 ; j <= size ; j +=step)
	    {
	      x=i+step;
	      y=j;
	      z=terr[(i+step)%size + ((j%size) * size)];

	      // Give OpenGL the current terrain texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x/size, -y/size);
	      
	      // Give OpenGL the current detail texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE1_ARB, x/size, -y/size);
	      
	      //glVertex3d(x, y, z);
	      Verts[q][0] = x;
	      Verts[q][1] = y;
	      Verts[q][2] = z;
	      q++;
	      
	      x=i ;
	      y=j;
	      z=terr[(i%size) + ((j%size) * size)];

	      // Give OpenGL the current terrain texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE0_ARB, x/size, -y/size);
	      
	      // Give OpenGL the current detail texture coordinate for our height map
	      //glMultiTexCoord2fARB(GL_TEXTURE1_ARB, x/size, -y/size);
	      
	      //glVertex3d(x, y, z);
	      Verts[q][0] = x;
	      Verts[q][1] = y;
	      Verts[q][2] = z;
	      q++;
	    }
	}

    }
  //glEnd();
  //glEndList();

  /*
    for(d = 0; d < q; d++)
    {
    cout <<  Verts[d][0] << " " << Verts[d][1] << " " << Verts[d][2] << "   ";
    }
  */
  // On calcul nos faces et leur vertices respectives, soit face[0] -> Vert[0] Vert[1] Vert[2] etc...
  // On a NumVert - 2 faces finalement (GL_TRIANGLE_TRIP)
  for(d = 0; d < NumFaces; d++)
    {
      for(v = 0; v < 3; v++)
	{
	  for(c = 0; c < 3; c++)
	    {
	      Faces[d][v][c] = Verts[d+v][c];
	      Faces[d][v][c] = Verts[d+v][c];
	      Faces[d][v][c] = Verts[d+v][c];
	    }
	}
    }
  
  // Calcul des normals des faces
  double NormalsFaces[NumFaces][3];
  double NormalsFacesTemps[NumFaces][3];
  double VecA[3], VecB[3], Temp[3], magnitude;
  
  for(d = 0; d < NumFaces; d++)
    {
      // Vecteurs Vert02 et Vert21
      VecA[0] = Faces[d][0][0] - Faces[d][2][0];
      VecA[1] = Faces[d][0][1] - Faces[d][2][1];
      VecA[2] = Faces[d][0][2] - Faces[d][2][2];
      VecB[0] = Faces[d][2][0] - Faces[d][1][0];
      VecB[1] = Faces[d][2][1] - Faces[d][1][1];
      VecB[2] = Faces[d][2][2] - Faces[d][1][2];
  	  
	  
      if(d % 2)
	{
	  // Produit scalaire
	  Temp[0] = ((VecA[1] * VecB[2]) - (VecA[2] * VecB[1]));
	  Temp[1] = ((VecA[2] * VecB[0]) - (VecA[0] * VecB[2]));
	  Temp[2] = ((VecA[0] * VecB[1]) - (VecA[1] * VecB[0]));
	} else {
	  Temp[0] = -((VecA[1] * VecB[2]) - (VecA[2] * VecB[1]));
	  Temp[1] = -((VecA[2] * VecB[0]) - (VecA[0] * VecB[2]));
	  Temp[2] = -((VecA[0] * VecB[1]) - (VecA[1] * VecB[0]));
	}
	  
      NormalsFacesTemps[d][0] = Temp[0];
      NormalsFacesTemps[d][1] = Temp[1];
      NormalsFacesTemps[d][2] = Temp[2];

      // On normalise
      magnitude = sqrt(Temp[0]*Temp[0] + Temp[1]*Temp[1] + Temp[2]*Temp[2]);
      Temp[0] /= (float)magnitude;
      Temp[1] /= (float)magnitude;
      Temp[2] /= (float)magnitude;

      NormalsFaces[d][0] = Temp[0];
      NormalsFaces[d][1] = Temp[1];
      NormalsFaces[d][2] = Temp[2];
    }
  
  // Calcul des normals des vertices cette fois
  double NormalsVertices[NumVerts][3];
  double Somme[3];
  Somme[0] = 0;
  Somme[1] = 0;
  Somme[2] = 0;
  int partages = 0;
  
  for(c = 0; c < NumVerts; c++)
    {
      // On verifie si une des vertices de la face sont partages
      for(d = 0; d < NumFaces; d++)
	{
	  if(	(Faces[d][0][0] == Verts[c][0] 
		 && Faces[d][0][1] == Verts[c][1] 
		 && Faces[d][0][2] == Verts[c][2]) || 
		  	
		(Faces[d][1][0] == Verts[c][0] 
		 && Faces[d][1][1] == Verts[c][1] 
		 && Faces[d][1][2] == Verts[c][2]) || 
		  	
		(Faces[d][2][0] == Verts[c][0] 
		 && Faces[d][2][1] == Verts[c][1] 
		 && Faces[d][2][2] == Verts[c][2])	)
	    {
	      // Nous avons un vertex partage, on aditionne les vecteurs partages
	      Somme[0] += NormalsFacesTemps[d][0];
	      Somme[1] += NormalsFacesTemps[d][1];
	      Somme[2] += NormalsFacesTemps[d][2];
	      partages++;
	    }
	}
      // Divions par le nombre de partages
      NormalsVertices[c][0] = Somme[0] / (float)(-partages);
      NormalsVertices[c][1] = Somme[1] / (float)(-partages);
      NormalsVertices[c][2] = Somme[2] / (float)(-partages);
  
      // Normalisation
      magnitude = sqrt(NormalsVertices[c][0]*NormalsVertices[c][0] + 
		       NormalsVertices[c][1]*NormalsVertices[c][1] + 
		       NormalsVertices[c][2]*NormalsVertices[c][2]);
      NormalsVertices[c][0] /= (float)magnitude;
      NormalsVertices[c][1] /= (float)magnitude;
      NormalsVertices[c][2] /= (float)magnitude;

      // On reset
      partages = 0;
      Somme[0] = 0;
      Somme[1] = 0;
      Somme[2] = 0;
    }
	  
  /*for(d = 0; d < NumFaces; d++)
    {
    cout << Faces[d][0][0] << " " <<
    Faces[d][0][1] << " " <<
    Faces[d][0][2] << " " <<
    Faces[d][1][0] << " " <<
    Faces[d][1][1] << " " <<
    Faces[d][1][2] << " " <<
    Faces[d][2][0] << " " <<
    Faces[d][2][1] << " " <<
    Faces[d][2][2] << " " << endl;
    }*/

  /*  for(d = 0; d < NumVerts; d++)
      {
      cout <<  NormalsVertices[d][0] << " " << NormalsVertices[d][1] << " " << NormalsVertices[d][2] << "   ";
      }
  */


  // On dessine tous les vertices avec leurs normals et on genere la liste d'affichage
  listid = glGenLists(1);
  cout << "listid : " << listid << endl;
  glNewList(listid, GL_COMPILE);

  glBegin( GL_TRIANGLE_STRIP );
  for(d = 0; d < NumVerts; d++)
    {
      glNormal3d(NormalsVertices[d][0], NormalsVertices[d][1], NormalsVertices[d][2]);
	  
      glMultiTexCoord2fARB(GL_TEXTURE0_ARB, Verts[d][0]/size, -Verts[d][1]/size);
	
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB, Verts[d][0]/size, -Verts[d][1]/size);
	      
      glVertex3d(Verts[d][0], Verts[d][1], Verts[d][2]);
    }
  glEnd();

  /*  glBegin( GL_LINES );
      for(d = 0; d < NumVerts; d++)
      {
      glVertex3d(Verts[d][0], Verts[d][1], Verts[d][2]);
      glVertex3d(Verts[d][0]+NormalsVertices[d][0], Verts[d][1]+NormalsVertices[d][1], Verts[d][2]+NormalsVertices[d][2]);
      }
      glEnd();*/
  glEndList();
	  
#ifdef DBG_MODE
  cout << NumVerts << " " << NumFaces << endl;
#endif

}


