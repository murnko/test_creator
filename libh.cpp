#include "main.h"
#include "funkcje.h"
#include "libh.h"

#ifdef HPDF_DLL
void __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    jmp_buf env;
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

//void
//PrintText(HPDF_Page page)
//{
//    char buf[512];
//    HPDF_Point pos = HPDF_Page_GetCurrentTextPos (page);

//    no++;
//    snprintf (buf, 512, ".[%d]%0.2f %0.2f", no, pos.x, pos.y);
//    HPDF_Page_ShowText(page, buf);
//}
typedef struct {
    string s;
    int i;
} para;
const static para odpowiedniki_polskich[] = {


    { "Ć", 198 },
    { "Ę", 202 },
    { "Ł", 163 },
    { "Ń", 209 },
    { "Ó", 211 },
    { "Ś", 166 },
    { "Ź", 172 },
    { "Ż", 175 },
    { "ą", 177 },
    { "ć", 230 },
    { "ę", 234 },
    { "ó", 243 },
    { "ł", 179 },
    { "ń", 241 },
    { "ś", 182 },
    { "ź", 188 },
    { "ż", 191 }
};
const int LICZBA_POLSKICH_ZNAKOW = sizeof( odpowiedniki_polskich ) / sizeof( para );

char * zamienZnaki( string wejsciowy)
{
    char * wyjsciowy = strdup(wejsciowy.c_str());
    for(int i = 0; i < LICZBA_POLSKICH_ZNAKOW; ++i ){
        string target = odpowiedniki_polskich[ i ].s;
        int idx = 0, loop = 0 ;
        int tablica_w[1024];

        while (idx != -1){
            idx = wejsciowy.find(target,idx+1);
            tablica_w[loop] = idx;
            loop++;
        }
        for (int z =0;z <99;z++){

            if (tablica_w[z]>0){
                wyjsciowy[tablica_w[z]] =( char ) odpowiedniki_polskich[ i ].i;
                if (odpowiedniki_polskich[ i ].s == "ó")
                    memmove(wyjsciowy[tablica_w[z]+1], wyjsciowy[tablica_w[z] + 2], strlen(wyjsciowy) - tablica_w[z]+1);
        }
        }
    }
    return wyjsciowy;

}

void zamienZnakWCiagu( char * wejsciowy, unsigned char znak_obecny, unsigned char znak_docelowy ) {
    char * pch = strchr( wejsciowy, znak_obecny );
    unsigned pozycja = 0;

    while( pch != NULL ) {
        pozycja = pch - wejsciowy;
        cout << "Debug: "<< pozycja;//(int)wejsciowy[pozycja];
        wejsciowy[ pozycja ] =( char ) znak_docelowy;
        pch = strchr( pch + 1, znak_obecny );
    }
}

void usunZNapisu( char * wejsciowy, unsigned pozycja ) {
    unsigned i;
    for( i = pozycja; i < strlen( wejsciowy ); ++i )
         wejsciowy[ i ] = wejsciowy[ i + 1 ];

    wejsciowy[ i ] = '\0';
}

//char * dodajOgonki( char * wejsciowy ) {
////    unsigned char * tymczasowy = malloc( sizeof( char ) * strlen( wejsciowy ) + 3 );
////    const unsigned char * cos = "a";
//    char * wyjsciowy = (char*)malloc( sizeof( char ) * strlen( wejsciowy ) + 3 );
//    unsigned i = 0;

//    wyjsciowy[ 0 ] = 'a';
//    wyjsciowy[ 1 ] = '\0';
//    strcat( wyjsciowy, wejsciowy ); // konkatenuje napisy

//    for( i; i < LICZBA_POLSKICH_ZNAKOW; ++i )
//         zamienZnakWCiagu( wyjsciowy, odpowiedniki_polskich[ i ].c, odpowiedniki_polskich[ i ].i );

//    for( i = 0; i < strlen( wejsciowy ); ++i ) // usuwam pierwsza litere z ciagu, ktora dodalem na poczatku
//         wyjsciowy[ i ] = wyjsciowy[ i + 1 ];

//    wyjsciowy[ i + 2 ] = '\0';

////    for( i = 0; i < strlen( wyjsciowy ); ++i )
////    if( !isalnum( wyjsciowy[ i ] ))
////        if (!(wyjsciowy[i] != " "))
////         usunZNapisu( wyjsciowy, i );

//    return wyjsciowy;
//}
