#include "headers.h"

/*---------------------------------------------------------------------------
 * FONCTION: Transformation
 * CLASSE  : Transformation
 *
 * Initialiser une nouvelle transformation à partir d'une fenêtre de X et
 * des coordonnées d'une fenêtre virtuelle. La cloture est initialisée à
 * toute la fenêtre X, et les coordonnées de la cloture sont directement
 * demandées à X. Un paramètre optionnel permet de spécifier le facteur
 * utilisé lors des opérations de zoom in et de zoom out. La fenêtre
 * spécifiée sera ajustée de facon à tenir compte du rapport d'aspect de la
 * cloture.
 *
 * ENTREES : ecr : identificateur de connection au serveur X
 *           Xfen : identificateur de la fenêtre X
 *           contexte : contexte GLX
 *           xmin : coordonnée X minimum de la fenêtre virtuelle
 *           xmax : coordonnée X maximum de la fenêtre virtuelle
 *           ymin : coordonnée Y minimum de la fenêtre virtuelle
 *           ymax : coordonnée Y maximum de la fenêtre virtuelle
 *           incr_zoom : facteur multiplicatif à appliquer à la fenêtre
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
 * Récupérer les dimensions de la cloture en interrogeant X, et ajuster la
 * fenêtre virtuelle afin de respecter le nouveau rapport d'aspect.
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
 * FONCTION: changerFenêtreVirtuelle
 * CLASSE  : Transformation
 *
 * Changer les coordonnées de la fenêtre virtuelle. Le valeurs fournies
 * seront ajustées afin de tenir compte du rapport d'aspect de la cloture.
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
 * FONCTION: ajusterFenêtre
 * CLASSE  : Transformation
 *
 * Fonction servant à ajuster les coordonnées d'une fenêtre virtuelle en
 * fonction de la cloture de facon à ce que le rapport d'aspect soit
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
