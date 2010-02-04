#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

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

LCSS_RES _lcss(char* s, char* t, int min, int utf8s, int utf8t);
void _free_res(LCSS_RES res);
void _get_byte_positions(char *s, int pos, int length, int *begin, int *end);
