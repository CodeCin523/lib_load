# Lib Load

This repository contains personal tests to explore how dynamic libraries work.

## Building the Project

To build the project, follow these steps:

1. Open a terminal and navigate to the project directory.
2. Run the following command to configure the project with CMake:
    ```bash
    cmake -S . -B _build
    ```
3. Change to the build directory:
    ```bash
    cd _build
    ```
4. Build the project:
    ```bash
    make
    ```

## Note

- The dynamic loading functionality using `dlfcn.h` is only available on Linux systems. Ensure you are using a compatible environment to utilize this feature.