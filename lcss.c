#include<stdlib.h>
#include<string.h>
#include "lcss.h"

LCSS_RES _lcss(char* s, char* t) {
    int i,j,m,n,z,found;
    int *pos_s, *pos_t;  /* hit positions in s and t */
    int **L;             /* dyn. programming matrix  */
    LCSS *lcss;          /* return value lcss        */
    LCSS_RES res;        /* return value             */

    m = strlen(s);
    n = strlen(t);
    // allocate space for the mn dynamic programming matrix L
    if ((L = (int**)malloc((m+1)*sizeof(int*))) != NULL) {
        for (i=0; i<=m; i++) {
            L[i] = (int*)calloc((n+1),sizeof(int));
        }
    }

    z = 0;
    found = 0;
    pos_s = (int*)malloc(MAXRESULTS * sizeof(int));
    pos_t = (int*)malloc(MAXRESULTS * sizeof(int));

    // compute matrix
    for (i=1; i<=m; i++) {
        for (j=1; j<=n; j++) {
            if (s[i-1] == t[j-1]) {
                L[i][j] = L[i-1][j-1]+1;
                if (L[i][j] > z) {
                    z = L[i][j];
                    found = 0;
                }
                if (L[i][j] == z && found < MAXRESULTS) {
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
    
    if ((lcss = (LCSS*) malloc(found * sizeof(LCSS)))!= NULL) {
        for (i=0; i < found; i++) {
            if ((lcss[i].s = malloc(z+1)) != NULL) {
                strncpy(lcss[i].s, &s[pos_s[i]],z)[z]='\0';
            }
            lcss[i].pos_s = pos_s[i];
            lcss[i].pos_t = pos_t[i];
        }
    }  
    res.lcss = lcss;
    res.n    = found;
    return res;
}
