/* Définition d'une classe permettant de stocker les données sur une fenêtre
   X et la transformation entre le monde virtuelle et le monde d'affichage à
   utiliser pour tracer. */

#ifndef _HEADER_Transformation_
#define _HEADER_Transformation_

#include "headers.h"

class Transformation
{
 public:
  // constructeur
  Transformation( class QGLWidget* fen,
		  double xmin = 0, double xmax = 0, double ymin = 0, double ymax = 0 );

  void mettreAJourCloture( bool deja_courante );
  void changerFenetreVirtuelle( double xmin, double xmax, double ymin, double ymax );
  void changerCloture( int imin, int imax, int jmin, int jmax );
  int GetWidth(){return i1;};
  int GetHeight(){return j1;};
  void ajusterFenetre( bool deja_courante );


 private:
  class QGLWidget* fenetreGL;
  double   x0, x1, y0, y1, aspect;
  int      i0, i1, j0, j1;
};

#endif
