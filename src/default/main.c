#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // Include for dynamic loading

int main() {
    // Load the dynamic library
    void *handle = dlopen("./liblibDefault.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Cannot load library: %s\n", dlerror());
        return 1;
    }

    // Clear any existing errors
    dlerror();

    // Load the symbol (function) from the library
    void (*hello)() = dlsym(handle, "hello");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        fprintf(stderr, "Cannot load symbol 'hello': %s\n", dlsym_error);
        dlclose(handle);
        return 1;
    }

    // Call the function
    hello();

    // Close the library
    dlclose(handle);
    return 0;
}