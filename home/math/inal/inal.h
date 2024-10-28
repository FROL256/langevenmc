/* FILE  inal.h
 * PURPOSE      Header file for Numerical Analysis Library
 *   Initial version.
 * $Log:$
 */

#ifndef _INAL_H_
#define _INAL_H_

#ifdef VCS
/* Vesrion control string */
/*char *sccsid = "@(#)$Header:$";*/
char *sccsid = "Num. Analysis Lib., v1.0 of 23.02.98";
#endif

/* MACRO interfaces to functions */
#define quicksort2(x, y, n) quick_sort2(x, y, 0, (n) - 1)

#define CLEAR(x, n) memset((char *)(x), 0, (n) * sizeof (*(x)))
#define COPY(y, x, n) memcpy((char *)(y), (char *)(x), \
                             (n) * min(sizeof (*(x)), sizeof (*(y))))
#define MOVE(y, x, n) memmove((char *)(y), (char *)(x), \
                             (n) * min(sizeof (*(x)), sizeof (*(y))))

#ifdef PI
  #undef PI
#endif
#ifdef PI2
  #undef PI2
#endif
#define PI       3.1415926535897931
#define PI2      6.2831853071795862    /* 2pi       */


#define ZERO_DOUBLE 1e-40  /* used as "underflow" limit */
#ifndef MAX_DOUBLE
  #define MAX_DOUBLE  1e200
#endif

/* Find if 'n' is a nonnegative integer power of '2'.
 * If yes, 'answer=1, otherwise, answer=0. 
 */
#define IS_POWER2(n, answer) \
  {                          \
  int _itmp1_, _itmp2_;      \
  _itmp1_ = 1;               \
  _itmp2_ = (n);             \
  while (_itmp2_ > 1)        \
  {                          \
    _itmp2_ >>= 1;           \
    _itmp1_ <<= 1;           \
  }                          \
  if (_itmp1_ != (n))        \
    answer = 0;              \
  else                       \
    answer = 1;              \
  }

typedef enum NAL_ERRCODE
  {
  NAL_OK         =  0,  /* no error                                      */
  NAL_BAD_MATRIX = -1,  /* singular matrix                               */
  NAL_MEM_ERR    = -2,  /* insufficient buffer size OR allocation failed */
  NAL_BAD_PARAM  = -3,  /* bad parameters (n != 2^m in FFT etc)          */
  NAL_BAD_INTERV = -4   /* bad interval (a > b etc)                      */
  } NAL_ERRCODE;

typedef enum FFT_DIRECTION
  {
  FFT_BACKWARD  = -1,
  FFT_FORWARD   =  1,
  FFT_SYNTHESIS = -1,
  FFT_ANALYSIS  =  1
  } FFT_DIRECTION;

typedef enum SKIND
  {
  SPLINE, EXP_SPLINE
  } SKIND;

typedef enum TREE_MODE
  {
  ADD     = -1,
  NO_ADD  =  1
  } TREE_MODE;

typedef struct TREE_NODE
  {
  double *x;               /* the data element                  */
  struct TREE_NODE *left;  /* left  son (with data element < x) */
  struct TREE_NODE *right; /* right son (with data element > x) */
  } TREE_NODE;


typedef struct KIAML
  {
  double full;   /* the kiaml over fine (=full) mesh            */
  double rough;  /* the kiaml over rough (=odd knots only) mesh */
  } KIAML;

char   *inal_version();

/* ============ Linear algebra =================== */
void   mmult(IN double *a, IN double *b, INOUT double *c,
                   IN int n1, IN int n2, IN int n3, OUT double *wk);

void   msqr(INOUT double **b, IN double *a,
                  IN int m, IN int n, IN double q, IN int mode);

int    resol(INOUT double *a, OUT double *x, INOUT double *f,
                   IN int n, IN int job, OUT int *iwk);
int    resol1(INOUT double *a, OUT double *x, INOUT double *f,
                    IN int n, IN int job);

int    invert(INOUT double *a, IN int n);

int    choldc(INOUT double *a, OUT double *r_s_diag, OUT double *d, 
                    IN int n);
void   cholsl(IN double *s, IN double *r_s_diag, IN double *d,
                    OUT double *x, IN double *f, IN int n);

int    choldc1(INOUT double **a, OUT double *r_s_diag, OUT double *d, 
                     IN int n);
void   cholsl1(IN double **s, IN double *r_s_diag, IN double *d,
                     OUT double *x, IN double *f, IN int n);

int    jacobi(INOUT double *a, OUT double *d, OUT double *v,
                    IN int n, OUT double *wk);

double **bd_create(IN int n, IN int m1, IN int m2,
                   INOUT char **buf, IN int size);
void   bd_destroy(IN double **a);

void   bd_mmult(IN double **a, IN double **b, OUT double **c,
                IN int n, IN int m1a, IN int m2a, IN int m1b, IN int m2b,
                OUT double *wk);

int    bd_resol(INOUT double **a, OUT double *x, INOUT double *f,
                IN int n, IN int m1, IN int m2, IN int job);

int    tridiag(INOUT double *a, INOUT double *b, IN double *c,
               OUT double *x, IN double *f, IN int n, IN int job);

