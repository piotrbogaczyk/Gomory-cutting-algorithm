#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class zm{
public:
string litera;
int numer;
void zm_new(string litera1, int numer1);
zm & operator=(const zm &zm1);
};

void zm::zm_new(string litera1, int numer1)
{
    litera=litera1;
    numer=numer1;
}

zm& zm::operator=(const zm &zm1)
{
    litera=zm1.litera;
    numer=zm1.numer;
}

vector < vector < float > > tab_sim_1; //1 tablica simpleksowa
vector < vector < float > > tab_sim; //tablica simpleksowa kolejna po obliczeniach
vector < vector < float > > tab_sim_pom; //tablica simpleksowa kolejna po obliczeniach
vector < zm > tab_x; //tablica okreslajaca zmienne na osi x
vector < zm > tab_y; //tablica okreslajaca zmienne na osi y

int n=2; //ilosc zmiennych
int m=3; //ilosc ograniczen
int ogr_dod=0;
float blad_dopuszczalny=0.0001;

int zaokrag()
{
            //ZAOKRAGLANIE DO LICZB CALKTITOLICZBOWYCH BIORAC POD UWAGE PRZYJETY BLAD
float ulam_cz;
float cal_cz;



            for(int i=0;i<m+1;i++)
            {
                for(int j=0;j<n+1;j++)
                {
                    if(tab_sim[i][j]<0) //mniejsze od zera
                    {
                        //cout<<endl<<"if("<<tab_sim[i][j]<<">"<<((-1)*(blad_dopuszczalny))<<")"<<endl;
                        if(tab_sim[i][j]>((-1)*(blad_dopuszczalny)))
                        {
                            tab_sim[i][j]=0;
                        }
                    }
                    else
                    {
                        if(tab_sim[i][j]<blad_dopuszczalny)
                        {
                            tab_sim[i][j]=0;
                        }
                    }
                }

            }

            for(int i=0;i<m+1;i++)
            {
                for(int j=0;j<n+1;j++)
                {
                    ulam_cz=modf(tab_sim[i][j], &cal_cz);
                    if(ulam_cz<0) //ujemne
                    {
                        if(ulam_cz>((-1)*(blad_dopuszczalny)))
                        {
                            tab_sim[i][j]=floor(tab_sim[i][j]);
                        }
                    }
                    else
                    {
                        if(ulam_cz<blad_dopuszczalny)
                        {
                            tab_sim[i][j]=floor(tab_sim[i][j]);
                        }
                    }
                }
            }

            //WYSWIETLENIE PO ZAOKRAGLANIACH
    cout<<endl<<"TABLICA PO ZAOKRAGLANIACH"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim[i][j]<<"   ";
        }
        cout<<endl;
    }
}


