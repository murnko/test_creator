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
const int liczba_punktow = 20;
const int liczba_odp = 4;

ifstream baza_pytan;
string pobraneWiersze[1024];
int wybrane_pytania[10];
int punktacja[100]; //każdy wiersz odpowiada tabeli odpowiada za kolejne pyatnie
jmp_buf env;

int main(int argc, char **argv)
{


    char nbsp= (char) 4294967200;

   cout << /*(unsigned int)*/nbsp<<endl;

    //baza_pytan.open("/media/murnko/store/projekty/studio1/Baza.txt");
    baza_pytan.open("/media/murnko/store/GIT/test_creator/Baza.txt");
    size_t rozm_bazy = sprawdz_baze(baza_pytan); //DONE
    int * wiersze_tmp = new int[rozm_bazy];//IN

    waga_pytan(baza_pytan,punktacja,rozm_bazy);//DONE

    liczba_pytan = wybierz_pytania(wiersze_tmp, punktacja, liczba_punktow,rozm_bazy);
    int * wybrane_wiersze = new int[3*liczba_pytan];

    string * Output = pobierz_pytania(baza_pytan,liczba_pytan,wybrane_wiersze,wiersze_tmp,
                                pobraneWiersze,rozm_bazy, liczba_odp);


    char* libHaruIN[20];
    string linetmp;
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
    HPDF_Doc  pdf;
    HPDF_Page page;
    char fname[256];
    HPDF_Font font;
    const char *fontname;
    HPDF_REAL page_height, page_width, linijka;
    HPDF_Point position;
    HPDF_STATUS stat;
    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    page = HPDF_AddPage (pdf);
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    stat = HPDF_UseUTFEncodings(pdf);
    cout << stat << endl;
    const char * utf = "UTF-8";
    HPDF_SetCurrentEncoder(pdf,utf);
    //print_grid  (pdf, page);

    page_height = HPDF_Page_GetHeight (page);
    page_width = HPDF_Page_GetWidth(page);
    //fontname = HPDF_LoadTTFontFromFile(pdf,"/home/murnko/Downloads/dosis-v1.7/Dosis v1.7/Dosis-Book.ttf", HPDF_TRUE);
    fontname = HPDF_LoadTTFontFromFile(pdf,"/media/murnko/store/GIT/test_creator/Lato-Regular.ttf", HPDF_TRUE);
    font = HPDF_GetFont (pdf, fontname, "UTF-8");
    HPDF_Page_SetTextLeading (page, 20);


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

    HPDF_Page_BeginText (page);

    HPDF_Page_SetFontAndSize (page, font, 12);
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



    linijka = page_height-12;
    for (int i =0; i<liczba_pytan;i++){
        HPDF_Page_TextRect (page, 10,linijka , page_width-10, 0,
                    libHaruIN[i], HPDF_TALIGN_JUSTIFY, NULL);
        position = HPDF_Page_GetCurrentTextPos(page);
        linijka = position.y - 12;
    }

//    HPDF_Page_TextRect (page, 0, position.y, page_width, 0,
//                SAMPLE3, HPDF_TALIGN_JUSTIFY, NULL);


    HPDF_Page_EndText (page);
    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

////Roboczy print wyniku posredniego
//    cout<< "OUTPUT" << endl;
//    for (int z =0; z < 2*liczba_pytan*(liczba_odp+2); z++){
//        cout << Output[z]<< endl;
//    }
//    cout << "\n"; return -1;
//            baza_pytan.close();
//            getchar();


//    return 0;
}
/*************************
FUNKCJE roboczo


*******************************/

