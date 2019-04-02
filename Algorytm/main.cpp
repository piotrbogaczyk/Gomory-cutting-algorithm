#include <iostream>
#include <vector>
#include <cmath>

#include "simplex.hpp"

using namespace std;

int main() {


  float ww_fc=0, c1_1=-1,  c2_1=-6;
  float ww_1=-2,  x1_1=-2,  x2_1=-1;
  float ww_2=3,  x1_2=-1,  x2_2=1;
  float ww_3=6,  x1_3=1, x2_3=1;

  float tab_dane[4][3];

  tab_dane[0][0]=ww_fc, tab_dane[0][1]=c1_1, tab_dane[0][2]=c2_1;
  tab_dane[1][0]=ww_1, tab_dane[1][1]=x1_1, tab_dane[1][2]=x2_1;
  tab_dane[2][0]=ww_2, tab_dane[2][1]=x1_2, tab_dane[2][2]=x2_2;
  tab_dane[3][0]=ww_3, tab_dane[3][1]=x1_3, tab_dane[3][2]=x2_3;

tworzenie_tablicy_simlex();
zaokraglenie_wynikow_w_tablicy();
metoda_odciec_gomorego();



}
