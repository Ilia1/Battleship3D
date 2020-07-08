#include "headers.h"



int Bateau::static_id = 200;

Bateau::Bateau(Models3D *ptrModels, Mer *ptrMer)
{
  lesModeles = ptrModels;
  laMer = ptrMer;
}

Bateau::Bateau(double _I, double _J, int _L, Models3D *ptrModels, Mer *ptrMer, bool en)
{

  ennemi = en;
  id = ++static_id;
  
  type = _L;

  if( _L == 2) _L = 3;
  if( _L == 1) _L = 2;
  
  m_cLen = _L;

  x = _I;
  y = _J;
  
  if(type == 2)
    z = -0.9;
  else
    z = -0.6;
  deg = 0;
  select = false;
  edition = false;
  coule = false;
  touches = 0;

  int k;
  for ( k = 0; k < 22; k++)
    liste[k] = 0;
  for ( k = 0; k < 5; k++)
    liste2[k] = 0;

  gridid =0;
  gridtemp = 0;
  gridtemp2 = 0;
  gridtemp3 = 0;
  lesModeles = ptrModels;
  laMer = ptrMer;
}

void Bateau::XYfromgrid(int gridid)
{	
  if ( gridid <= 100 ) {
    x = gridid % 10;
    
    if ( x == 0 ) {
      x = 10;
      y = int(gridid/10);
    } else {
      y = int((gridid / 10) + 1);
    }
      
    // On transforme en coordonnes du monde virtuel, on a le coin inferieur gauche
    x -= 6;
    y -= 11.5;
  } else if ( gridid >= 101 ) {
    int temp;
    temp = gridid - 100;

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
}

Bateau::~Bateau()
{

}

ostream& Bateau::imprimer( ostream& out ) const
{
  /*out << "Bateau " << id 
    << " au coordonees : " << m_cPosI << " " 
    << m_cPosJ << " " <<  z 
    << "\nLength : " << m_cLen << endl;*/

  if(ennemi) return out;

  out << TYPE_OF_BOAT"\nType of boat ";
  switch(type)
    {
    case 1 :
      out << "Against-Torpedo," ;
      break;
    case 2:
      out << "Submarine,";
      break;
    case 3:
      out << "Cruiser,";
      break;
    case 4:
      out << "Cuirass,";
      break;
    case 5:
      out << "Aircraft carrier,";
      break;
    }
  out << " place at coordinates : " << x << " " 
      << y << " "  << "\nWith Id number : " << id << endl;

  if(select) out << "This boat is the selected boat\n";

  if(touches)
    out << "The boat was hit " << touches << " time.\n";
	
  return out;
}


void Bateau::afficher()
{
  double zm = 0.6;

  if (ennemi && !coule) return;
  
  glLoadName(id);

  glPushMatrix();
  
 
  glTranslatef( x, y, 0);
  glRotatef(deg, 0,0,1);
  glTranslatef(- x,- y, 0);
 
  if(deg == -90)
    glTranslatef(-1.0,0.0,0.0);
  
  if(select)
    {
      glColor4d(1.0f, 0.5f, 0.5f, 0.9f);
    }
  else if(coule)
    glColor4d(0.5f, 0.0f, 0.0f, 1.0);
  else
    glColor4d(0.0, 0.3, 0.6, 1.0);

  if(type == 1)
    {
      glTranslatef(x+1.0f, y+0.5f, laMer->GetHeight(x+1.0f, y+0.5f));
      glScalef(0.035f, 0.085f, 0.04f);
      if(coule)
	{
	  glRotatef(30, 1.0f, 0.0f, 0.0f);
	  glTranslatef(0.0f, 0.0f, -5.95f);
	}
      lesModeles->DrawModel("./models/contretor.3ds");
      glPopMatrix();
      return;
    } else if(type == 2)
      {
	glTranslatef(x+1.8f, y+0.5f, laMer->GetHeight(x+1.8f, y+0.5f)-0.15f);
	glScalef(0.15f, 0.15f, 0.15f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	if(coule)
	  {
	    glRotatef(-30, 0.0f, 1.0f, 0.0f);
	    glTranslatef(0.0f, 0.0f, -0.5f);
	  }
	lesModeles->DrawModel("./models/sub.3ds");
	glPopMatrix();
	return;
      } else if(type == 3)
	{
	  glTranslatef(x+1.55f, y+0.5f, laMer->GetHeight(x+1.55f, y+0.5f));
	  glScalef(0.035f, 0.1f, 0.075f);
	  if(coule)
	    {
	      glRotatef(-30, 1.0f, 0.0f, 0.0f);
	      glTranslatef(0.0f, 0.0f, -6.0f);
	    }
	  lesModeles->DrawModel("./models/croiseur.3ds");
	  glPopMatrix();
	  return;
	} else if(type == 4)
	  {
	    glTranslatef(x+2.0f, y+0.6f, laMer->GetHeight(x+2.0f, y+0.6f)-0.2f);
	    glScalef(0.8f, 0.8f, 0.8f);
	    glRotatef(90, 0.0f, 0.0f, 1.0f);
	    if(coule)
	      {
		glRotatef(30, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.5f);
	      }
	    lesModeles->DrawModel("./models/cuirasse.3ds");
	    glPopMatrix();
	    return;

	  } else if(type == 5)

	    {
	      glTranslatef(x+2.4f, y+0.6f, laMer->GetHeight(x+2.4f, y+0.6f));
	      glScalef(0.01f, 0.01f, 0.01f);
	      glRotatef(90, 0.0f, 0.0f, 1.0f);
	      if(coule)
		{
		  glRotatef(-30, 0.0f, 1.0f, 0.0f);
		  glTranslatef(0.0f, 0.0f, -50.5f);
		}
	      lesModeles->DrawModel("./models/porte.3ds");
	      glPopMatrix();
	      return;
	    }

  glPopMatrix();

  glEnd();

  if(select){
    // glDisable(GL_BLEND);
    //    glEnable(GL_DEPTH_TEST);
  }

    

    
}

void Bateau::Rotate()
{

  if(deg) deg = 0;
  else  deg = -90;

}

void Bateau::RotateSurPlace(CarteNavale * LaCarte)
{
  int gridid = 0, gridid2 = 0, i;
  double old_x, old_y;
  int old_deg;
  int old_liste[22];
  int old_liste2[5];       

  old_x = x;
  old_y = y;
  old_deg = deg;
  for(i = 0; i < 22; i++)
    old_liste[i] = liste[i];
  for(i = 0; i < 5; i++)
    old_liste2[i] = liste2[i];
	
  Rotate();
  gridid = liste2[0];
  gridid2 = gridid;
	
  ArrangerPosition(gridid, gridid2, x, y);
		
  if( deg != 0 )
    CalculerListes(gridid2);
  else
    CalculerListes(gridid2 + 10*(m_cLen-1));
	
  edition = true;
  LaCarte->RefreshBoats();
  if ( VerifierPlacement(LaCarte) )
    {
      edition = false;
      LaCarte->RefreshBoats();
    } else {
      x = old_x;
      y = old_y;
      deg = old_deg;
      for(i = 0; i < 22; i++)
	liste[i] = old_liste[i];
      for(i = 0; i < 5; i++)
	liste2[i] = old_liste2[i];
      edition = false;
      LaCarte->RefreshBoats();
    }
}


void Bateau::MoveBoat(CarteNavale * LaCarte, int gridid)
{
  int gridid2 = 0, i;
  double old_x, old_y;
  int old_deg;
  int old_liste[22];
  int old_liste2[5];       

  old_x = x;
  old_y = y;
  old_deg = deg;
  for(i = 0; i < 22; i++)
    old_liste[i] = liste[i];
  for(i = 0; i < 5; i++)
    old_liste2[i] = liste2[i];

  gridid2 = gridid;
  XYfromgrid(gridid);
	
  ArrangerPosition(gridid, gridid2, x, y);

  cout << "x " << x << " y " << y << endl;
	
  CalculerListes(gridid2);
		
  edition = true;
  LaCarte->RefreshBoats();
  if ( VerifierPlacement(LaCarte) )
    {
      edition = false;
      LaCarte->RefreshBoats();
    } else {
      x = old_x;
      y = old_y;
      deg = old_deg;
      for(i = 0; i < 22; i++)
	liste[i] = old_liste[i];
      for(i = 0; i < 5; i++)
	liste2[i] = old_liste2[i];
      edition = false;
      LaCarte->RefreshBoats();
    }
}


void Bateau::MouseReleaseEvent1(Graphique *graph, double _x, double _y)
{
  bool Allie;

  gridid = graph->GetGrid((int) _x, (int) _y, 0.01, 0.01, _x, _y, Allie);
  gridtemp2 = gridid;
	
  if( gridid != -1 && (Allie))
    {
      Rotate();
      ArrangerPosition(gridid, gridtemp2, _x, _y);
      gridtemp3 = gridtemp2;
      x = _x;
      y = _y;
      // z = -0.5;
    }
}

void Bateau::MouseReleaseEvent2(Graphique *graph)
{
  CalculerListes(gridtemp3);
  if ( VerifierPlacement(graph->obtenirCarte()) )
    {
      edition = false;
      graph->obtenirCarte()->RefreshBoats();
      gridid = 0;
      gridtemp = 0;
      gridtemp2 = 0;
      gridtemp3 = 0;

    }
}

void Bateau::MouseMotionEvent(QMouseEvent * ev, Graphique *graph)
{
  double _x, _y;
  bool Allie;
  _x = ev->x();
  _y = ev->y();

  gridid = graph->GetGrid((int) _x, (int) _y, 0.01, 0.01, _x, _y, Allie);

  gridtemp2 = gridid;
  if(gridtemp == gridid) 
    return;
  gridtemp = gridid;
	      
  if((gridid != -1) && (Allie))
    {
      ArrangerPosition(gridid, gridtemp2, _x, _y);
      gridtemp3 = gridtemp2;
      x = _x;
      y = _y;
      // z = -0.5;
    }
}
	

void Bateau::SetType(CarteNavale * carte, int t)
{
  int temp, i;


  if (type > t)
    {
      temp = type - t;
      //cout << type << " " << t << " " << temp << endl;
      for(i=0; i < temp ; i++)
	DiminuerTaille(carte);
    }
  else
    {
      temp = t - type;
      //cout << type << " " << t << " " << temp << endl;
      for(i=0; i < temp ; i++) 
	AugmenterTaille(carte);
    }
}

void Bateau::DiminuerTaille(CarteNavale *laCarte)
{
  if (type == 3) 
    {
      m_cLen = 3;
      type--;
      z = -0.9;
      return;
    }
  if(m_cLen > 2)
    {
      m_cLen--;
      type--;

      if ( !edition )
	{
	  if ( deg == 0 )
	    laCarte->GetSelectedObject()->CalculerListes(liste2[0]);
	  else
	    laCarte->GetSelectedObject()->CalculerListes(liste2[m_cLen]);
	  
	  laCarte->RefreshBoats();
	}
      z = -0.6;
    }
}

void Bateau::AugmenterTaille(CarteNavale * laCarte)
{

  if (type == 2) 
    {
      z = -0.6;
      m_cLen = 3;
      type++;
      return;
    }
  if(m_cLen < 5
     && !((deg == 0) && (liste2[m_cLen-1] % 10) == 0)
     && !((deg == -90) && (liste2[0] - 10 <= 0)) )

    {
      if (type == 1)
	z = -0.9;
      else
	z = -0.6;
      m_cLen++;
      type++;
      

      if ( !edition )
	{
	  if ( deg == 0 )
	    laCarte->GetSelectedObject()->CalculerListes(liste2[0]);
	  else
	    laCarte->GetSelectedObject()->CalculerListes(liste2[m_cLen-2]);
 
	  edition = true;
	  laCarte->RefreshBoats();


	  if ( VerifierPlacement(laCarte) )
	    {
	      edition = false;
	      laCarte->RefreshBoats();
	    }
	  else
	    {
	      edition = false;
	      DiminuerTaille(laCarte);
	    }
	}
    }
}

double Bateau::GetLargeur_x ()
{
  if(deg == 0)
    return (m_cLen / 2);
  else
    return 0.5;
}
double Bateau::GetLargeur_y ()
{
  if(deg == -90)
    return (m_cLen / 2);
  else
    return 0.5;

}

bool Bateau::VerifierPlacement(CarteNavale * LaCarte)
{
  int m;
	
  for ( m = 0; m < m_cLen; m++ )
    {
      if(liste2[m] != 0 && LaCarte->GetObjet(liste2[m])->GetEtat() != 1 )
	return false;
    }

  return true;
}

void Bateau::CalculerListes(int gridid)
{

  int idx = 0;
  int idx2 = 0;
  int currentgrid = 0;
  int k, l, m;
	
  for ( m = 0; m < 22; m++ )
    liste[m] = 0;

  for ( m = 0; m < 5; m++)
    liste2[m] = 0;
		
  if(ennemi)
    gridid -= 100;
	
  if (deg == 0)
    {
      k = 3;
      l = (m_cLen + 2);
    } 
  else 
    {
      k = (m_cLen + 2);
      l = 3;
      gridid -= ((m_cLen - 1) * 10);
    }
	
  for(int i = 0; i < k; i++)
    {
      currentgrid = (gridid - 11) + (10 * i);
      for(int j = 0; j < l; j++)
	{
	  if ( (currentgrid + j) < 101 && (currentgrid + j) > 0)
	    {
	      if ( !((j == 0) && (((currentgrid) % 10) == 0)) )
		if ( !(j == (l-1) && (currentgrid + j) == 1) )
		  liste[idx] = currentgrid + j;
				
	      if( i != 0 && i != (k -1) && j != 0 && j != (l - 1) )
		{
		  liste2[idx2] = currentgrid + j;
		  idx2++;
		}
				
	      if ( ((currentgrid + j) % 10) == 0 && (j < l-1) && (j != 0) )
		{
		  idx+=2;
		  break;
		}

	    }
	  idx++;
	}
    }

  if(ennemi)
    {
      for ( m = 0; m < 22; m++ )
	{
	  if(liste[m] != 0)
	    liste[m] += 100;
	}
      for ( m = 0; m < 5; m++)
	{
	  if(liste2[m] != 0)
	    liste2[m] += 100;
	}
    }

}
	
void Bateau::Placer(CarteNavale * LaCarte) 
{
  int k, l;
  int idx = 0;
	
  if (deg == 0)
    {
      k = 3;
      l = (m_cLen + 2);
    } 
  else 
    {
      k = (m_cLen + 2);
      l = 3;
    }

  for(int i = 0; i < k; i++)
    {
      for(int j = 0; j < l; j++)
	{
	  if ( liste[idx] != 0 ) {
	    if ( i == 0 || i == ( k - 1) )
	      LaCarte->GetObjet(liste[idx])->SetEtat(3);
	    else if ( j == 0 || j == (l - 1) )
	      LaCarte->GetObjet(liste[idx])->SetEtat(3);
	    else
	      {
		LaCarte->GetObjet(liste[idx])->SetEtat(2);
		LaCarte->GetObjet(liste[idx])->SetBateau(id);
		//				cout << "\ncase " << liste[idx] << " avec bateau " << id << endl;
		//				cout << LaCarte->GetObjet(liste[idx])->GetBateau();
	      }
	  }

	  idx++;
	}
    }
}

void Bateau::ArrangerPosition(int gridid, int &gridtemp2, double &_x, double &_y)
{
  if ( ennemi )
    gridid -= 100;

  if( ( deg == 0 ))
    {
      if( (gridid % 10) == 0 )
	{
	  _x -= m_cLen - 1;
	  gridtemp2 -= m_cLen - 1;
	}
      else if(((gridid % 10) + m_cLen) >= 11)
	{
	  _x -= ( ((gridid % 10) + m_cLen) - 11 );
	  gridtemp2 -= ( ((gridid % 10) + m_cLen) - 11 );
	}
		
    } else if ( ( deg == -90 )) {
      if( int(gridid / 10) < m_cLen)
	{
	  if( (gridid % 10) == 0)
	    {
	      _y += m_cLen - int(gridid / 10);
	      gridtemp2 += ((m_cLen - int(gridid / 10)) * 10);
	    }
	  else
	    {
	      _y += m_cLen - int(gridid / 10) - 1;
	      gridtemp2 += ((m_cLen - int(gridid / 10) - 1) * 10);
	    }
	}
    }
}

bool Bateau::VerifierCoule(CarteNavale * LaCarte)
{
  int i;

  touches = 0;

  for(i = 0; i < m_cLen ; i++)
    {
      
      if(LaCarte->GetObjet(liste2[i])->GetEtatJeu() == 1)
	touches++;
    }

  for(i = 0; i < m_cLen ; i++)
    {

      if(LaCarte->GetObjet(liste2[i])->GetEtatJeu() == 0)
	return false;
    }

  for(i = 0; i < 22 ; i++)
    {
      if(liste[i] != 0)
	{
	  LaCarte->GetObjet(liste[i])->Touche();
	  LaCarte->GetObjet(liste[i])->RemoveTouche();
	  LaCarte->GetObjet(liste[i])->SetEtatJeu(1);
	}
    }

  if(ennemi)
    LaCarte->BateauCouleEnnemi();
  else
    LaCarte->BateauCouleAllie();

  coule = true;
  return true;

}

void Bateau::Write(ostream &out)
{
  int i;
  out << "1 " << id << " " << select << " " << x << " " << y << " "  << z
      << " " << m_cLen << " " << deg << " " << type << " " << touches << " "
      << ennemi << " " << coule << " " << edition << endl;
  for(i = 0 ; i < 22 ; i++)
    out << liste[i] << " ";
  for (i = 0 ; i < 5 ; i++)
    out << liste2[i] << " ";

  out << static_id << endl;
}

void Bateau::Read(istream &in)
{
  int i;
  in >> id >> select >> x >> y >> z >>  m_cLen >> deg >> type
     >> touches >> ennemi >> coule >> edition;
  for(i = 0 ; i < 22 ; i++)
    in >> liste[i];
  for (i = 0 ; i < 5 ; i++)
    in >> liste2[i];
  in >> static_id;

}

