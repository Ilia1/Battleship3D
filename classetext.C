#include "headers.h"

ClasseText::ClasseText()
{
}

ClasseText::~ClasseText()
{
}

void ClasseText::addText(const char* letexte, int modee)
{
  if(ListTextes.size() == 3)
    {
      ListTextes.pop_back();
      TimeStart.pop_back();
      ListModes.pop_back();
    }
  ListTextes.push_front(letexte);
  TimeStart.push_front(0);
  ListModes.push_front(modee);
}

void ClasseText::afficher(Graphique *graph)
{
  glGetIntegerv(GL_RENDER_MODE,&mode);
  if(mode != GL_SELECT)
    {
      for(unsigned int i = 0; i < ListTextes.size(); i++)
	{
	  float alpha = 1.0f - (float)(TimeStart[i]/300.0f);
	  glEnable(GL_BLEND);
	  if(ListModes[i] == 1)
	    {
#ifndef NO_TEXT
	      glColor4f(0.0f, 0.0f, 0.0f, alpha);
	      graph->renderText((graph->obtenirTransf()->GetWidth() / 2.0f) - 250.0f, graph->obtenirTransf()->GetHeight()/2.0f, ListTextes[i], QFont("flexure", 32));
#endif
	      TimeStart[i]++;
	      if(alpha == 0) TimeStart[i] = 0;
	      break;
	    } else {
#ifndef NO_TEXT
	      glColor4f(0.0f, 0.0f, 0.0f, alpha);
	      graph->renderText(10, 80 - i*15, ListTextes[i], QFont("flexure", 12));
#endif
	      TimeStart[i]++;
	    }
	  glDisable(GL_BLEND);
	}
    }

  if ( TimeStart[0] < 2)
    {
      //if (!modee)
      graph->GetStatus()->showMessage(ListTextes[0], 2500);
      //	else 
      //		graph->GetStatus()->message(ListTextes[0]);
    }
}
