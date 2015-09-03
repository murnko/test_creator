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
jmp_buf env;

int main(int argc, char **argv)
{

    baza_pytan.open("/media/murnko/store/projekty/studio1/Baza.txt");
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
        if (!(i%7)){

//            cout <<linetmp<< endl;
            libHaruIN[n] = strdup(linetmp.c_str());
            cout <<libHaruIN[n]<<endl;
            n++;
            linetmp = "";
            linetmp.append(to_string(n+1));
            linetmp.append(". ");
        }
        }
        linetmp.append(Output[i]);
        linetmp.append(" ");
//        char * out_tmp = new char[Output[i].size() + 1];
//        copy(Output[i].begin(), Output[i].end(), out_tmp);
//        out_tmp[Output[i].size()] = '\0';

//        strcat(linetmp, out_tmp);
//        delete out_tmp;
        //libHaruIN[n] =
        //strcpy (libHaruIN[n], out_tmp);
        //strcat (libHaruIN[n]," ");
        cout << "i= " << i << " n= " << n << endl;
    }


//LIBHARU
    char* testlibharu = libHaruIN[0];

    HPDF_Doc  pdf;
    HPDF_Page page;
    char fname[256];
    HPDF_Font font;
    HPDF_REAL page_height, page_width;
    HPDF_Point position;
    testlibharu = dodajOgonki(testlibharu);
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

    //print_grid  (pdf, page);

    page_height = HPDF_Page_GetHeight (page);
    page_width = HPDF_Page_GetWidth(page);

    font = HPDF_GetFont (pdf, "Helvetica", "ISO8859-2");
    HPDF_Page_SetTextLeading (page, 20);
    //HPDF_Page_Stroke (page);

    HPDF_Page_BeginText (page);

    HPDF_Page_SetFontAndSize (page, font, 10);
    HPDF_Page_TextRect (page, 5, page_height-10, page_width, 0,
                testlibharu, HPDF_TALIGN_JUSTIFY, NULL);
    position = HPDF_Page_GetCurrentTextPos(page);
    cout << position.x << endl;
    cout << position.y << endl;
//    HPDF_Page_TextRect (page, 0, position.y, page_width, 0,
//                SAMPLE3, HPDF_TALIGN_JUSTIFY, NULL);


    HPDF_Page_EndText (page);
    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

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
