#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "lcss.h"
#include "macros.h"

LCSS_RES
_lcss(char *s, char *t, int min, int utf8s, int utf8t)
{
    int     i, j, m, n, z, found, allocated;
    int    *pos_s, *pos_t, bb, be, bl;  /* hit positions in s and t */
    int    *L, *K, *temp;       /* dyn. programming rows    */
    char    uvs, uvt;
    char   *tt = t, *ss = s;
    STRLEN  len;


    LCSS   *lcss;               /* return value lcss        */
    LCSS_RES res;               /* return value             */

    m = strlen(s);
    n = strlen(t);

    /* allocate space for the dynamic programming rows
       I should switch s and t when t is larger than s     */
    CALLOC(L, int, n + 1);
    CALLOC(K, int, n + 1);

    z = min - 1;
    found = 0;
    allocated = 256;
    MALLOC(pos_s, int, allocated);
    MALLOC(pos_t, int, allocated);

    /* compute matrix */
    if (utf8s || utf8t) {
        i = 0;
        while (*ss) {
            if (UTF8_IS_INVARIANT(*ss) || !utf8s) {
                uvs = *ss;
                ss++;
            } else {
                uvs = utf8_to_uvchr(ss, &len);
                ss += len;
            }
            i++;
            L[0] = 0;
            tt = t;
            j = 0;
            while (*tt) {
                if (UTF8_IS_INVARIANT(*tt) || !utf8t) {
                    uvt = *tt;
                    tt++;
                } else {
                    uvt = utf8_to_uvchr(tt, &len);
                    tt += len;
                }
                j++;

                if (uvs == uvt) {
                    L[j] = K[j - 1] + 1;
                    if (L[j] > z) {
                        z = L[j];
                        pos_s[0] = i - z;
                        pos_t[0] = j - z;
                        found = 1;
                    } else if (L[j] == z && found) {
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
                } else {
                    L[j] = 0;
                }
            }
            temp = K;
            K = L;
            L = temp;
        }
    } else {
        for (i = 1; i <= m; i++) {
            L[0] = 0;
            for (j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    L[j] = K[j - 1] + 1;
                    if (L[j] > z) {
                        z = L[j];
                        pos_s[0] = i - z;
                        pos_t[0] = j - z;
                        found = 1;
                    } else if (L[j] == z && found) {
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
                } else {
                    L[j] = 0;
                }
            }
            temp = K;
            K = L;
            L = temp;
        }

    }
    FREE(L);
    FREE(K);
    MALLOC(lcss, LCSS, found);
    
    //fprintf(stderr, "%s vs %s (%d %d)\n",s,t,utf8s,utf8t);
    if (utf8s) {
        for (i = 0; i < found; i++) {
            _get_byte_positions(s, pos_s[i], z, &bb, &be);
            bl = be - bb + 1;
            //fprintf(stderr, "%s %d %d %d %d %d\n",s,pos_s[i],z,bb,be,bl);
            MALLOC(lcss[i].s, char, bl + 1);
            strncpy(lcss[i].s, &s[bb], bl)[bl] = '\0';

            lcss[i].pos_s = pos_s[i];
            lcss[i].pos_t = pos_t[i];
        }
    } else {
        for (i = 0; i < found; i++) {
            MALLOC(lcss[i].s, char, z + 1);
            strncpy(lcss[i].s, &s[pos_s[i]], z)[z] = '\0';
            lcss[i].pos_s = pos_s[i];
            lcss[i].pos_t = pos_t[i];
        }
    }
    FREE(pos_s);
    FREE(pos_t);
    res.lcss = lcss;
    res.n = found;
    return res;
}

void
_get_byte_positions(char *s, int pos, int length, int *begin, int *end)
{
    int     i = 0;
    char   *ss = s;
    STRLEN  len;
    UV      c;
    while (*ss) {
        if (i == pos)
            *begin = ss - s;
        if (i == pos + length - 1) {
            *end = ss - s;
            return;
        }
        i++;
        if (UTF8_IS_INVARIANT(*ss)) {
            ss++;
        } else {
            c = utf8_to_uvchr(s, &len);
            ss += len;
        }
    }
}

void
_free_res(LCSS_RES res)
{
    int     i;

    for (i = 0; i < res.n; i++) {
        FREE(res.lcss[i].s);
    }
    FREE(res.lcss);
}
