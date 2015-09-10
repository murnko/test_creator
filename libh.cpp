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
