#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>

class simplex{
private:
  int kolumny;
  int wiersze;

public:

  void tworzenie_tablicy_simlex();
  void kryterium_dopuszczalnosci();
  void kryterium_optymalnosci();
};

#endif
