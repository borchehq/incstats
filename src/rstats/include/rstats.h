#ifndef RSTATS_H
#define RSTATS_H

#include <math.h>
#include <stdint.h>

inline double rstats_pow(double x, uint64_t y) {
    double result = x;

    if(y == 0) {
        return 1.0;
    }
    for(uint64_t i = 0; i < y - 1; i++) {
        result *= x;
    }

    return result;
}

inline double factorial(uint64_t n) {
    uint64_t result = 1.0;
    for(uint64_t i = 2; i <= n; i++) {
        result *= i;
    }
    return (double)result;
}

inline double n_choose_k(uint64_t n, uint64_t k) {
    uint64_t result = 1.0;
    k = k > n-k ? n-k : k;
    for(uint64_t j = 1; j <= k; j++, n--) {
        if(n % j == 0) {
            result *= n / j;
        }
        else if(result % j == 0) {
            result = result / j * n;
        }
        else {
            result = result * n / j;
        }
    }
    return (double)result;
}

inline void rstats_mean(double x, double w, double *buffer) {
    buffer[0] += w;
    buffer[1] = buffer[1] + w / buffer[0] * (x - buffer[1]);
}

inline void rstats_mean_finalize(double *mean, double *buffer) {
    *mean = buffer[1];
}

inline void rstats_variance(double x, double w, double *buffer) {
    double new_mean;

    buffer[0] += w;
    new_mean = buffer[1] + w / buffer[0] * (x - buffer[1]);
    buffer[2] = buffer[2] + w * (x - buffer[1]) * (x - new_mean);
    buffer[1] = new_mean;
}

inline void rstats_variance_finalize(double *results, double *buffer) {
    results[0] = buffer[1];
    results[1] = buffer[2] / buffer[0];
}

inline void rstats_skewness(double x, double w, double *buffer) {
    double new_sum_w = buffer[0] + w;
    buffer[3] = buffer[3] + 3 * (buffer[2]) * (-w * (x - buffer[1]) /
                    new_sum_w) + buffer[0] * rstats_pow(-w * (x - buffer[1]) / 
                    new_sum_w, 3) + w * rstats_pow(buffer[0] * 
                    (x - buffer[1]) / new_sum_w, 3);
    buffer[2] = buffer[2] + buffer[0] * rstats_pow(-w * (x - buffer[1]) / 
                    new_sum_w, 2) + w * rstats_pow(buffer[0] * 
                    (x - buffer[1]) / new_sum_w, 2);
    buffer[1] = buffer[1] + w / new_sum_w * (x - buffer[1]);
    buffer[0] = new_sum_w;
}

inline void rstats_skewness_finalize(double *results, double *buffer) {
    results[0] = buffer[1];
    results[1] = buffer[2] / buffer[0];
    results[2] = (buffer[3] / buffer[0]) / ((buffer[2] / buffer[0]) 
                 * sqrt(buffer[2] / buffer[0]));
}

inline void rstats_kurtosis(double x, double w, double *buffer) {
    double new_sum_w = buffer[0] + w;
    buffer[4] = buffer[4] + 4.0 * (buffer[3]) * 
                (-w * (x - buffer[1]) / new_sum_w) + 6.0 * (buffer[2]) * 
                rstats_pow((-w * (x  - buffer[1]) / new_sum_w), 2) + buffer[0]
                * rstats_pow((-w * (x  - buffer[1]) / new_sum_w), 4) + w * 
                rstats_pow((buffer[0] * (x  - buffer[1]) / new_sum_w), 4);
    buffer[3] = buffer[3] + 3 * (buffer[2]) * (-w * (x - buffer[1]) /
                    new_sum_w) + buffer[0] * rstats_pow(-w * (x - buffer[1]) / 
                    new_sum_w, 3) + w * rstats_pow(buffer[0] * 
                    (x - buffer[1]) / new_sum_w, 3);
    buffer[2] = buffer[2] + buffer[0] * rstats_pow(-w * (x - buffer[1]) / 
                    new_sum_w, 2) + w * rstats_pow(buffer[0] * 
                    (x - buffer[1]) / new_sum_w, 2);
    buffer[1] = buffer[1] + w / new_sum_w * (x - buffer[1]);
    buffer[0] = new_sum_w;
}

inline void rstats_kurtosis_finalize(double *results, double *buffer) {
    results[0] = buffer[1];
    results[1] = buffer[2] / buffer[0];
    results[2] = (buffer[3] / buffer[0]) / ((buffer[2] / buffer[0]) 
                 * sqrt(buffer[2] / buffer[0]));
    results[3] = (buffer[4] / buffer[0]) / 
                 rstats_pow((buffer[2] / buffer[0]), 2);
}

inline void rstats_central_moment(double x, double w, double *buffer, uint64_t p) {
    double new_sum_w = buffer[0] + w;

    for(uint64_t i = p; i > 1; i--) {
        double tmp = 0.0;
        for(uint64_t k = i - 2; k > 0; k--) {
           tmp += n_choose_k(i, k) * buffer[i - k] * 
                  rstats_pow(-w * (x - buffer[1]) / new_sum_w, k);  
        }
        buffer[i] = buffer[i] + tmp +
                    buffer[0] * rstats_pow(-w * (x - buffer[1]) / 
                    new_sum_w, i) + w * rstats_pow(buffer[0] * 
                    (x - buffer[1]) / new_sum_w, i);
    }
    buffer[1] = buffer[1] + w / new_sum_w * (x - buffer[1]);
    buffer[0] = new_sum_w;
}

inline void rstats_central_moment_finalize(double *results, double *buffer, uint64_t p) {
    results[0] = buffer[1];
    for(uint64_t i = 1; i < p; i++) {
        results[i] = buffer[i + 1] / buffer[0];
    }
}

inline void rstats_max(double x, double *max) {
    if(*max < x) {
        *max = x;
    }
}

inline void rstats_min(double x, double *min) {
    if(*min > x) {
        *min = x;
    }
}

#endif