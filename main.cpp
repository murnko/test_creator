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
int liczba_pytan;//decyduje algorytm, nie ustawiac samemu w tej wersji
//ARGUMENTY
const int liczba_punktow = 20;
const int liczba_odp = 4;
const int LICZBA_ZESTAWOW = 15;

ifstream baza_pytan;

jmp_buf env;

int main(int argc, char **argv)
{
    HPDF_Doc  pdf;
    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }
    char fname[256];
    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");
    HPDF_Page page;
    HPDF_Font font;
    const char *fontname;
    HPDF_REAL page_height, page_width, linijka;
    HPDF_Point position;
    HPDF_STATUS stat;
    stat = HPDF_UseUTFEncodings(pdf);
    cout << stat << endl;
    fontname = HPDF_LoadTTFontFromFile(pdf,"/media/store/GIT/test_creator/Lato-Regular.ttf", HPDF_TRUE);
    font = HPDF_GetFont(pdf, fontname, "UTF-8");
    const char * utf = "UTF-8";
    HPDF_SetCurrentEncoder(pdf,utf);
    int ** dobre_odpowiedzi = new int*[LICZBA_ZESTAWOW];
    int ** punkty_odpowiedzi = new int*[LICZBA_ZESTAWOW];
    int * odp_pyt = new int[LICZBA_ZESTAWOW];
    baza_pytan.open("/media/store/GIT/test_creator/Baza.txt");
    size_t rozm_bazy = sprawdz_baze(baza_pytan);
    int punktacja[100]; //każdy wiersz odpowiada tabeli odpowiada za kolejne pyatnie
    waga_pytan(baza_pytan,punktacja,rozm_bazy);
//POCZATEK PETLI DLA JEDNEGO TESTU
for (int t=0; t <LICZBA_ZESTAWOW; t++)
{
    string pobraneWiersze[1024];


    int * wiersze_tmp = new int[rozm_bazy];
    liczba_pytan = wybierz_pytania(wiersze_tmp, punktacja, liczba_punktow,rozm_bazy);
    dobre_odpowiedzi[t] = new int[liczba_pytan];
    punkty_odpowiedzi[t] = new int[liczba_pytan];
    odp_pyt[t] = liczba_pytan;
    int * wybrane_wiersze = new int[3*liczba_pytan];

    string * Output = pobierz_pytania(baza_pytan,liczba_pytan,wybrane_wiersze,wiersze_tmp,
                                pobraneWiersze,rozm_bazy,liczba_odp,
                                dobre_odpowiedzi[t],punkty_odpowiedzi[t]);


    char* libHaruIN[20];
    string linetmp;
    linetmp.append("");
    int n = 0;
    linetmp.append("1. ");
    for (int i=0; i < 7*liczba_pytan+1; i++){
        if (i != 0){
        if (!(i%7)){ //za każdym razem gdy pytanie i odpowiedzi zostaną skomponowane w jeden rekord
            libHaruIN[n] = strdup(linetmp.c_str());
            n++;
            linetmp = "";
            linetmp.append(to_string(n+1));
            linetmp.append(". ");
        }
        }
        linetmp.append(Output[i]);
        linetmp.append(" ");
    }


//LIBHARU

    page = HPDF_AddPage (pdf);
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    page_height = HPDF_Page_GetHeight(page);
    page_width = HPDF_Page_GetWidth(page);
    HPDF_Page_SetTextLeading (page, 20);
    HPDF_Page_SetFontAndSize (page, font, 12);

//PYTANIA
HPDF_Page_BeginText (page);
    linijka = page_height-12;
    for (int i =0; i<liczba_pytan;i++){
        HPDF_Page_TextRect (page, 10,linijka , page_width-10, 0,
                    libHaruIN[i], HPDF_TALIGN_JUSTIFY, NULL);
        position = HPDF_Page_GetCurrentTextPos(page);
        linijka = position.y - 12;
    }
HPDF_Page_EndText (page);

//KRATKI ODPOWIEDZI
//numery pytań
HPDF_Page_BeginText (page);

string numer;
    char numer_pytania[100];
    for (int i =0;i<liczba_pytan;i++ ){
        numer = to_string(i+1);
        //numer_pytania = strdup(numer.c_str());
        sprintf(numer_pytania, "%d", i+1);
        cout << numer_pytania << endl;
        //HPDF_Page_TextOut(page, 29+20*i,17+20*liczba_odp, numer_pytania 22+20*i+20,30+20*liczba_odp+20);
        HPDF_Page_TextRect (page, 32+20*i,30+20*liczba_odp , 50+20*i,50+20*liczba_odp,
                    numer_pytania, HPDF_TALIGN_CENTER, NULL);
    }

    //litery odpowiedzi
    string literal;
    char *odpowiedz;

    int litera = 64;
    for(int i =0; i<liczba_odp; i++){
        litera++;
        literal = (char)litera;
        odpowiedz = strdup(literal.c_str());
        HPDF_Page_TextOut(page, 12,20*liczba_odp-20*i-3,odpowiedz);
    }
    //numer zestawu
    char numer_zestawu[100];
    sprintf(numer_zestawu, "%d", t);
     HPDF_Page_TextOut(page, 10,20*liczba_odp+20,numer_zestawu);

HPDF_Page_EndText (page);

    //pola odpowiedzi
    //ramka odpowiedzi
    HPDF_Page_Rectangle(page, 8,12,page_width-15,20*(liczba_odp+1));

    //pionowe linie
    for (int i =0; i < liczba_pytan; i++){
    HPDF_Page_Rectangle(page, 32+20*i,12,20,20*(liczba_odp+1));
    }

    //poziome linie
    HPDF_Page_MoveTo(page,8,32);
    for (int i =0; i < liczba_odp; i++){
        HPDF_Page_LineTo(page,page_width-7,32+20*i);
        HPDF_Page_MoveTo(page,8,52+20*i);
    }
    //kratki
    for(int h =0; h<liczba_odp; h++){
        for(int v = 0; v <liczba_pytan;v++){
        HPDF_Page_Rectangle(page, 38+20*v,18+20*h,8,8);
        }
    }

HPDF_Page_Stroke (page);

}
 //KONIEC PĘTLI DLA JEDNEGO TESTU
ofstream myfile;
  myfile.open ("/media/store/GIT/test_creator/odpowiedzi.txt");

for (int a=0;a<LICZBA_ZESTAWOW;a++){
    cout << endl;

    for (int b=0;b<odp_pyt[a];b++){
        myfile << dobre_odpowiedzi[a][b];
        cout << dobre_odpowiedzi[a][b];
    }
    cout << endl;
    myfile << "\n";
    for (int b=0;b<odp_pyt[a];b++){
        myfile << punkty_odpowiedzi[a][b];
        cout << punkty_odpowiedzi[a][b];
    }
    myfile << "\n";
}
myfile.close();


    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

}
/*************************
FUNKCJE roboczo


*******************************/