//FUNKCJA DWUFAZOWY SIMPLEKS FAZA 1
int DWU_FAZA_1()
{
    int blad=1;
    float min_pom_s=9999999;
    float min_pom_k=9999999;
    float min_pom_r=9999999;
    int s_x=0;
    int k_y=0;
    int r_x=0;
    int blad1=0;
    int zlicz1=0;

    //KROK1 wyb�r pomocniczej funkcji celu
    for(int i=0;i<m+1;i++)
    {
        if((tab_sim[i][0]<min_pom_s)&&(tab_sim[i][0]<0))
        {
            min_pom_s=tab_sim[i][0];
            s_x=i;
        }
    }

    //KROK 2 (wybor zmiennej wchodzacej do bazy)

    for(int j=1;j<n+1;j++)
    {
        if(tab_sim[s_x][j]>0)
        {
            zlicz1=zlicz1+1;
        }
    }
    if(zlicz1==n)
    {
        blad1=1;
        blad=5;
    }

    if(blad1==0)
    {
    for(int j=1;j<n+1;j++) //ZMIENIONE z j=0 na j=1
    {
        if((tab_sim[s_x][j]<min_pom_k)&&(tab_sim[s_x][j]<0))
        {

            min_pom_k=tab_sim[s_x][j];
            //cout<<endl<<"min_pom_k :"<<min_pom_k<<endl;
            k_y=j;
            blad=0;
        }
    }
    }
    if(blad==0)
    {
        //KROK 3 (wybor zmiennej usuwanej z bazy)
        for(int i=0;i<m+1;i++)
        {
            if(((tab_sim[i][0]/tab_sim[i][k_y])<min_pom_r)&&((tab_sim[i][0]/tab_sim[i][k_y])>0))
            {
                min_pom_r=tab_sim[i][0]/tab_sim[i][k_y];
                r_x=i;
            }
        }

        //KROK 5 ELIMINACJA GAUSSA

        tab_sim_pom=tab_sim;

        for(int x1=0;x1<m+1;x1++)
        {
            for(int y1=0;y1<n+1;y1++)
            {
                if((x1!=r_x)&&(y1!=k_y)) //wszytskie inne niz wiersz i kolumna centralna
                {
                    tab_sim_pom[x1][y1]=tab_sim[x1][y1]-((tab_sim[x1][k_y]*tab_sim[r_x][y1])/(tab_sim[r_x][k_y]));
                }
                else
                {
                    if((x1==r_x)&&(y1==k_y))
                    {
                        tab_sim_pom[x1][y1]=1/tab_sim[x1][y1];
                    }
                    else
                    {
                        if(y1==k_y) //element w kolumnie centralnej
                        {
                            tab_sim_pom[x1][y1]=(-1)*((tab_sim[x1][y1])/(tab_sim[r_x][k_y]));
                        }

                        if(x1==r_x) //element w wierszu centralnym
                        {
                            tab_sim_pom[x1][y1]=(tab_sim[x1][y1])/(tab_sim[r_x][k_y]);
                        }
                    }
                }
            }
        }

    tab_sim=tab_sim_pom;

    //ZAMIANA ZNAKOW
    string litera1;
    int numer1;
    litera1=tab_x[k_y].litera;
    numer1=tab_x[k_y].numer;
    tab_x[k_y].litera=tab_y[r_x].litera;
    tab_x[k_y].numer=tab_y[r_x].numer;
    tab_y[r_x].litera=litera1;
    tab_y[r_x].numer=numer1;

    //WYSWIETLENIE TABLICY SIMPLEKSOWEJ PO METODZIE DWUFAZOWEJ FAZA 1
    cout<<endl<<"METODA DWUFAZOWA FAZA 1"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim[i][j]<<"   ";
        }
        cout<<endl;
    }

    }
    else //BRAK ROZWIAZANIA DOPUSZCZALNEGO, PROBLEM SPRZECZNY
    {
        blad=5;
    }

    return blad;
}


//FUNKCJA DWUFAZOWY SIMPLEKS FAZA 2

