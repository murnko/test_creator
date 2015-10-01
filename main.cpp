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
//ARGUMENTY
const int liczba_punktow = 3;
const int liczba_odp = 4;
const int LICZBA_ZESTAWOW = 2;

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


    baza_pytan.open("/media/store/GIT/test_creator/Baza.txt");
    size_t rozm_bazy = sprawdz_baze(baza_pytan);
    int punktacja[100]; //każdy wiersz odpowiada tabeli odpowiada za kolejne pyatnie
    waga_pytan(baza_pytan,punktacja,rozm_bazy);
//POCZATEK PETLI DLA JEDNEGO TESTU
for (int t=1; t <LICZBA_ZESTAWOW+1; t++)
{
    string pobraneWiersze[1024];


    int * wiersze_tmp = new int[rozm_bazy];
    liczba_pytan = wybierz_pytania(wiersze_tmp, punktacja, liczba_punktow,rozm_bazy);
    int * wybrane_wiersze = new int[3*liczba_pytan];

    string * Output = pobierz_pytania(baza_pytan,liczba_pytan,wybrane_wiersze,wiersze_tmp,
                                pobraneWiersze,rozm_bazy, liczba_odp);


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
HPDF_Page_BeginText (page);
    string numer;
    char * numer_pytania;
    for (int i =0;i<liczba_pytan;i++ ){
        numer = to_string(i+1);
        numer_pytania = strdup(numer.c_str());
        //HPDF_Page_TextOut(page, 29+20*i,17+20*liczba_odp, numer_pytania );
        HPDF_Page_TextRect (page, 22+20*i,30+20*liczba_odp , 22+20*i+20,30+20*liczba_odp+20,
                    numer_pytania, HPDF_TALIGN_CENTER, NULL);
    }
    string literal;
    char *odpowiedz;
    int litera = 64;

    for(int i =0; i<liczba_odp; i++){
        litera++;
        literal = (char)litera;
        odpowiedz = strdup(literal.c_str());
        HPDF_Page_TextOut(page, 12,20*liczba_odp-20*i-3,odpowiedz);
    }
HPDF_Page_EndText (page);
    HPDF_Page_Rectangle(page, 22,12,page_width-35,20*(liczba_odp+1));

    for (int i =0; i < 15; i++){
    HPDF_Page_Rectangle(page, 22+20+40*i,12,20,20*(liczba_odp+1));
    }
    HPDF_Page_MoveTo(page,22,32);
    for (int i =0; i < liczba_odp; i++){
        HPDF_Page_LineTo(page,page_width-13,32+20*i);
        HPDF_Page_MoveTo(page,22,52+20*i);
    }
    for(int h =0; h<liczba_odp; h++){
        for(int v = 0; v <28;v++){
        HPDF_Page_Rectangle(page, 28+20*v,18+20*h,8,8);
        }
    }

HPDF_Page_Stroke (page);

}
// KONIEC PĘTLI DLA JEDNEGO TESTU



    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

}
/*************************
FUNKCJE roboczo


*******************************/

