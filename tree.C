#include "headers.h"

Tree::Tree(Models3D * ptrModels)
{
  lesModeles = ptrModels; 
};

Tree::Tree(double _x, double _y, double _z, Models3D * ptrModels, float xs, float ys, float zs)
{ 
  x = _x;
  y = _y;
  z = _z;
  lesModeles = ptrModels; 
  xscale = xs; 
  yscale = ys; 
  zscale = zs;
  id = 0;
  select = 0;
};


Tree::~Tree()
{
};

void Tree::afficher() 
{ 
  glPushMatrix();
  //glRotatef((xscale - 0.1f)*3600, 0.0f, 0.0f, 1.0f);
  glTranslatef(x, y, z); 
  glScalef(xscale, yscale, zscale);
  glRotatef((xscale - 0.1f)*3600, 0.0f, 0.0f, 1.0f);
  lesModeles->DrawModel("./models/Palmtree.3ds"); 
  glPopMatrix(); 
};


void Tree::Read(istream & in)
{
  in >> x >> y >> z >> xscale >> yscale 
     >>	zscale >> id >> select;
}


void Tree::Write(ostream &out)
{
  out << "2 " << x << " " << y << " "<< z << " " << xscale << " " 
      << yscale << " " << zscale << " " << id << " " << select << endl;
}
