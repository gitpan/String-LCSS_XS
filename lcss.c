#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* lcss(char* s, char* t) {
	// allocate space for the mn dynamic programming matrix L
	int m = strlen(s);
	int n = strlen(t);
    int ** L = (int**)malloc((m+1)*sizeof(int*));
	int i; 
    int j;
	for (i=0; i<(m+1); i++) {
		L[i] = (int*)malloc((n+1)*sizeof(int));
	}
	int z = 0;
	int found = 0;
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
				}
				if (L[i][j] == z) {
					found = i - z;
				}	
			}			
		}	
	}	
	
	// free matrix
	for (i=0; i<(sizeof(s)+1); i++) {
		free(L[i]);
	}
	free(L);
	
	char* ret = (char*)malloc((z+1)*sizeof(char));
	strncpy(ret, &s[found],z)[z]='\0';
	return ret;
}
