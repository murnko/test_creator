#ifndef LIBH
#define LIBH
#include "main.h"


#ifdef HPDF_DLL
void __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data);

void PrintText(HPDF_Page page);

void zamienZnakWCiagu(char * wejsciowy, unsigned char znak_obecny, unsigned char znak_docelowy );
void usunZNapisu(char * wejsciowy, unsigned pozycja );
char * dodajOgonki( char* wejsciowy );


#endif // LIBH

