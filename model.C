#include "headers.h"

Models3D::Models3D(Textures *ptrTextures)
{
  i = 0;
  lesTextures = ptrTextures;
}

Models3D::~Models3D()
{
}

void Models3D::MakeList(t3DModel & g_3DModel, char * NomFichier)
{
  ListIDs[NomFichier] = glGenLists(1);

#ifdef DBG_MODE	
  cout << "model " <<  NomFichier << " a une liste : " << ListIDs[NomFichier] << endl;

  cout << "IN MAKE of " << ListIDs[NomFichier] << " " << NomFichier << endl;

  cout << "nummaterials : " << g_3DModel.numOfMaterials << endl;

  for(int w = 0; w < g_3DModel.numOfMaterials; w++)
    {
      //if(strlen(g_3DModel.pMaterials[w].strFile) > 0)
      //{
      cout << "texture : " << g_3DModel.pMaterials[w].strFile << endl;           
      //}
    }

#endif
  int vertex = 0, triangles =0;

  glNewList(ListIDs[NomFichier], GL_COMPILE);

  glEnable(GL_BLEND);

  for(int i = 0; i < g_3DModel.numOfObjects; i++)
    {
      // Make sure we have valid objects just in case. (size() is in the vector class)
      if(g_3DModel.pObject.size() <= 0) break;
      
      // Get the current object that we are displaying
      t3DObject *pObject = &g_3DModel.pObject[i];
      
      
      // Check to see if this object has a texture map, if so bind the texture to it.
      if(pObject->bHasTexture) {
#ifdef DBG_MODE
	cout << "texture on : " << NomFichier << " ID : " << pObject->materialID << endl;
	cout << "texture file is : " << g_3DModel.pMaterials[pObject->materialID].strFile << endl;
#endif
      

	// Turn on texture mapping and turn off color
	glEnable(GL_TEXTURE_2D);
	
	// Reset the color to normal again
	glColor3ub(255, 255, 255);
	
	// Bind the texture map to the object by it's materialID
	lesTextures->BindTexture(g_3DModel.pMaterials[pObject->materialID].strFile);
      } else {

	// Turn off texture mapping and turn on color
	glDisable(GL_TEXTURE_2D);
	
	// Reset the color to normal again
	glColor3ub(255, 255, 255);
      }
      
      // This determines if we are in wireframe or normal mode
      glBegin(GL_TRIANGLES);                    // Begin drawing with our selected mode (triangles or lines)
      
      // Go through all of the faces (polygons) of the object and draw them
      for(int j = 0; j < pObject->numOfFaces; j++)
	{
	  // Go through each corner of the triangle and draw it.
	  for(int whichVertex = 0; whichVertex < 3; whichVertex++)
	    {


	      // Get the index for each point of the face
	      int index = pObject->pFaces[j].vertIndex[whichVertex];
	      
	      // Give OpenGL the normal for this vertex.
	      glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
	      triangles++;
	      
	      
	      // If the object has a texture associated with it, give it a texture coordinate.
	      if(pObject->bHasTexture) {
		
		// Make sure there was a UVW map applied to the object or else it won't have tex coords.
		if(pObject->pTexVerts) {
		  glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
		}
	      } else {
		
		// Make sure there is a valid material/color assigned to this object.
		// You should always at least assign a material color to an object, 
		// but just in case we want to check the size of the material list.
		// if the size is at least one, and the material ID != -1,
		// then we have a valid material.
		if(g_3DModel.pMaterials.size() && pObject->materialID >= 0) 
		  {
		    // Get and set the color that the object is, since it must not have a texture
		    BYTE *pColor = g_3DModel.pMaterials[pObject->materialID].color;
		    
		    // Assign the current color to this model
		    glColor3ub(pColor[0], pColor[1], pColor[2]);
		  }
	      }

	      // Pass in the current vertex of the object (Corner of current face)
	      glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].z, pObject->pVerts[ index ].y);
	      vertex++;
	    }
	}
      
      glEnd();                                // End the drawing
      glEnable(GL_TEXTURE_2D);
    }

  glDisable(GL_BLEND);

  glEndList();
#ifdef DBG_MODE
  cout << "triangles : " << triangles << " Vertex : " << vertex << endl;
#endif
}

void Models3D::LoadModel(char * NomFichier)
{
#ifdef DBG_MODE
  cout << "Importing " << NomFichier << endl;
#endif
  g_Load3ds[i].Import3DS(&Models[i], NomFichier);
#ifdef DBG_MODE
  cout << "Imported\n";
#endif
  for(int k = 0; k < Models[i].numOfMaterials; k++)
    {
      if(strlen(Models[i].pMaterials[k].strFile) > 0)
	{
#ifdef DBG_MODE
	  cout << "loading texture : " << Models[i].pMaterials[k].strFile
	       << " " <<strlen(Models[i].pMaterials[k].strFile) << endl;
#endif
	  lesTextures->CreerTexture(Models[i].pMaterials[k].strFile);
#ifdef DBG_MODE
	  cout << "end loading texture\n";
#endif
	}
      //g_3DModel.pMaterials[i].texureId = i;
    }
#ifdef DBG_MODE
  cout << "Making list\n";
#endif
  MakeList(Models[i], NomFichier);
	
  int j;
#ifdef DBG_MODE
  cout << "deleting\n";
#endif
  for(j = 0; j < Models[i].numOfObjects; j++)
    {
      //	  cout <<"delete pfaces\n";
      if(Models[i].pObject[j].pFaces) delete [] Models[i].pObject[j].pFaces;
      //	  cout << "delete pNormals\n";
      if(Models[i].pObject[j].pNormals) delete [] Models[i].pObject[j].pNormals;
      //	  cout << "delete pVerts\n";
      if(Models[i].pObject[j].pVerts) delete [] Models[i].pObject[j].pVerts;
      //	  cout <<"delete pTexVerts\n";
      if(Models[i].pObject[j].pTexVerts) delete [] Models[i].pObject[j].pTexVerts;
    }
#ifdef DBG_MODE
  cout <<"end deleting\n";
#endif
  i++;
}

void Models3D::DrawModel(char * NomFichier)
{

  if(!strcmp(NomFichier, "./models/sub.3ds")) glCallList(1);
  if(!strcmp(NomFichier, "./models/porte.3ds")) glCallList(2);
  if(!strcmp(NomFichier, "./models/light.3ds")) glCallList(3);
  if(!strcmp(NomFichier, "./models/croiseur.3ds")) glCallList(4);
  if(!strcmp(NomFichier, "./models/contretor.3ds")) glCallList(5);
  if(!strcmp(NomFichier, "./models/cuirasse.3ds")) glCallList(6);
  if(!strcmp(NomFichier, "./models/Palmtree.3ds")) glCallList(7);
  if(!strcmp(NomFichier, "./models/skull.3ds")) glCallList(8);
  if(!strcmp(NomFichier, "./models/bomb.3ds")) glCallList(9);
  
  
  /*if(ListIDs[NomFichier])
    glCallList(ListIDs[NomFichier]);*/

}
