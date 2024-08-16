#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "rstats.h"

void test_rstats_mean() {
    double x[10] = {4, 8, 12, 16, 23, 45, 678, 123, 2.0123, M_PI};
    double weights[10] = {1, 7, 2, 0.3, 1, M_PI_2, M_PI_4, 10, 9, M_2_SQRTPI};
    double mean = 0, sum_weights = 0;
    double comp;
    double sum_comp = 0, sum_weights_comp = 0;
    double buffer[2] = {0};

    for(size_t i = 0; i < 10; i++) {
        rstats_mean(x[i], weights[i], buffer);
        rstats_mean_finalize(&mean, buffer);
        sum_comp += weights[i] * x[i];
        sum_weights_comp += weights[i];
        comp = sum_comp / sum_weights_comp;
        //printf("%f, %f\n", wmean, comp);
        assert(fabs(mean - comp) < 1e-7);
    }
}

void test_rstats_variance() {
    double x[10] = {10831.0, 10825.03, 10831.4, 10831.4, 10825.03, 10830.0, 10830.0, 10830.0, 10826.31, 10830.0};
    double weights[10] = {0.00548588, 0.0052706, 0.078, 0.09186439, 0.18799166, 1.59741459, 0.53998836, 0.50323176, 0.0334425, 0.76408126};
    double buffer[3] = {0.0};
    double results[2] = {0.0};
    double comp, variance;
    double sum_comp = 0, sum_weights_comp = 0, comp_v = 0;


    for(size_t i = 0; i < 10; i++) {
        rstats_variance(x[i], 1, buffer);
        rstats_variance_finalize(results, buffer);
        sum_comp += x[i];
        sum_weights_comp += 1;
        comp = sum_comp / sum_weights_comp;
        for(size_t j = 0; j < i + 1; j++) {
            comp_v += (x[j] - comp) * (x[j] - comp);
        }
        comp_v /= sum_weights_comp;
        //printf("%f, %f\n", variance, comp_v);
        assert(fabs(results[0] - comp) < 1e-7);
        assert(fabs(results[1] - comp_v) < 1e-7);
        assert(fabs(buffer[2] / buffer[0] - comp_v) < 1e-7);
        comp_v = 0;
    }

}

void test_rstats_wskewness() {
    double x[10] = {10831.0, 10825.03, 10831.4, 10831.4, 10825.03, 10830.0, 10830.0, 10830.0, 10826.31, 10830.0};
    double weights[10] = {0.00548588, 0.0052706, 0.078, 0.09186439, 0.18799166, 1.59741459, 0.53998836, 0.50323176, 0.0334425, 0.76408126};
    double buffer[4] = {0.0}, results[3] = {0.0};
    double skewness, dummy;
    double sum_weights_comp, skewness_comp = 0, sum_comp = 0, comp = 0, variance_comp = 0;

    for(size_t i = 0; i < 10; i++) {
        rstats_skewness(x[i], weights[i], buffer);
        rstats_skewness_finalize(results, buffer);
        sum_comp += weights[i] * x[i];
        sum_weights_comp += weights[i];
        comp = sum_comp / sum_weights_comp;
         for(size_t j = 0; j < i + 1; j++) {
            skewness_comp += weights[j] * (x[j] - comp) * (x[j] - comp) * (x[j] - comp);
            variance_comp += weights[j] * (x[j] - comp) * (x[j] - comp);
        }
        skewness_comp /= sum_weights_comp;
        variance_comp /= sum_weights_comp;
        if(i > 0)
            assert(fabs(results[2] - skewness_comp / pow(variance_comp, 1.5)) < 1e-7);
        //printf("%f, %f\n", skewness, skewness_comp);
        skewness_comp = 0;
        variance_comp = 0;
    }
}

void test_rstats_kurtosis() {
    double x[10] = {10831.0, 10825.03, 10831.4, 10831.4, 10825.03, 10830.0, 10830.0, 10830.0, 10826.31, 10830.0};
    double weights[10] = {0.00548588, 0.0052706, 0.078, 0.09186439, 0.18799166, 1.59741459, 0.53998836, 0.50323176, 0.0334425, 0.76408126};
    double buffer[5] = {0.0}, results[4] = {0.0};
    double kurtosis, dummy;
    double sum_weights_comp, kurtosis_comp = 0, skewness_comp = 0, sum_comp = 0, comp = 0, variance_comp = 0;
    for(size_t i = 0; i < 10; i++) {
        rstats_kurtosis(x[i], weights[i], buffer);
        rstats_kurtosis_finalize(results, buffer);
        sum_comp += weights[i] * x[i];
        sum_weights_comp += weights[i];
        comp = sum_comp / sum_weights_comp;
         for(size_t j = 0; j < i + 1; j++) {
            kurtosis_comp += weights[j] * (x[j] - comp) * (x[j] - comp) * (x[j] - comp) * (x[j] - comp);
            variance_comp += weights[j] * (x[j] - comp) * (x[j] - comp);
        }
        kurtosis_comp /= sum_weights_comp;
        variance_comp /= sum_weights_comp;
       // printf("Variance: %f\n", pow(variance_comp, 2.0));
        if(i > 0) {
            assert(fabs(results[3] - kurtosis_comp / pow(variance_comp, 2.0)) < 1e-5);
        }
        //printf("%f, %f\n", results[3], kurtosis_comp / (variance_comp * variance_comp));
        kurtosis_comp = 0.0;
        variance_comp = 0.0;
    }
}

