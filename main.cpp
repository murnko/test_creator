#include <QCoreApplication>
#include "main.h"

/* Format bazy pytań
  1|Pytanie
  Odpowiedz_dobra
  Odpowiedz_zla

 *
 *
 *
 */

using namespace std;
int liczba_pytan;
const int liczba_punktow = 3;
const int liczba_odp = 4;

ifstream baza_pytan;
string pobraneWiersze[1024];
int wybrane_pytania[10];
int punktacja[100]; //każdy wiersz odpowiada tabeli odpowiada za kolejne pyatnie


int main(){

    baza_pytan.open("/media/murnko/store/projekty/studio1/Baza.txt");
    size_t rozm_bazy = sprawdz_baze(baza_pytan); //DONE
    int * wiersze_tmp = new int[rozm_bazy];//IN

    waga_pytan(baza_pytan,punktacja,rozm_bazy);//DONE

    liczba_pytan = wybierz_pytania(wiersze_tmp, punktacja, liczba_punktow,rozm_bazy);
    int * wybrane_wiersze = new int[3*liczba_pytan];

    string * Output = pobierz_pytania(baza_pytan,liczba_pytan,wybrane_wiersze,wiersze_tmp,
                                pobraneWiersze,rozm_bazy, liczba_odp);

//Roboczy print wyniku posredniego
    cout<< "OUTPUT" << endl;
    for (int z =0; z < 2*liczba_pytan*(liczba_odp+2); z++){
        cout << Output[z]<< endl;
    }
    cout << "\n"; return -1;
            baza_pytan.close();
            getchar();


    return 0;
    }
/*************************
FUNKCJE roboczo


*******************************/



//Parsing zlych odpowiedzi
/*
std::string s = "scott>=tiger>=mushroom";
std::string delimiter = ">=";

size_t pos = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
}
std::cout << s << std::endl;
*/
