#ifndef _HEADER_CLASSETEXT_H_
#define _HEADER_CLASSETEXT_H_

#include "headers.h"


class ClasseText
{
 public:
  ClasseText();
  ~ClasseText();
  void addText(const char *, int);
  void afficher(Graphique *);
  
 private:
  deque<const char *> ListTextes;
  deque<int> TimeStart;
  deque<int> ListModes;
  int mode;
};

#endif
