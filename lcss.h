#define MALLOC(P,T,S) { if((P=(T*)malloc(sizeof(T)*(size_t)(S)))==NULL) { \
      fprintf(stderr,"malloc failed.\n"); \
      exit(EXIT_FAILURE); \
    } memset(P,0,sizeof(T)*(size_t)(S)); \
}

#define REALLOC(P,T,S) { if((P=(T*)realloc(P,sizeof(T)*(size_t)(S)))==NULL) { \
      fprintf(stderr,"realloc failed.\n");              \
      exit(EXIT_FAILURE); \
} }

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

LCSS_RES _lcss(char* s, char* t);
void _free_res(LCSS_RES res);
