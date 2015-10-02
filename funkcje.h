#ifndef FUNKCJE
#define FUNKCJE
#include "main.h"


size_t sprawdz_baze(ifstream &baza_pytan);
void shuffle(int *arr, size_t n);
void shuffleS(string *arr, int n, int seed);
void waga_pytan(ifstream &baza, int punkty[], int rozmiar);
int wybierz_pytania(int tablica_wierszy[], int punkty[], size_t pkt, size_t baz);
string* pobierz_pytania(ifstream &baza_pytan, int liczba_pytan, int wybrane_wiersze[],
                        int wiersze_tmp[], string pobraneWiersze[], size_t rozm_bazy,
                        int liczba_odp, int *klucz_odp);

#endif // FUNKCJE

