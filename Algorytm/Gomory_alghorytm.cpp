#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n = 2;
int m = 3;
int x = n*m;
int k = 0; // POMOCNICZA ZMIENNA DO LICZNIKA W X1,X2,X3...XN;

int main() {


  float tablica_dane_x[n][m];
  float tablica_pomocnicza[n][m];
  float tablica_dane_c[x];

//TWORZENIE POMOCNICZEJ TABLICY
  for(int i =0; i<x; i++)
  {
    tablica_dane_c[i]=i;
  }

//WPROWADZANIE DANYCH ZADANIA
  for(int i=0; i<m+1;i++) //po wierszach
  {
      for(int j=0;j<n+1;j++) //po kolumnach
      {
        cout << "Podaj x " << i << j << '\n';
        cin >> tablica_dane_x[i][j];
      }
  }

//WYSWIETLENIE PIERWSZEJ TABLICY SIMPLEX
cout << "  " << "  ";
for(k=0;k<n; k++)
{
  std::cout << "  x" << tablica_dane_c[k+1];
}
cout << '\n' << "x0";
    for(int j=0;j<m+1;j++) //po kolumnach
    {
      for(int i=0; i<n+1;i++) //po wierszach
      {
      cout << "  " << tablica_dane_x[j][i];
    }
    if(k<x-1)
    {
      cout << '\n';
    k++;
    cout << "x" << tablica_dane_c[k];
    }
  }
cout << '\n';
// KROK II ALGORYTMU KRYTERIUM DOPUSZCZALNOSCI

for(int i =1; i<m+1; i++)
{
    if (tablica_dane_x[i][1]<0) {
      if (tablica_dane_x[i][0]*tablica_dane_x[i][1]>0) {
        int m = i; // zmienna pomocnicza
        k=tablica_dane_c[m+i];
        tablica_dane_c[m+i]=tablica_dane_c[1];
        tablica_dane_c[1] = k;

        for(int j=0;j<m+1;j++) //po kolumnach
        {
          for(int i=0; i<n+1;i++) //po wierszach
          {
          if(j=1)
          {
            tablica_dane_x[i][j] = -tablica_dane_x[i][j]/tablica_dane_x[i][1];
          }
          else
          if(i=m)
          {
            tablica_dane_x[i][j] = tablica_dane_x[i][j]/tablica_dane_x[i][1];
          }
          else
          if(j!=1 || i!=m)
          {
            tablica_dane_x[i][j] = tablica_dane_x[i][j] - ((tablica_dane_x[m][j]*tablica_dane_x[i][1])/tablica_dane_x[m][1]);
          }
        }
      }
    }
  }
}

//WYSWIETLENIE PIERWSZEJ TABLICY SIMPLEX
cout << "  " << "  ";
for(k=0;k<n; k++)
{
  std::cout << "  x" << tablica_dane_c[k+1];
}
cout << '\n' << "x0";
    for(int j=0;j<m+1;j++) //po kolumnach
    {
      for(int i=0; i<n+1;i++) //po wierszach
      {
      cout << "  " << tablica_dane_x[j][i];
    }
    if(k<x-1)
    {
      cout << '\n';
    k++;
    cout << "x" << tablica_dane_c[k];
    }
  }
  cout << '\n';
}
