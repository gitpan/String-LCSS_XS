#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "lcss.h"
#include "macros.h"

LCSS_RES
_lcss(char *s, char *t)
{
    int i, j, m, n, z, found, allocated;
    int *pos_s, *pos_t;         /* hit positions in s and t */
    int *L, *K;                 /* dyn. programming rows    */
    int *Lm, *Km, *temp;        /* dyn. programming rows    */

    LCSS *lcss;                 /* return value lcss        */
    LCSS_RES res;               /* return value             */

    m = strlen(s);
    n = strlen(t);

    /* allocate space for the dynamic programming rows
       I should switch s and t when t is larger than s     */
    CALLOC(Km, int, n + 1);
    CALLOC(Lm, int, n + 1);

    z = 0;
    found = 0;
    allocated = 256;
    MALLOC(pos_s, int, allocated);
    MALLOC(pos_t, int, allocated);

    L = Lm;
    K = Km;

    /* compute matrix */
    for (i = 1; i <= m; i++) {
        for (j = 0; j <= n; j++) {      /* reset L[0] */
            L[j] = 0;
            if (j >= 1 && s[i - 1] == t[j - 1]) {
                L[j] = K[j - 1] + 1;
                if (L[j] > z) {
                    z = L[j];
                    found = 0;
                }
                if (L[j] == z) {
                    /* maybe we need some more space */
                    if (found >= allocated) {
                        allocated += 256;
                        REALLOC(pos_s, int, allocated);
                        REALLOC(pos_t, int, allocated);
                    }
                    pos_s[found] = i - z;
                    pos_t[found] = j - z;
                    found++;
                }
            }
        }
        temp = K;
        K = L;
        L = temp;
    }

    free(L);
    free(K);

    MALLOC(lcss, LCSS, found);
    for (i = 0; i < found; i++) {
        MALLOC(lcss[i].s, char, z + 1);
        strncpy(lcss[i].s, &s[pos_s[i]], z)[z] = '\0';
        lcss[i].pos_s = pos_s[i];
        lcss[i].pos_t = pos_t[i];
    }
    free(pos_s);
    free(pos_t);
    res.lcss = lcss;
    res.n = found;
    return res;
}


void
_free_res(LCSS_RES res)
{
    int i;

    for (i = 0; i < res.n; i++) {
        free(res.lcss[i].s);
    }
    free(res.lcss);
}