int DWU_FAZA_2()
{
    int blad=0;
    float min_pom_x=99999999;
    float min_pom_y=99999999;
    float min_pom_obl;
    int k_y=0;
    int r_x=0;
    zm zm_pom1;

    //KROK 1
    //SPRAWDZENIE DOPUSZCZALNOSCI
    for(int i=0;i<m+1;i++)
    {
        if(tab_sim[i][0]>=0)
        {

        }
        else
        {
            blad=1;
        }
    }

    //KROK 2
    //TEST OPTYMALNOSCI
    for(int j=0;j<n+1;j++)
    {
        if(tab_sim[0][j]>=0)
        {

        }
        else
        {
            blad=2; //koniec aktualne rozwiazanie jest optymalne
        }
    }

    if(blad==2)
    {
        //KROK3 (wybor zmiennej wchodzacej do bazy)
        for(int j=0;j<n+1;j++)
        {
            if((tab_sim[0][j]<min_pom_x)&&(tab_sim[0][j]<0))
            {
                min_pom_x=tab_sim[0][j];
                k_y=j;
            }
        }

        //KROK 4 (wybor zmiennej usuwanej z bazy)

        for(int i=0;i<m+1;i++)
        {

        min_pom_obl=(tab_sim[i][0])/(tab_sim[i][k_y]);

            if((min_pom_obl<min_pom_y)&&(tab_sim[i][k_y]>0))
            {
                min_pom_y=min_pom_obl;
                r_x=i;
            }

        }
        //KROK 5 ELIMINACJA GAUSSA

        tab_sim_pom=tab_sim;

        for(int x1=0;x1<m+1;x1++)
        {
            for(int y1=0;y1<n+1;y1++)
            {
                if((x1!=r_x)&&(y1!=k_y)) //wszytskie inne niz wiersz i kolumna centralna
                {
                    tab_sim_pom[x1][y1]=tab_sim[x1][y1]-((tab_sim[x1][k_y]*tab_sim[r_x][y1])/(tab_sim[r_x][k_y]));
                }
                else
                {
                    if((x1==r_x)&&(y1==k_y))
                    {
                        tab_sim_pom[x1][y1]=1/tab_sim[x1][y1];
                    }
                    else
                    {
                        if(y1==k_y) //element w kolumnie centralnej
                        {
                            tab_sim_pom[x1][y1]=(-1)*((tab_sim[x1][y1])/(tab_sim[r_x][k_y]));
                        }

                        if(x1==r_x) //element w wierszu centralnym
                        {
                            tab_sim_pom[x1][y1]=(tab_sim[x1][y1])/(tab_sim[r_x][k_y]);
                        }
                    }
                }
            }
        }

    tab_sim=tab_sim_pom;

    //ZAMIANA ZNAKOW
    string litera1;
    int numer1;
    litera1=tab_x[k_y].litera;
    numer1=tab_x[k_y].numer;
    tab_x[k_y].litera=tab_y[r_x].litera;
    tab_x[k_y].numer=tab_y[r_x].numer;
    tab_y[r_x].litera=litera1;
    tab_y[r_x].numer=numer1;

    //WYSWIETLENIE TABLICY SIMPLEKSOWEJ PO METODZIE DWUFAZOWEJ FAZA 2
    cout<<endl<<"METODA DWUFAZOWA FAZA 2"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim[i][j]<<"   ";
        }
        cout<<endl;
    }

    }



    return blad; //blad=1 brak dopuszczalnosci, blad=2 to jest aktualne rozwiazanie optymalne
}

//FUNKCJA METODA ODCIEC GOMOREGO

int MET_ODC_GOM()
{
    int blad=0;
    float max_pom_x=-999999;
    float suma1=0;
    int r_x;
    float cal_cz;
    float ulam_cz;

    //SZUKANIE WIERSZA Z KTOREGO ZAPISANE ZOSTANIE ODCIECIE
    for(int i=1;i<m+1;i++) //ZMIENIONE i=0 na i=1
    {
        suma1=0;
        for(int j=1;j<n+1;j++)
        {
            ulam_cz=modf(tab_sim[i][j], &cal_cz);
            //cout<<endl<<"ulam_cz: "<<ulam_cz<<endl;
            suma1=suma1+ulam_cz;
        }
        //cout<<endl<<"SUMA: "<<suma1<<endl;
        ulam_cz=modf(tab_sim[i][0], &cal_cz);
        if(((ulam_cz)/(suma1))>max_pom_x)
        {
            max_pom_x=(ulam_cz)/(suma1);
            r_x=i;
        }
    }

    //DODANIE WIERSZA Z ODCIECIEM
    tab_sim.push_back(vector < float >());
    m=m+1;
    ogr_dod=ogr_dod+1;
    for(int i=0;i<n+1;i++) //uzupelnienie kolumnami stworzonego wiersza na odciecie
    {

        tab_sim[m].push_back(0);

    }

    //UZUPELNIENIE NOWYMI DANYMI TABLICY SIMPLEKS

    for(int j=0;j<n+1;j++)
    {
        if(j==0) //uzupelnienie wyrazu wolnego
        {
            ulam_cz=modf(tab_sim[r_x][0], &cal_cz);
            //cout<<endl<<"glowna ulam_cz: "<<ulam_cz<<endl;
            tab_sim[m][j]=(-1)*(tab_sim[r_x][0]-cal_cz);
            //cout<<"tab_sim[m][j]: "<<tab_sim[m][j]<<endl;
        }
        else
        {
            ulam_cz=modf(tab_sim[r_x][j], &cal_cz);
            //cout<<endl<<"kolejne ulam_cz: "<<ulam_cz<<endl;
            tab_sim[m][j]=(-1)*(tab_sim[r_x][j]-cal_cz);
            //cout<<"tab_sim[m][j]: "<<tab_sim[m][j]<<endl;
        }
    }

    //DODANIE ZNAKU
    zm test1;
    tab_y.push_back(test1);
    tab_y[m].litera='s';
    tab_y[m].numer=ogr_dod;


    //WYSWIETLENIE TABLICY SIMPLEKSOWEJ PO METODZIE GOMOREGO
    cout<<endl<<"METODA ODCIEC GOMOREGO"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim[i][j]<<"   ";
        }
        cout<<endl;
    }


    return blad;
}

