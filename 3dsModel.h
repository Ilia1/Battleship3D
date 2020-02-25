#ifndef _3DSMODEL_H
#define _3DSMODEL_H



typedef unsigned char BYTE;


// This file includes all of the model structures that are needed to load
// in a .3DS file.  If you intend to do animation you will need to add on
// to this.  These structures only support the information that is needed
// to load the objects in the scene and their associative materials.

#define MAX_TEXTURES 100                                // The maximum amount of textures to load



// This is our 3D point class.  This will be used to store the vertices of our model.
class CVector3 
{
 public:
  float x, y, z;
};

// This is our 2D point class.  This will be used to store the UV coordinates.
class CVector2 
{
 public:
  float x, y;
};

// This is our face structure.  This is is used for indexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace
{
  int vertIndex[3];           // indicies for the verts that make up this triangle
  int coordIndex[3];          // indicies for the tex coords to texture this face
};

// This holds the information for a material.  It may be a texture map of a color.
// Some of these are not used, but I left them because you will want to eventually
// read in the UV tile ratio and the UV tile offset for some models.
struct tMaterialInfo
{
  char  strName[255];         // The texture name
  char  strFile[255];         // The texture file name (If this is set it's a texture map)
  BYTE  color[3];             // The color of the object (R, G, B)
  int   texureId;             // the texture ID
  float uTile;                // u tiling of texture  (Currently not used)
  float vTile;                // v tiling of texture  (Currently not used)
  float uOffset;              // u offset of texture  (Currently not used)
  float vOffset;              // v offset of texture  (Currently not used)
} ;

// This holds all the information for our model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject 
{
  int  numOfVerts;            // The number of verts in the model
  int  numOfFaces;            // The number of faces in the model
  int  numTexVertex;          // The number of texture coordinates
  int  materialID;            // The texture ID to use, which is the index into our texture array
  bool bHasTexture;           // This is TRUE if there is a texture map for this object
  char strName[255];          // The name of the object
  CVector3  *pVerts;          // The object's vertices
  CVector3  *pNormals;        // The object's normals
  CVector2  *pTexVerts;       // The texture's UV coordinates
  tFace *pFaces;              // The faces information of the object
};

// This holds our model information.  This should also turn into a robust class.
// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
struct t3DModel 
{
  int numOfObjects;                   // The number of objects in the model
  int numOfMaterials;                 // The number of materials for the model
  vector<tMaterialInfo> pMaterials;   // The list of material information (Textures and colors)
  vector<t3DObject> pObject;          // The object list for our model
};

void DrawModel(t3DModel & g_3DModel);
void CreateTexture(unsigned int textureArray[],char *strFileName,int textureID);

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


#endif  // _3DSMODEL_H_

/////////////////////////////////////////////////////////////////////////////////
////
//// * QUICK NOTES *
////
//// This file includes all the structures that you need to hold the model data.
//// Of course, if you want a robust loader, you need some more things for animation, etc..
//// If you intend to use this code, I would make the model and object structures classes.
//// This way you can have a bunch of helper functions like Import(), Translate(), Render()...
////
//// * What's An STL (Standard Template Library) Vector? *
//// Let me quickly explain the STL vector for those of you who are not familiar with them.
//// To use a vector you must include <vector> and use the std namespace: using namespace std;
//// A vector is an array based link list.  It allows you to dynamically add and remove nodes.
//// This is a template class so it can be a list of ANY type.  To create a vector of type
//// "int" you would say:  vector<int> myIntList;
//// Now you can add a integer to the dynamic array by saying: myIntList.push_back(10);
//// or you can say:  myIntList.push_back(num);.  The more you push back, the larger
//// your array gets.  You can index the vector like an array.  myIntList[0] = 0;
//// To get rid of a node you use the pop_back() function.  To clear the vector use clear().
//// It frees itself so you don't need to worry about it, except if you have data
//// structures that need information freed from inside them, like our objects.
////
//// The Import() function would decide which loader it needed to call, depending on the extension.
////
////
////
//// Ben Humphrey (DigiBen)
//// Game Programmer
//// DigiBen@GameTutorials.com
//// Co-Web Host of www.GameTutorials.com
////
////
////
