#define MALLOC(P,T,S) { if((P=(T*)malloc(sizeof(T)*(size_t)(S)))==NULL) { \
      fprintf(stderr,"malloc failed.\n"); \
      exit(EXIT_FAILURE); \
    } memset(P,0,sizeof(T)*(size_t)(S)); \
}

#define CALLOC(P,T,S) { if((P=(T*)calloc((size_t)(S),sizeof(T)))==NULL) { \
      fprintf(stderr,"calloc failed.\n"); \
      exit(EXIT_FAILURE); \
} } 

#define REALLOC(P,T,S) { if((P=(T*)realloc(P,sizeof(T)*(size_t)(S)))==NULL) { \
      fprintf(stderr,"realloc failed.\n");              \
      exit(EXIT_FAILURE); \
} }
