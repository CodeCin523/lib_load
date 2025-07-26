#include <stddef.h>
#include <stdio.h>


// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// MEMORY MAP
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

// Features
//  - simpler
//  - only this process and its children
//  - need to be done before fork();

#include <sys/ipc.h>
#include <sys/mman.h>

int *mman_dt;

void mman_init() {
    mman_dt = (int *) mmap(
        NULL,
        4,
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );
}
int mman_inc() {
    return (*mman_dt)++;
}
void mman_exit(int _pid) {
    munmap((void *)mman_dt, 4);
}


// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// MEMORY SHARING
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

// Features
//  - lots more customisations
//  - can be attached to files?

#include <sys/shm.h> 
#include <sys/stat.h> 

int shm_id;
int *shm_dt;

void shm_init() {
    const int segment_key = /*1234*/ IPC_PRIVATE;  // can be hard-coded, but not recommended
    shm_id = shmget(
        segment_key,
        4,
        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR
    );

    shm_dt = (int *) shmat(shm_id, NULL, 0);
}
int shm_inc() {
    return (*shm_dt)++;
}
void shm_exit() {
    shmdt((void *)shm_dt);
    shmctl(shm_id, IPC_RMID, 0);
}


// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// PIPES
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

// Features
//  - not really memory sharing.
//  - more input/output of data throw fds.
//  - usable in non-fork environments with named pipes (mkfifo?)
//  - custom implementation with socket?

#include <unistd.h>

int pipe_fd[2];

void pipe_init() {
    pipe(pipe_fd);
    int i = 0;
    write(pipe_fd[1], &i, 4);
}
int pipe_inc() {
    int i = 0;
    read(pipe_fd[0], &i, 4);
    ++i;
    write(pipe_fd[1], &i, 4);
    return i;
}
void pipe_exit() {
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

