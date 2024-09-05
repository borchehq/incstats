#include "incstats.h"


extern double incstats_pow(double x, uint64_t y);
extern uint64_t factorial(uint64_t n);
extern void incstats_mean(double x, double w, double *buffer);
extern void incstats_mean_finalize(double *mean, double *buffer);
extern void incstats_variance(double x, double w, double *buffer);
extern void incstats_variance_finalize(double *results, double *buffer);
extern void incstats_skewness(double x, double w, double *buffer);
extern void incstats_skewness_finalize(double *results, double *buffer);
extern void incstats_kurtosis(double x, double w, double *buffer);
extern void incstats_kurtosis_finalize(double *results, double *buffer);
extern void incstats_central_moment(double x, double w, double *buffer,
                                  uint64_t p);
extern void incstats_central_moment_finalize(double *results, double *buffer,
                                           uint64_t p, bool standardize);
extern void incstats_max(double x, double *max);
extern void incstats_min(double x, double *min);
extern uint64_t n_choose_k(uint64_t n, uint64_t k);