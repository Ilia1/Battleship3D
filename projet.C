/*=======================================================================
 * Programme principal
 *=====================================================================*/

#include "headers.h"

/**
 * @fn  int main( int argc, char **argv )
 *
 * Programme principal pour le tp1.
 *
 * @param argc : nombre de param�tres pass�s au programme
 * @param argv : cha�nes de caract�res contenant chaque param�tre.
 * @return 0: application termin�e normalement; != 0: erreur
 * @exception
 *
 */


int main( int argc, char **argv )
{
#ifdef DBG_MODE
  cout << "Debut du main\n";
#endif

#ifdef USE_SKIN
  int i;
  char **args = new char*[argc + 1];
  for(i =0; i < argc ; i++)
    {
      args[i] = new char[strlen(argv[i]) +1];
      strcpy(args[i], argv[i]);
    }
  args[i] = new char[strlen("-style=cde") + 1 ];
  strcpy(args[i],"-style=cde" );

  argc++;

  QApplication app( argc, args );
#endif
#ifndef USE_SKIN
  QApplication app( argc, argv );
#endif

  Principale* principale = new Principale;
  QMainWindow* fenetrePrincipale = principale->getFenetrePrincipale();

//  app.setMainWidget( fenetrePrincipale );
  fenetrePrincipale->show( );



  fflush(stdout);
  return app.exec( );
}
