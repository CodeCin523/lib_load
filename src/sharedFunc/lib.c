// mylib.c
#include <stdio.h>
#include <dlfcn.h>

void lib_hello() {
    printf("Hello from lib\n");

    // Access the main program's function
    void (*main_function)() = dlsym(RTLD_DEFAULT, "app_hello");
    if (main_function) {
        main_function(); // Call the main program's function
    } else {
        fprintf(stderr, "Could not find app_hello: %s\n", dlerror());
    }
}