#include "main.h"
#include "funkcje.h"

size_t sprawdz_baze(ifstream &baza_pytan){
    if( !baza_pytan.good() )  {cout << "bazaZla\n"; return -1;}
    baza_pytan.clear();
    baza_pytan.seekg(0, ios::beg);
    baza_pytan.unsetf(std::ios_base::skipws);
    size_t line_count = count(istream_iterator<char>(baza_pytan),istream_iterator<char>(), '\n');
    baza_pytan.clear();
    baza_pytan.seekg(0,ios::beg);
    return line_count+1;
}

void shuffle(int *arr, size_t n)
{
    if (n > 1)
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

void shuffleS(string *arr, int n, int seed)
{
    if (n > 1)
    {
        int i;
        srand(time(NULL)+seed);
        for (i = 0; i < n - 1; i++)
        {
          int j = i + rand() / (RAND_MAX / (n - i) + 1);
          string t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

void waga_pytan(ifstream &baza, int punkty[], int rozmiar){
    char kolejna_linia[256];
    int tmp,j = 0;
    for (int i = 0; i<rozmiar; i++){
        baza.getline(kolejna_linia, 256);
        if (i%3 == 0) {
            string s = kolejna_linia;
            string delimiter = "|";
            size_t pos = 0;
            string token;
                pos = s.find(delimiter);
                token = s.substr(0, pos);
                //cout << token << endl;

                sscanf(token.c_str(), "%d", &tmp);
                //cout << tmp << endl;
                punkty[j] = tmp;
                j++;
        }
    }
    baza.clear();
    baza.seekg(0,ios::beg);
    cout << "koniec wag pytań";
}

int wybierz_pytania(int tablica_wierszy[], int punkty[], size_t pkt, size_t baz)
{

int liczba_pytan = 0;
int * arr = new int[baz/3];

for (int i=0; i<baz/3; i++){
    arr[i] = i;
}

(int)pkt;
shuffle(arr, baz/3);

//tutaj po wybraniu każdego pytania należy je sprawdzić za ile jest punktów

//D
/*for (int i=0; i<baz/3; i++){
    //cout << arr[i] << " tab" << endl;
    //cout << punkty[arr[i]] << endl;
}*/
//endD

        for(int i = 0; i < baz/3; i++ ){
        //printf("%d ",  arr[i]+1);

        if (pkt >= punkty[arr[i]]){
        //cout << "waga = " << punkty[arr[i]] << endl;
            pkt = pkt - punkty[arr[i]];
            tablica_wierszy[3*i] = arr[i]*3 + 1;
            tablica_wierszy[1+3*i] = arr[i]*3 + 2;
            tablica_wierszy[2+3*i] = arr[i]*3 + 3;
            //cout << "pkt = " << pkt <<endl;
            liczba_pytan++;

            if (pkt == 0) {
                cout << "pktZero"<<endl;
                sort(tablica_wierszy, tablica_wierszy+3*liczba_pytan);

                for (int j=0; j<baz; j++){
                    cout << tablica_wierszy[j] << endl;
                }

                cout<< "Wybranych pytan: " << liczba_pytan << endl;
                return liczba_pytan;
            }
        }
    }
}

string* pobierz_pytania(ifstream &baza_pytan, int liczba_pytan, int wybrane_wiersze[],int wiersze_tmp[],string pobraneWiersze[], size_t rozm_bazy, int liczba_odp)
{
     for (int j=0; j<3*liczba_pytan; j++){
         wybrane_wiersze[j] = wiersze_tmp[j];
     }
    //D
    /*for (int i = 0; i <liczba_pytan*3; i++){
     cout << wybrane_wiersze[i] << endl;
    }*/
    //endD
     int x = 0, y = 0;
     string kolejny_wiersz;
     for (int i = 0; i<rozm_bazy; i++){
             getline(baza_pytan,kolejny_wiersz);
             if (i == wybrane_wiersze[x]-1) {
             pobraneWiersze[y] =  kolejny_wiersz;
             x++; y++;
             }
     }

     int n;
     string punkt;
     string dobra;
     string pytanie;
     string * odp = new string [liczba_odp];
     string * Output = new string[2*liczba_pytan*(liczba_odp+2)+1];

     for(int i = 0; i < liczba_pytan; i++){
             //D
             //cout << pobraneWiersze[i*3+2]<<endl;

             string delimiter = "|";
             //if (i == 0)
             string p = pobraneWiersze[i*3];
             size_t posp = 0;
             string tokenp;


             while ((posp = p.find(delimiter)) != std::string::npos)
             {
                 tokenp = p.substr(0, posp);
                 //cout << tokenp << endl;
                 punkt = tokenp + " pkt";
                 p.erase(0, posp + delimiter.length());
                 pytanie = p;

             }

             dobra = pobraneWiersze[i*3+1];
             cout <<"dobra: " << dobra << "dla i: "<< i << endl;
             cout <<"waga: " << punkt << endl;
             cout <<"pytanie: " << pytanie << endl;

             string s = pobraneWiersze[i*3+2];
             size_t pos = 0;
             string token;
                 n = 0;
                 while ((pos = s.find(delimiter)) != std::string::npos) {
                     //token = s.substr(0, pos);
                     //cout << token << endl;
                     n++;
                     s.erase(0, pos + delimiter.length());
                 }
             string * bledne = new string [n];

             s = pobraneWiersze[i*3+2];
             pos = 0; n = 0;
             while ((pos = s.find(delimiter)) != std::string::npos) {
                 token = s.substr(0, pos);
                 cout << token <<endl;
                 bledne[n] = token;
                 n++;
                 s.erase(0, pos + delimiter.length());
             }
             shuffleS(bledne, n, 0);


             for (int q =0; q<liczba_odp-1; q++){

                 odp[q] = bledne[q];
             }

             //na ostatniej pozycji dodana zostaje poprawna odpowiedz + mieszanie
             odp[liczba_odp-1] = dobra;
             shuffleS(odp, liczba_odp, i);
             //wybór punktow i pytania
             Output[7*i] = punkt;
             Output[7*i+1] = pytanie;
             //przejsce przez odpowiedzi
             for(int w=0; w < liczba_odp; w++ ){
                 Output[7*i+w+2] = odp[w];
                 //cout << odp[w] << endl;
             }
             Output[7*i+liczba_odp+3] = ' ';
             cout << "koniecPytania" << endl;
             }
     return  Output;
}
