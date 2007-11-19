#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* lcss(char* s, char* t) {
    int i,j,m,n,z,found;
    int** L;
    char *ret;

    m = strlen(s);
    n = strlen(t);
    // allocate space for the mn dynamic programming matrix L
    L = (int**)malloc((m+1)*sizeof(int*));
    for (i=0; i<=m; i++) {
        L[i] = (int*)malloc((n+1)*sizeof(int));
    }
    z = 0;
    found = 0;
    // initialize matrix
    for (i=0; i<=m; i++) {
        for (j=0; j<=n; j++) {
            L[i][j] =0;
        }
    }
    // compute matrix
    for (i=1; i<=m; i++) {
        for (j=1; j<=n; j++) {
            if (s[i-1] == t[j-1]) {
                L[i][j] = L[i-1][j-1]+1;
                if (L[i][j] > z) {
                    z = L[i][j];
            // if this will ever return a list
            // of lcss, then the above if statement needs
            // to erase the ret array and the one below
            // needs to push the current position in ret
            //    }
            //    if (L[i][j] == z) {
                    found = i - z;
                }	
            }			
        }	
    }	

    // free matrix
    for (i=0; i<=m; i++) {
        free(L[i]);
    }
    free(L);

    
    if ((ret = malloc(z+1)) != NULL) {
        strncpy(ret, &s[found],z)[z]='\0';
    }   
    return ret;
}
