#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "lcss.h"

LCSS_RES _lcss(char* s, char* t) {
    int i,j,m,n,z,found,allocated;
    int *pos_s, *pos_t;  /* hit positions in s and t */
    int **L;             /* dyn. programming matrix  */
    LCSS *lcss;          /* return value lcss        */
    LCSS_RES res;        /* return value             */

    m = strlen(s);
    n = strlen(t);
    // allocate space for the mn dynamic programming matrix L
    MALLOC(L, int*,m+1);
    for (i=0; i<=m; i++) {
        if ( ( L[i] = (int*)calloc((n+1),sizeof(int) )) == NULL) {
            fprintf(stderr,"calloc failed.\n");
            exit(EXIT_FAILURE); 
        }
    }

    z = 0;
    found = 0;
    allocated = 256;    
    MALLOC(pos_s, int, allocated);
    MALLOC(pos_t, int, allocated);

    // compute matrix
    for (i=1; i<=m; i++) {
        for (j=1; j<=n; j++) {
            /* maybe we need some more space */
            if (found >= allocated) {
                allocated += 256;
                REALLOC(pos_s, int, allocated);
                REALLOC(pos_t, int, allocated);
            }    
            if (s[i-1] == t[j-1]) {
                L[i][j] = L[i-1][j-1]+1;
                if (L[i][j] > z) {
                    z = L[i][j];
                    found = 0;
                }
                if (L[i][j] == z) {
                    pos_s[found] = i - z;
                    pos_t[found] = j - z;
                    found++;
                }	
            }
        }	
    }	

    // free matrix
    for (i=0; i<=m; i++) {
        free(L[i]);
    }
    free(L);
    
    MALLOC(lcss, LCSS,found);
    for (i=0; i < found; i++) {
        MALLOC(lcss[i].s, char, z+1);
        strncpy(lcss[i].s, &s[pos_s[i]],z)[z]='\0';
        lcss[i].pos_s = pos_s[i];
        lcss[i].pos_t = pos_t[i];
    }
    free(pos_s);
    free(pos_t);
    res.lcss = lcss;
    res.n    = found;
    return res;
}


void _free_res(LCSS_RES res) {
    int i;
    for (i=0; i<res.n; i++) {
        free(res.lcss[i].s);
    }
    free(res.lcss);
}

