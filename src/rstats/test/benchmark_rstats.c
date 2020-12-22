#include <stdio.h>

#include <sys/time.h>

#include "rstats.h"

double time_elapsed(void (*function)()) {
    struct timeval tv_begin, tv_end;
    gettimeofday(&tv_begin, NULL);
    function();
    gettimeofday(&tv_end, NULL);
    return ((tv_end.tv_sec * 1e6 + tv_end.tv_usec) - (tv_begin.tv_sec * 1e6 + tv_begin.tv_usec)) / (double)1e6;
}

void benchmark_rstats_mean() {
    double buffer[2] = {0.0};
    double rounds = 1000000000;

    for(volatile double i = 0; i < rounds; i++) {
        rstats_mean(i, 1, buffer);
    }
}

void benchmark_rstats_variance() {
    double buffer[3] = {0.0};
    double rounds = 1000000000;

    for(volatile double i = 0; i < rounds; i++) {
        rstats_variance(i, 1, buffer);
    }
}

void benchmark_rstats_wskewness() {
    double buffer[4] = {0.0};
    double rounds = 1000000000;

    for(volatile double i = 0; i < rounds; i++) {
        rstats_skewness(i, 1, buffer);
    }
}

void benchmark_rstats_kurtosis() {
    double buffer[5] = {0.0};
    double rounds = 1000000000;

    for(volatile double i = 0; i < rounds; i++) {
        rstats_kurtosis(i, 1, buffer);
    }
}

void benchmark_rstats_central_moment() {
    double rounds = 1000000000;
    double buffer[31] = {0.0};
    double sum_weights = 0.0;
    uint64_t p = 30;

    for(volatile double i = 0; i < rounds; i++) {
        rstats_central_moment(i, 1, buffer, p);
    }
}

int main(int argc, char const *argv[]) {
    double time = 0;

    time = time_elapsed(benchmark_rstats_mean);
    printf("Time rstats_mean(): %.16f sec\n", time);
    time = time_elapsed(benchmark_rstats_variance);
    printf("Time rstats_variance(): %.16f sec\n", time);
    time = time_elapsed(benchmark_rstats_wskewness);
    printf("Time rstats_wskewness(): %.16f sec\n", time);
    time = time_elapsed(benchmark_rstats_kurtosis);
    printf("Time rstats_wkurtosis(): %.16f sec\n", time);
    time = time_elapsed(benchmark_rstats_central_moment);
    printf("Time rstats_central_moment(): %.16f sec\n", time);
    return 0;
}