#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

static const char *encryptName = "./encrypted.dat";
static const char *decryptName = "./decrypted.so";

#define BUFFER_SIZE 128
static uint8_t buffer[BUFFER_SIZE] = {0};

void encrypt() {
    remove(encryptName);
    FILE *lib = fopen("libEncrypt.so", "rb");
    FILE *ery = fopen(encryptName, "ab");

    int size = BUFFER_SIZE;
    while (size == BUFFER_SIZE) {
        // get the lib data
        size = fread(buffer, 1, BUFFER_SIZE, lib);
        printf("%d\n", size);
        // stupid encryption
        for(int i = 0; i < size; ++i) {
            ++buffer[i];
        }
        // set the encrypt data
        fwrite(buffer, 1, size, ery);
    }

    fclose(lib);
    fclose(ery);
}
void decrypt() {
    FILE *ery = fopen(encryptName, "rb");
    FILE *dry = fopen(decryptName, "ab");

    int size = BUFFER_SIZE;
    while (size == BUFFER_SIZE) {
        // get the lib data
        size = fread(buffer, 1, BUFFER_SIZE, ery);
        printf("%d\n", size);
        // stupid encryption
        for(int i = 0; i < size; ++i) {
            --buffer[i];
        }
        // set the encrypt data
        fwrite(buffer, 1, size, dry);
    }

    fclose(ery);
    fclose(dry);
}

int main(int argc, char **argv) {
    if(argc <= 1) return -1;

    if(*argv[1] == 'e') {       // ENCRYPT
        encrypt();
        printf("-- ENCRYPTED\n");
    }else if(*argv[1] == 'd') { // DECRYPT
        decrypt();
        printf("-- DECRYPTED\n");

        void *handle = dlopen(decryptName, RTLD_LAZY);
        const char *dlsym_error = dlerror();
        if (!handle) {
            fprintf(stderr, "Cannot load library: %s\n", dlsym_error);
            return 1;
        }
        remove(decryptName);

        void (*hello)() = dlsym(handle, "hello");
        dlsym_error = dlerror();
        if (dlsym_error) {
            fprintf(stderr, "Cannot load symbol 'hello': %s\n", dlsym_error);
            dlclose(handle);
            return 1;
        }

        hello();

        dlclose(handle);
    }else return -1;
    return 0;
}