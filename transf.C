#include "headers.h"

/*---------------------------------------------------------------------------
 * FONCTION: Transformation
 * CLASSE  : Transformation
 *
 * Initialiser une nouvelle transformation � partir d'une fen�tre de X et
 * des coordonn�es d'une fen�tre virtuelle. La cloture est initialis�e �
 * toute la fen�tre X, et les coordonn�es de la cloture sont directement
 * demand�es � X. Un param�tre optionnel permet de sp�cifier le facteur
 * utilis� lors des op�rations de zoom in et de zoom out. La fen�tre
 * sp�cifi�e sera ajust�e de facon � tenir compte du rapport d'aspect de la
 * cloture.
 *
 * ENTREES : ecr : identificateur de connection au serveur X
 *           Xfen : identificateur de la fen�tre X
 *           contexte : contexte GLX
 *           xmin : coordonn�e X minimum de la fen�tre virtuelle
 *           xmax : coordonn�e X maximum de la fen�tre virtuelle
 *           ymin : coordonn�e Y minimum de la fen�tre virtuelle
 *           ymax : coordonn�e Y maximum de la fen�tre virtuelle
 *           incr_zoom : facteur multiplicatif � appliquer � la fen�tre
 *                       lors des operations de zoom in et de zoom out
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
Transformation::Transformation( class QGLWidget* fen,
                                double xmin, double xmax,
                                double ymin, double ymax )
  : fenetreGL(fen),
    x0( xmin ), x1( xmax ), y0( ymin ), y1( ymax ),
    i0( -5 ), j0( 5 )
{
}

/*---------------------------------------------------------------------------
 * FONCTION: mettreAJourCloture
 * CLASSE  : Transformation
 *
 * R�cup�rer les dimensions de la cloture en interrogeant X, et ajuster la
 * fen�tre virtuelle afin de respecter le nouveau rapport d'aspect.
 *
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Transformation::mettreAJourCloture( bool deja_courante )
{
  if( ! deja_courante )
    fenetreGL->makeCurrent();
  glViewport( i0, j0, (GLint)i1, (GLint)j1 );
}

void Transformation::changerCloture( int imin, int imax, int jmin, int jmax )
{
  i0 = imin;
  i1 = imax;
  j0 = jmin;
  j1 = jmax;
}

/*---------------------------------------------------------------------------
 * FONCTION: changerFen�treVirtuelle
 * CLASSE  : Transformation
 *
 * Changer les coordonn�es de la fen�tre virtuelle. Le valeurs fournies
 * seront ajust�es afin de tenir compte du rapport d'aspect de la cloture.
 *
 * ENTREES : double xmin :
 *           double xmax :
 *           double ymin :
 *           double ymax :
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Transformation::changerFenetreVirtuelle( double xmin, double xmax,
                                              double ymin, double ymax )
{
  x0 = xmin;
  x1 = xmax;
  y0 = ymin;
  y1 = ymax;
}

/*---------------------------------------------------------------------------
 * FONCTION: ajusterFen�tre
 * CLASSE  : Transformation
 *
 * Fonction servant � ajuster les coordonn�es d'une fen�tre virtuelle en
 * fonction de la cloture de facon � ce que le rapport d'aspect soit
 * respecter.
 *
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void Transformation::ajusterFenetre( bool deja_courante )
{
  if( ! deja_courante )
    fenetreGL->makeCurrent();
  
  double width, height;

  width = i1;
  height = j1;
  
  int mode;
  glGetIntegerv(GL_RENDER_MODE,&mode);
  if ( mode != GL_SELECT )
    {
      aspect = (width/height);
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();

      gluPerspective( 45.0f, aspect , 0.5f, 550.0f );
      
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
    }
}
