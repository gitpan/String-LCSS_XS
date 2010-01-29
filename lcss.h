typedef struct S_LCSS
{
    char* s;
    int pos_s;
    int pos_t;
} LCSS;

typedef struct S_LCSS_RES
{
    LCSS* lcss;
    int n;
} LCSS_RES;

LCSS_RES _lcss(char* s, char* t, int min);
void _free_res(LCSS_RES res);
