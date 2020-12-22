#include "rstats.h"


extern double rstats_pow(double x, uint64_t y);
extern double factorial(uint64_t n);
extern void rstats_mean(double x, double w, double *buffer);
extern void rstats_mean_finalize(double *mean, double *buffer);
extern void rstats_variance(double x, double w, double *buffer);
extern void rstats_variance_finalize(double *results, double *buffer);
extern void rstats_skewness(double x, double w, double *buffer);
extern void rstats_skewness_finalize(double *results, double *buffer);
extern void rstats_kurtosis(double x, double w, double *buffer);
extern void rstats_kurtosis_finalize(double *results, double *buffer);
extern void rstats_central_moment(double x, double w, double *buffer,
                                  uint64_t p);
extern void rstats_central_moment_finalize(double *results, double *buffer,
                                           uint64_t p);
extern void rstats_max(double x, double *max);
extern void rstats_min(double x, double *min);
extern double n_choose_k(uint64_t n, uint64_t k);