int    fivediag(IN double *a, IN double *b, IN double *c,
                IN double *d, IN double *e, OUT double *x,
                IN double *f, IN int n, IN int job);

void   fivediag_ser_init(IN double *a, IN double *b, IN double *c,
                         IN double *d, IN double *e, OUT double *aux,
                         IN int n);

/* ================= Splines =================== */
void   spline_func(IN double *y, IN double *s, IN double *ds, IN int m,
                   IN double *x, OUT double *f, OUT double *df,
                   OUT double *d2f, IN int n);
void   spline_func1(IN double *y, IN double *s, IN double *ds, IN int m,
                   IN double *x, OUT double *f, IN int n);

int    ispline(IN double *x, IN double *f, OUT double *ds,
               IN int n, IN int bc1, IN int bc2, OUT double *wk);
int    sspline(IN double *x, IN double *f, OUT double *ds,
               IN int n, IN int kind, OUT double *wk);

int    tspline(IN double *x, IN double *f, OUT double *ds, OUT double *aux,
               IN int n, IN int bc1, IN int bc2,
               IN double p, OUT double *wk);

void   tspline_func(IN double *y, IN double *s, IN double *ds, IN int m,
                    IN double *aux, IN double *x, OUT double *f,
                    OUT double *df, IN int n, IN double p);
void   tspline_func1(IN double *y, IN double *s, IN double *ds, 
                    IN int m,
                    IN double *aux, IN double *x, OUT double *f,
                    IN int n, IN double p);

int    aspline(IN double *x, IN double *f, IN int n,
               IN double *y, OUT double *s, OUT double *ds,
               IN int m, IN SKIND kind, OUT char *wk);
int    aspline_auto(IN double *x, IN double *f, IN int n,
                    INOUT double *y, OUT double *s, OUT double *ds,
                    INOUT int *m, IN int mmax, INOUT double *tol,
                    IN SKIND kind, OUT char *wk);

int    mspline(IN double *x, IN double *f, IN int n,
               IN double *y, IN double *s, OUT double *ds,
               IN int m, IN SKIND kind, OUT double *wk);

int    mspline_auto(IN double *x, IN double *f, IN int n,
                    OUT double *y, OUT double *s, OUT double *ds,
                    OUT int *m, IN int mmax, INOUT double *tol,
                    IN SKIND kind, OUT double *wk);

double spline_error(IN double *x, IN double *f, IN int n,
                    IN double *y, IN double *s, IN double *ds,
                    IN int m, IN SKIND kind, OUT double *wk);

 /* ============= Roots of equations ============= */
double newton(IN void func(double y, double *f, double *df),
              IN double x, INOUT int *n, INOUT double *tol);
int    newton_md(IN void func(double *y, double *f, double *df),
                 INOUT double *x, IN double *z, IN int dim, INOUT int *n,
                 INOUT double *tol, INOUT double *wk);
double bisection(IN double func(double y), IN double y,
                 IN double a, IN double b, IN double tol);
int    find_left_knot(IN double x, IN double *xv, IN int n);
double secant(IN double func(IN double x), IN double x, IN double eps,
              INOUT int *n, INOUT double *tol);

/* ============ Kiamtion =================== */
int na_kiaml(IN void kiamnd(double x, double *f),
                IN double a, IN double b,
                IN int n, IN int k, OUT struct KIAML *kiamls);
int na_kiaml_p(IN void kiamnd(double x, double *f, void *p),
                  IN double a, IN double b,
                  IN int n, IN int k, OUT struct KIAML *kiamls,
                  IN void *p);

int na_kiaml_auto(void kiamnd(double x, double *f),
                     IN double a, IN double b,
                     INOUT int *n, IN int n_max, IN int k,
                     OUT struct KIAML *kiamls, INOUT double *tol);
int na_kiaml_auto_p(void kiamnd(double x, double *f, void *p),
                       IN double a, IN double b,
                       INOUT int *n, IN int n_max, IN int k,
                       OUT struct KIAML *kiamls, INOUT double *tol,
                       IN void *p);

/* ============ Fast Fourier Transform =================== */
extern int fft(INOUT double *z, IN int n, IN FFT_DIRECTION dir);
extern int fft_real(INOUT double *f, IN int n, IN FFT_DIRECTION dir);
extern int fft_sine(INOUT double *f, IN int n);
extern int fft_cosine(INOUT double *f, IN int n);
extern int fft_sine_halved(INOUT double *f, IN int n, 
                                 IN FFT_DIRECTION dir);

extern int convreal(OUT double *z, INOUT double *x, INOUT double *y,
                    IN int n, IN int mode);

extern void duhamel(INOUT double *h, INOUT double *f, OUT double *g,
                    IN int n, IN int m, OUT double *wk);

/* ========== Binary tree ============== */
TREE_NODE *tree_create(INOUT double **x, IN int n, IN int n_nodes,
                       INOUT char **buf, IN int size);
void       tree_destroy(IN TREE_NODE *tree_node, IN double *x);


int        na_tree(IN double *x, IN int n, INOUT TREE_NODE *tree_node,
                   INOUT int *last_node, IN int max_nodes, IN TREE_MODE mode);

/* ========== Quick sort ============== */
void      quick_sort2(IN double *x, IN double *y, IN int start, IN int end);

#endif

/* 'inal.h' file end */
