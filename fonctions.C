#include "headers.h"

float interval = 0.0f;
long initial_time = 0.0;

void CalculFPS(Graphique *graph)
{
  struct timezone tz;
  static float FPS = 0.0f;
  static float tempsprec = 0.0f;
  static float tempsframe = 0.0f;
  timeval Temp;

  gettimeofday(&Temp, &tz);
  if ( initial_time == 0.0)
    initial_time = Temp.tv_sec;
  float tempscourant = Temp.tv_sec + (Temp.tv_usec / 1000000.0f) - (float)initial_time;
  interval = tempscourant - tempsframe;
  tempsframe = tempscourant;
  ++FPS;

  if(tempscourant - tempsprec > 1.0f)
    {
      tempsprec = tempscourant;
      graph->SetFPS((int)FPS);
      FPS = 0;
    }
}

bool RemoveSelected(Objet * obj)
{
  return obj->GetSelect();
}

bool JeuOrdi(CarteNavale *laCarte)
{
  int Objet;
  srand ( time(NULL) );
  Objet = 101 + rand()% 100;

  for(; ;)
    {
      Objet = 1 + rand()% 100;
      if(laCarte->GetObjet(Objet)->GetEtatJeu() == 1)
        continue;

      if(laCarte->GetObjet(Objet)->GetEtat() == 2 && laCarte->GetObjet(Objet)->GetEtatJeu() == 0)
        {
          laCarte->GetText()->addText(MSG_TOUCH_BOAT, 0);
          laCarte->GetObjet(Objet)->SetEtatJeu(1);
          laCarte->GetObjet(Objet)->Touche();
          if(laCarte->GetObjet(laCarte->GetObjet(Objet)->GetBateau())->VerifierCoule(laCarte)) 
            laCarte->GetText()->addText(MSG_ENEMY_SUN_BOAT, 0);
          break;
        }
      if(laCarte->GetObjet(Objet)->GetEtat() == 3 && laCarte->GetObjet(Objet)->GetTouche() == 1)
        continue;
      
      
      laCarte->GetObjet(Objet)->SetEtatJeu(1);
      break;
    }

  //laCarte->GetText()->addText("L'adversaire a joue, c'est maintenant a votre tour.");
  return laCarte->VerifierGagnant();
}

bool VerifierBateaux(CarteNavale * laCarte)
{
  int i;
  bool OK = true;
  bool *Bateaux =  laCarte->VerifierBateaux();
  
  string message( MISSING_BOAT);
  string message2 = " ";
  for (i = 0 ; i < 5 ; i++)
    {
      if(Bateaux[i] == false)
        {
          OK = false;
	  switch(i+1)
            {
            case 1 :
              message2 += BAT1;
	      message2 += ", ";
              break;
            case 2:
              message2 += BAT2 ;
	      message2 += ", ";
              break;
            case 3:
              message2 += BAT3;
	      message2 += ", ";
              break;
            case 4:
              message2 += BAT4;
	      message2 += ", ";
              break;
            case 5:
              message2 += BAT5;
	      message2 += ", ";
              break;
            }
	}
    }
  if( !OK )
    {
      message += message2;
      laCarte->GetText()->addText(strdup(message.c_str()), 0);
    }

  return OK;
}

bool VerifierPlay(CarteNavale * LaCarte)
{
  unsigned int i;
  double x, y;
  bool nodebug = true ;
  Bateau ** BatEnemis;
  int gridid, rotate;
  std::vector<int> bateaux;

  srand ( time(NULL) );

  if (VerifierBateaux(LaCarte))
    {
      LaCarte->GetSelectedObject()->UnSelect();
      
      bateaux = LaCarte->GetObjectTypes();     
      
      BatEnemis = new Bateau*[bateaux.size()];

      for( i = 0; i < bateaux.size(); i++)
	{
	  BatEnemis[i] = new Bateau(0.0, 0.0, bateaux[i], LaCarte->GetModels(), LaCarte->GetMer(), nodebug);
	  gridid = 101 + rand()% 100;
              
	  rotate = rand()% 2;
	  if (rotate)
	    BatEnemis[i]->Rotate();
              
	  BatEnemis[i]->XYfromgrid(gridid);
	  x = BatEnemis[i]->GetX();
	  y = BatEnemis[i]->GetY();
	  BatEnemis[i]->ArrangerPosition(gridid, gridid, x, y);
	  BatEnemis[i]->SetXY(x, y, BatEnemis[i]->GetZ() );
	  BatEnemis[i]->CalculerListes(gridid);
	  while(!(BatEnemis[i]->VerifierPlacement(LaCarte)))
	    {
	      gridid = 101 + rand()% 100;
	      BatEnemis[i]->XYfromgrid(gridid);
	      x = BatEnemis[i]->GetX();
	      y = BatEnemis[i]->GetY();
	      BatEnemis[i]->ArrangerPosition(gridid, gridid, x, y);
	      BatEnemis[i]->SetXY(x, y, BatEnemis[i]->GetZ() );
	      BatEnemis[i]->CalculerListes(gridid);
                    
	    }
	  LaCarte->ajouterObjet(BatEnemis[i]);
	  //LaCarte->AddBoat();
	  LaCarte->RefreshBoats();
	}
      LaCarte->CommencerJeu(bateaux.size());
      return true;
    }
  return false;
}

void NouveauBateau(CarteNavale *LaCarte, int taille)
{
  Bateau *bat;
  int id;

  if( LaCarte->GetNbreBateaux() == 0 )
    {
      bat = new Bateau(-5, -10.5, taille, LaCarte->GetModels(), LaCarte->GetMer());
      id = bat->GetID();
      LaCarte->ajouterObjet(bat);
      LaCarte->AddBoat();
      if(LaCarte->GetSelectedObject())LaCarte->GetSelectedObject()->UnSelect();
      LaCarte->GetObjet(id)->Selected();
      LaCarte->GetObjet(id)->Edit();
    } else {
      if( LaCarte->GetSelectedObject() != NULL )
	{
	  if(! (LaCarte->GetSelectedObject()->Edition()) )
	    {
	      bat = new Bateau(-5, -10.5, taille, LaCarte->GetModels(), LaCarte->GetMer());
	      id = bat->GetID();
	      LaCarte->ajouterObjet(bat);
	      LaCarte->AddBoat();
	      if(LaCarte->GetSelectedObject())LaCarte->GetSelectedObject()->UnSelect();
	      LaCarte->GetObjet(id)->Selected();
	      LaCarte->GetObjet(id)->Edit();
	    } else {
	      LaCarte->GetText()->addText(MSG_MUST_PLACE_BOAT, 0);
	    }
	}

    }
}