void test_central_moment() {
    double x[10] = {10831.0, 10825.03, 10831.4, 10831.4, 10825.03, 10830.0, 10830.0, 10830.0, 10826.31, 10830.0};
    double weights[10] = {0.00548588, 0.0052706, 0.078, 0.09186439, 0.18799166, 1.59741459, 0.53998836, 0.50323176, 0.0334425, 0.76408126};
    uint64_t p = 15;
    double mass = 0;
    double mean_cmp = 0;
    double results[15 + 2] = {0.0}, buffer[15 + 1] = {0.0}, wmoments_comp[15 + 1] = {0.0};
    double results_2[4] = {0.0}, buffer_2[5] = {0.0};
    double sum_weights = 0.0, sum_weights_comp = 0.0;
    double tmp = 0.0;
    double results_3[3], buffer_3[3];

    for(size_t i = 0; i < 10; i++) {
    rstats_central_moment(x[i], weights[i], buffer, p);
    rstats_central_moment_finalize(results, buffer, p, false);
    
    // Calculate mean.
    mass += weights[i] * x[i];
    sum_weights_comp += weights[i];
    mean_cmp = mass / sum_weights_comp;
    //printf("%f, %f\n", results[16],  mean_cmp);
    assert(fabs(results[16] - mean_cmp) < 1e-7);
    for(size_t k = 0; k < p; k++) {
        for(size_t j = 0; j < i + 1; j++) {
            wmoments_comp[k] += weights[j] * rstats_pow(x[j] - mean_cmp, k);
        }
        //printf("%f, %f\n", results[k],  wmoments_comp[k] / sum_weights_comp);
        assert(fabs(results[k] - wmoments_comp[k] / sum_weights_comp) < 1e-2);
        wmoments_comp[k] = 0.0;
    }
    }

    for(size_t i = 0; i < 16; i++) {
        buffer[i] = 0.0;
    }

    for(size_t i = 0; i < 10; i++) {
        rstats_central_moment(x[i], weights[i], buffer, p);
        rstats_central_moment_finalize(results, buffer, p, true);
        rstats_kurtosis(x[i], weights[i], buffer_2);
        rstats_kurtosis_finalize(results_2, buffer_2);
        if(i > 0) {
            assert(fabs(results[3] - results_2[2]) < 1e-2);
            assert(fabs(results[4] - results_2[3]) < 1e-2);
        }
    }

    for(size_t k = 0; k < 3; k++) {
        for(size_t i = 0; i < 10; i++) {
            rstats_central_moment(x[i], weights[i], buffer_3, k);
            rstats_central_moment_finalize(results_3, buffer_3, k, false);
            assert(results_3[0] == 1.0);
            if(k >= 1) {
                assert(results_3[1] == 0.0);
            }
            rstats_central_moment_finalize(results_3, buffer_3, k, true);
            assert(results_3[0] == 1.0);
            if(k >= 1) {
                assert(results_3[1] == 0.0);
            }
            if(k >= 2) {
                assert(results_3[2] == 1.0);
            }
        }
    }
}

void test_rstats_max() {
    double x[10] = {4, 8, 12, 16, 23, 45, 678, 123, 2.0123, M_PI};
    double max = DBL_MIN;
    double max_val;

    for(size_t i = 0; i < 10; i++) {
        rstats_max(x[i], &max);
    }
    assert(678 == max);
}


void test_rstats_min() {
    double x[10] = {4, 8, 12, 16, 23, 45, 678, 123, 2.0123, M_PI};
    double min = DBL_MAX;
    double min_val;

    for(size_t i = 0; i < 10; i++) {
        rstats_min(x[i], &min);
    }
    assert(2.0123 == min);
}

int main(int argc, char const *argv[]) {
    printf("[i] Testing rstats_mean()...\n");
    test_rstats_mean();
    printf("[i] Testing rstats_variance()...\n");
    test_rstats_variance();
    printf("[i] Testing rstats_wskewness()...\n");
    test_rstats_wskewness();
    printf("[i] Testing rstats_kurtosis()...\n");
    test_rstats_kurtosis();
    printf("[i] Testing rstats_max()...\n");
    test_rstats_max();
    printf("[i] Testing rstats_min()...\n");
    test_rstats_min();
    printf("[i] Testing central_moment...\n");
    test_central_moment();
    return 0;
}