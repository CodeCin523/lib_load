#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <assert.h>

struct tech {
    const char * name;
    void (*fInit)();
    int  (*fInc )();
    void (*fExit)();
};

int main(int argc, char **argv) {
    void *handle = dlopen("./liblibMultiApp.so", RTLD_LAZY);
    if(!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    struct tech ths[3];
    // MEMORY MAPPING
    ths[0].name = "Memory Mapping";
    ths[0].fInit = dlsym(handle, "mman_init");
    ths[0].fInc  = dlsym(handle, "mman_inc");
    ths[0].fExit = dlsym(handle, "mman_exit");

    assert( ths[0].name  != NULL &&
            ths[0].fInit != NULL &&
            ths[0].fInc  != NULL &&
            ths[0].fExit != NULL);
    // MEMORY SHARING
    ths[1].name = "Memory Sharing";
    ths[1].fInit = dlsym(handle, "shm_init");
    ths[1].fInc  = dlsym(handle, "shm_inc");
    ths[1].fExit = dlsym(handle, "shm_exit");

    assert( ths[1].name  != NULL &&
            ths[1].fInit != NULL &&
            ths[1].fInc  != NULL &&
            ths[1].fExit != NULL);
    // PIPES
    ths[2].name = "Pipe";
    ths[2].fInit = dlsym(handle, "pipe_init");
    ths[2].fInc  = dlsym(handle, "pipe_inc");
    ths[2].fExit = dlsym(handle, "pipe_exit");

    assert( ths[2].name  != NULL &&
            ths[2].fInit != NULL &&
            ths[2].fInc  != NULL &&
            ths[2].fExit != NULL);

    for(int i = 0; i < 3; ++i) {
        ths[i].fInit();
    }

    int pid = fork();

    for(int i = 0; i < 3; ++i) {
    if(pid == 0) {
        sleep(1);
        printf("[%s] child value is : %d\n", ths[i].name, ths[i].fInc());
    } else {
        printf("[%s] parent value is : %d\n", ths[i].name, ths[i].fInc());
        sleep(2);
    
    }
    }

    for(int i = 0; i < 3; ++i)
        ths[i].fExit();


    dlclose(handle);
    return 0;
}