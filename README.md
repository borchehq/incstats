# librstats

**librstats** is a C library for efficiently computing running statistics, such as mean, variance, skewness, kurtosis, central moments, and finding the maximum and minimum values in a dataset. The library is designed to handle weighted data points, making it suitable for a wide range of applications.

## Features

- Compute running mean, variance, skewness, and kurtosis.
- Calculate central moments up to a specified order.
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