int dual_sim()
{
    int blad=0;
    int blad_1=1;
    int blad_2=0;
    float min_pom_x=999999999;
    float max_pom_y=-999999999;
    int r_x=0;
    int k_y=0;

    //KROK 1
    for(int j=0;j<n+1;j++)
    {
        if(tab_sim[0][j]<0)
        {
            blad_1=0;
        }
    }

    //KROK 2
    if(blad_1==1)
    {
        for(int i=1;i<m+1;i++)
        {
            if(tab_sim[i][0]>=0)
            {

            }
            else
            {
            blad_2=1;
            }
        }
    }

    //KROK 3
    if(blad_2==1)
    {

        for(int i=1;i<m+1;i++)
        {
            if((tab_sim[i][0]<min_pom_x)&&(tab_sim[i][0]<0))
            {
                min_pom_x=tab_sim[i][0];
                r_x=i;
            }
        }

        //KROK 4

        for(int j=1;j<n+1;j++)
        {
            if(((tab_sim[0][j]/tab_sim[r_x][j])>max_pom_y)&&(tab_sim[r_x][j]<0))
            {
                max_pom_y=tab_sim[0][j]/tab_sim[r_x][j];
                k_y=j;
            }
        }
        cout<<endl<<"DUAL : "<<r_x<<" : "<<k_y<<endl;

        //KROK 5 ELIMINACJA GAUSSA

        tab_sim_pom=tab_sim;

        for(int x1=0;x1<m+1;x1++)
        {
            for(int y1=0;y1<n+1;y1++)
            {
                if((x1!=r_x)&&(y1!=k_y)) //wszytskie inne niz wiersz i kolumna centralna
                {
                    tab_sim_pom[x1][y1]=tab_sim[x1][y1]-((tab_sim[x1][k_y]*tab_sim[r_x][y1])/(tab_sim[r_x][k_y]));
                }
                else
                {
                    if((x1==r_x)&&(y1==k_y))
                    {
                        tab_sim_pom[x1][y1]=1/tab_sim[x1][y1];
                    }
                    else
                    {
                        if(y1==k_y) //element w kolumnie centralnej
                        {
                            tab_sim_pom[x1][y1]=(-1)*((tab_sim[x1][y1])/(tab_sim[r_x][k_y]));
                        }

                        if(x1==r_x) //element w wierszu centralnym
                        {
                            tab_sim_pom[x1][y1]=(tab_sim[x1][y1])/(tab_sim[r_x][k_y]);
                        }
                    }
                }
            }
        }

    tab_sim=tab_sim_pom;

    //ZAMIANA ZNAKOW
    string litera1;
    int numer1;
    litera1=tab_x[k_y].litera;
    numer1=tab_x[k_y].numer;
    tab_x[k_y].litera=tab_y[r_x].litera;
    tab_x[k_y].numer=tab_y[r_x].numer;
    tab_y[r_x].litera=litera1;
    tab_y[r_x].numer=numer1;

    //WYSWIETLENIE TABLICY SIMPLEKSOWEJ PO METODZIE DUALNEJ SIMPLEKS
    cout<<endl<<"METODA DUALNA SIMPLEKS"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim[i][j]<<"   ";
        }
        cout<<endl;
    }

    }

    return blad;
}

