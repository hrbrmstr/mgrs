#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP mgrs_latlng_to_mgrs(SEXP, SEXP, SEXP, SEXP);
extern SEXP mgrs_mgrs_to_latlng(SEXP, SEXP);
extern SEXP mgrs_mgrs_to_ups(SEXP);
extern SEXP mgrs_mgrs_to_utm(SEXP);
extern SEXP mgrs_ups_to_latlng(SEXP, SEXP, SEXP, SEXP);
extern SEXP mgrs_ups_to_mgrs(SEXP, SEXP, SEXP, SEXP);
extern SEXP mgrs_utm_to_latlng(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP mgrs_utm_to_mgrs(SEXP, SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"mgrs_latlng_to_mgrs", (DL_FUNC) &mgrs_latlng_to_mgrs, 4},
    {"mgrs_mgrs_to_latlng", (DL_FUNC) &mgrs_mgrs_to_latlng, 2},
    {"mgrs_mgrs_to_ups",    (DL_FUNC) &mgrs_mgrs_to_ups,    1},
    {"mgrs_mgrs_to_utm",    (DL_FUNC) &mgrs_mgrs_to_utm,    1},
    {"mgrs_ups_to_latlng",  (DL_FUNC) &mgrs_ups_to_latlng,  4},
    {"mgrs_ups_to_mgrs",    (DL_FUNC) &mgrs_ups_to_mgrs,    4},
    {"mgrs_utm_to_latlng",  (DL_FUNC) &mgrs_utm_to_latlng,  5},
    {"mgrs_utm_to_mgrs",    (DL_FUNC) &mgrs_utm_to_mgrs,    5},
    {NULL, NULL, 0}
};

void R_init_mgrs(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}