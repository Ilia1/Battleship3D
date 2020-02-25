#include "headers.h"

Case::Case(int numero, Models3D *ptrModels)
{
  id = numero;
  if ( id <= 100 ) {
    x = id % 10;
    if ( x == 0 ) {
      x = 10;
      y = int(id/10);
    } else {
      y = int((id / 10) + 1);
    }

    // On transforme en coordonnes du monde virtuel, on a le coin inferieur gauche
    x -= 6;
    y -= 11.5;

  } else if ( id >= 101 ) {
    int temp;
    temp = id - 100;

    x = temp % 10;
    if ( x == 0 ) {
      x = 10;
      y = int(temp/10);
    } else {
      y = int((temp / 10) + 1);
    }

    // On transforme en coordonnes du monde virtuel, on a le coin inferieur gauche
    x -= 6;
    y -= 0.5;
		
  }
  select = false;
  etatprimaire = 1;
  etatjeu = 0;
  bateau = 0;
  rotation = 0;
  touche = false;
  lesModeles = ptrModels;
}

Case::~Case()
{
}

void Case::afficher()
{

  double bcolor, rcolor, gcolor,  alpha;
  
  //glDisable(GL_DEPTH_TEST);
  
  if(etatjeu == 1)
    {
      rcolor = 1.0;
      gcolor = 1.0;
      bcolor = 1.0;
      alpha = 1.0;
      glBindTexture(GL_TEXTURE_2D, grid2);
    }
  else
    {
      rcolor = 1.0;
      gcolor = 1.0;
      bcolor = 1.0;
      alpha = 1.0;
      glBindTexture(GL_TEXTURE_2D, grid1);
    }
  if(touche)    
    {
      glPushMatrix();
      glTranslatef(x+0.5f, y+0.5f, 1.0f);
      glScalef(0.05f, 0.05f, 0.05f);
      //glRotatef(-180, 0.0f, 0.0f, 1.0f);
      glRotatef(rotation, 0.0f, 0.0f, 1.0f);
      incrRot(5);
      lesModeles->DrawModel("./models/bomb.3ds");
      glPopMatrix();
      rcolor = 1.0;
      gcolor = 1.0;
      bcolor = 1.0;
      alpha = 1.0;
      glBindTexture(GL_TEXTURE_2D, grid3);
    }
    
  glEnable(GL_BLEND);
  
  glLoadName(id);
  
  glBegin(GL_QUADS);
  glColor4f(rcolor, gcolor, bcolor, alpha);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d( x, y, 0.5 );
  glTexCoord2f(1.0f, 0.0f);
  glVertex3d( x+1, y, 0.5 );
  glTexCoord2f(1.0f, 1.0f);
  glVertex3d( x+1, y+1, 0.5 );
  glTexCoord2f(0.0f, 1.0f);
  glVertex3d( x, y+1, 0.5 );
  glEnd();

  glEnd();

  glDisable(GL_BLEND);
  //glEnable(GL_DEPTH_TEST);

}


void Case::Write(ostream & out)
{
  out << "0 " << id << " " << select << " " << x << " " << y << " 0.5 "
      << bateau << " " << etatprimaire << " " << etatjeu << " " << touche 
      << " " << endl;
  
}

void Case::Read(istream & in)
{
  in >> id >>  select >> x >> y >> z >> bateau >> etatprimaire >> etatjeu 
     >> touche;
  
}