int main()
{

    int n_wpr=2; //ilosc zmiennych wprowadzonych
    int m_wpr=3; //ilosc ograniczen wprowadzonych

    n=n_wpr;
    m=m_wpr;

    //float ww_fc=0, c1_1=-2,  c2_1=-1;
    //float ww_1=5,  x1_1=1,  x2_1=1;
    //float ww_2=0,  x1_2=-1,  x2_2=1;
    //float ww_3=21,  x1_3=6, x2_3=2;

    float ww_fc=0, c1_1=-1,  c2_1=-6;
    float ww_1=-2,  x1_1=-2,  x2_1=-1;
    float ww_2=3,  x1_2=-1,  x2_2=1;
    float ww_3=6,  x1_3=1, x2_3=1;

    //float ww_fc=0, c1_1=1,  c2_1=1;
    //float ww_1=-8,  x1_1=-1,  x2_1=-2;
    //float ww_2=-6,  x1_2=-2,  x2_2=-1;
    //float ww_3=-5,  x1_3=-1,  x2_3=-1;

    float tab_dane[4][3];

    tab_dane[0][0]=ww_fc, tab_dane[0][1]=c1_1, tab_dane[0][2]=c2_1;
    tab_dane[1][0]=ww_1, tab_dane[1][1]=x1_1, tab_dane[1][2]=x2_1;
    tab_dane[2][0]=ww_2, tab_dane[2][1]=x1_2, tab_dane[2][2]=x2_2;
    tab_dane[3][0]=ww_3, tab_dane[3][1]=x1_3, tab_dane[3][2]=x2_3;

    //TWORZENIE PIERWSZEJ TABLICY SIMPLEKSOWEJ

    for(int i=0; i<m+1;i++) //tworzenie pierwszej tablicy simpleks
    {
        tab_sim_1.push_back(vector < float > ()); //tworzenie wierszy
        for(int j=0;j<n+1;j++)//tworzenie kolumn
        {
            tab_sim_1[i].push_back(1);
        }
    }

    zm test;
    for(int i=0;i<n+1;i++)
    {
        tab_x.push_back(test);
        if(i==0)
        {
            tab_x[i].litera=' ';
            tab_x[i].numer=0;

        }
        else
        {
            tab_x[i].litera='x';
            tab_x[i].numer=i;
        }
    }

    for(int j=0;j<m+1;j++)
    {
        tab_y.push_back(test);
        if(j==0)
        {
            tab_y[j].litera='x';
            tab_y[j].numer=0;
        }
        else
        {
            tab_y[j].litera='x';
            tab_y[j].numer=j+n;
        }
    }
    //UZUPELNIANIE DANYMI PIERWSZEJ TABLICY SIMPLEKSOWEJ

    for(int i=0; i<m+1;i++) //po wierszach
    {
        for(int j=0;j<n+1;j++) //po kolumnach
        {
            tab_sim_1[i][j]=tab_dane[i][j];
        }
    }

    //WYSWIETLENIE PIERWSZEJ TABLICY SIMPLEKSOWEJ
    cout<<endl<<"PIERWSZA TABLICA SIMPLEKSOWA"<<endl;
    for(int j=0;j<n+1;j++)
    {
        if(j==0)
        {
            cout<<"         ";
        }
        else
        {
            cout<<tab_x[j].litera<<tab_x[j].numer<<"   ";
        }
    }
    cout<<endl;

    for(int i=0; i<m+1;i++) //po wierszach
    {
        cout<<" "<<tab_y[i].litera<<tab_y[i].numer<<"   ";
        for(int j=0;j<n+1;j++)//po kolumnach
        {
            cout<<tab_sim_1[i][j]<<"   ";
        }
        cout<<endl;
    }


//ROZWIAZYWANIE

tab_sim=tab_sim_1;

int blad_alg_1=0;
int blad_alg_2=0;
int blad_alg_3=0;
int blad_alg_4=0;
int dop=0; //jesli 0 to mniejszosciowe sa tylko, jesli 1 to wiekszosciowe wystepuja
int wyk1=0;
int wyk2=0;
int wyk3=0;
float ulam_cz=0;
float cal_cz=0;
int koniec=0;

    do
    {
    koniec=0;
        do
        {
            wyk1=0;
            //SPRAWDZENIE DOPUSZCZALNOSCI
            for(int i=0;i<m+1;i++)
            {
                if(tab_sim[i][0]<0) //[wiersze][kolumny]
                {
                    wyk1=1;
                }
            }

            if(wyk1==1)
            {
            blad_alg_1=DWU_FAZA_1();
            cout<<endl<<"TUTAJ 1"<<endl;
            zaokrag();

                if(blad_alg_1==5)
                {
                    cout<<"ROZWIAZANIE SPRZECZNE";
                    koniec=koniec-1;
                    wyk1=0;
                }
                else
                {
                    koniec=koniec+1;
                }
            }
        }while(wyk1==1);

        if(blad_alg_1!=5)
        {
        do
        {
            wyk2=0;
            for(int j=0;j<n+1;j++)
            {
                if(tab_sim[0][j]<0) //[wiersze][kolumny]
                {
                    wyk2=1;
                }
            }

            if(wyk2==1)
            {
                blad_alg_1=DWU_FAZA_2();
                koniec=koniec+1;
                cout<<endl<<"TUTAJ 2"<<endl;
                zaokrag();
            }

        }while(wyk2==1);

            //METODA ODCIEC (GOMOREGO)
            wyk3=0;
            for(int i=0;i<m+1;i++)
            {
                ulam_cz=modf(tab_sim[i][0], &cal_cz);

                if(ulam_cz>blad_dopuszczalny) //[wiersze][kolumny]
                {
                    wyk3=1;
                }
            }

            if(wyk3==1)
            {
                blad_alg_3=MET_ODC_GOM();
                koniec=koniec+1;
                cout<<endl<<"TUTAJ 3"<<endl;
                zaokrag();

                if(blad_alg_3==5)
                {
                    koniec=koniec-1;
                }
            }
        }
        else
        {
            koniec=0;
        }
            //blad_alg_3=MET_ODC_GOM();

    //if(blad_alg_1!=0)
    //    cout<<endl<<"BLAD FAZA 1 !!!!! nr= "<<blad_alg_1<<" BRAK ROZWIAZANIA PROBLEM SPRZECZNY"<<endl;

    //if(blad_alg_2!=0)
    //    cout<<endl<<"BLAD FAZA 2 !!!!! nr= "<< blad_alg_2<<endl;

    //if(blad_alg_3!=0)
    //    cout<<endl<<"BLAD GOMORY !!!!! nr= "<< blad_alg_3<<endl;

    //if(blad_alg_4!=0)
    //    cout<<endl<<"BLAD DUALNY SIMPLEKS !!!!! nr= "<< blad_alg_4<<endl;

    }while(koniec!=0);


    //blad_alg_4=dual_sim();
    //blad_alg_2=DWU_FAZA_1();
    //blad_alg_4=dual_sim();
    //blad_alg_4=dual_sim();



/*
blad_alg_1=DWU_FAZA_2();
blad_alg_2=DWU_FAZA_2();
//blad_alg_2=DWU_FAZA_1();
//blad_alg_2=DWU_FAZA_1();
//blad_alg_2=DWU_FAZA_1();
blad_alg_3=MET_ODC_GOM();
blad_alg_2=DWU_FAZA_1();
blad_alg_3=MET_ODC_GOM();
blad_alg_2=DWU_FAZA_1();
*/
}
