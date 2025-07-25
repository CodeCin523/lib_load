#include <stdio.h>
#include <dlfcn.h>

void __attribute__((noinline, visibility("default"))) app_hello() {
    printf("Hello from app\n");
}

int main() {
    // Access the main program's function
    void (*main_function)() = dlsym(RTLD_DEFAULT, "app_hello");
    if (main_function) {
        main_function(); // Call the main program's function
    } else {
        fprintf(stderr, "Could not find app_hello: %s\n", dlerror());
    }

    // Load the shared library
    void *handle = dlopen("./liblibSharedFunc.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Call a function in the shared library
    void (*lib_function)() = dlsym(handle, "lib_hello");
    if (lib_function) {
        lib_function();
    }

    dlclose(handle);

    return 0;
}