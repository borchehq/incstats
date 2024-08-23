# librstats

**librstats** is a C library for efficiently computing running statistics, such as mean, variance, skewness, kurtosis, central moments, and finding the maximum and minimum values in a dataset. The library is designed to handle weighted data points, making it suitable for a wide range of applications.

## Status
[![CI](https://github.com/borchehq/rstats/actions/workflows/ci.yml/badge.svg)](https://github.com/borchehq/rstats/actions/workflows/ci.yml)
[![codecov](https://codecov.io/github/borchehq/rstats/graph/badge.svg?token=H24FODSV01)](https://codecov.io/github/borchehq/rstats)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/427138751ae64c2cafe2036c844e0642)](https://app.codacy.com/gh/borchehq/rstats/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
## Features

- Compute running mean, variance, skewness, and kurtosis.
- Calculate central moments up to a specified order.
- Calculate standardized central moments up to a specified order.
- Track maximum and minimum values.
- Designed for efficiency and simplicity.
- Handles weighted data points.

## Installation

To build and install the library, you will need [CMake](https://cmake.org/) version 3.0 or higher. Follow the steps below:

1. Clone the repository:
```bash
   git clone https://github.com/borchehq/rstats.git
   cd rstats
```

2. Create a build directory and navigate into it:
```bash
    mkdir build
    cd build
```

3. Configure the project using CMake:
```bash
    cmake ..
```

4. Build the project:
```bash
    make
```

5. Run the tests (optional):
```bash
    make test
```

6. Install the library:
```bash
    sudo make install
```

## Usage

Include the rstats header files in your project to use the library functions. 
Here is a brief overview of the available functions:

Running Mean
```C
inline void rstats_mean(double x, double w, double *buffer);
inline void rstats_mean_finalize(double *mean, double *buffer);
```

Running Variance
```C
inline void rstats_variance(double x, double w, double *buffer);
inline void rstats_variance_finalize(double *results, double *buffer);
```

Running Skewness
```C
inline void rstats_skewness(double x, double w, double *buffer);
inline void rstats_skewness_finalize(double *results, double *buffer);
```

Running Kurtosis
```C
inline void rstats_kurtosis(double x, double w, double *buffer);
inline void rstats_kurtosis_finalize(double *results, double *buffer);
```

Central Moments
```C
inline void rstats_central_moment(double x, double w, double *buffer, uint64_t p);
inline void rstats_central_moment_finalize(double *results, double *buffer, uint64_t p, bool standardize);
```

Maximum and Minimum
```C
inline void rstats_max(double x, double *max);
inline void rstats_min(double x, double *min);
```


**Important Note**
All functions for higher moments (e.g., kurtosis) will also compute all lower moments 
(e.g., skewness, variance, and mean) in a single pass. This feature enhances performance 
and reduces computational overhead, making it efficient to obtain all necessary statistical
measures with minimal passes through the data.

**Example Usage in C**
```C
#include <stdio.h>
#include "rstats.h"

int main() {
    double buffer[5] = {0}; // Initialize buffer for mean, variance, skewness, kurtosis
    double data[20] = {5.0, 3.2, 4.1, 2.9, 6.5, 4.3, 5.1, 3.8, 4.6, 2.7, 
                       3.3, 5.7, 4.9, 2.4, 3.6, 5.8, 4.0, 6.2, 3.4, 5.3};
    double w = 1.0;

    // Update statistics with new values
    for (int i = 0; i < 20; ++i) {
        rstats_kurtosis(data[i], w, buffer);  // This will also update mean, variance, and skewness
    }

    // Finalize and get results
    double results[4];
    rstats_kurtosis_finalize(results, buffer);

    printf("Mean: %f\n", results[0]);
    printf("Variance: %f\n", results[1]);
    printf("Skewness: %f\n", results[2]);
    printf("Kurtosis: %f\n", results[3]);

    return 0;
}
```
**Example Usage in C++**
```CXX
#include <iostream> // Use C++ iostream for printing

// Include the C header file with extern "C"
extern "C" {
#include "rstats.h"
}

int main() {
    double buffer[5] = {0}; // Initialize buffer for mean, variance, skewness, kurtosis
    double data[20] = {5.0, 3.2, 4.1, 2.9, 6.5, 4.3, 5.1, 3.8, 4.6, 2.7, 
                       3.3, 5.7, 4.9, 2.4, 3.6, 5.8, 4.0, 6.2, 3.4, 5.3};
    double w = 1.0;

    // Update statistics with new values
    for (int i = 0; i < 20; ++i) {
        rstats_kurtosis(data[i], w, buffer);  // This will also update mean, variance, and skewness
    }

    // Finalize and get results
    double results[4];
    rstats_kurtosis_finalize(results, buffer);

    std::cout << "Mean: " << results[0] << std::endl;
    std::cout << "Variance: " << results[1] << std::endl;
    std::cout << "Skewness: " << results[2] << std::endl;
    std::cout << "Kurtosis: " << results[3] << std::endl;

    return 0;
}
```

## License

This project is licensed under the Apache License, Version 2.0. You may obtain a copy of the License at:

    http://www.apache.org/licenses/LICENSE-2.0

The full text of the license is available in the `LICENSE.txt` file in this repository.
