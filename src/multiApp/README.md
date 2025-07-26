# Multiple Application, Shared Memory

This subdirectory explores how a shared library can enable two applications to access and manipulate the same memory space. Specifically, it investigates how a library can share data across different instances, allowing multiple programs to work with the same data seamlessly.

## How Can two Application Share Variables That the Library Uses?

Three methods have been tested to share data between applications via a library. Each approach has its strengths and limitations:

1. **Memory Mapping**
   Using `mmap` with the `MAP_SHARED` flag, a memory page can be allocated and shared between a parent and child process created via `fork`. This allows both processes to read from and write to the same memory region efficiently.
   - **Strengths**: Simple to implement for parent-child processes; provides direct memory access with low overhead.
   - **Weaknesses**: Limited to processes spawned from the same parent, making it unsuitable for unrelated applications.
   - **Status**: Basic implementation tested;

2. **Memory Sharing**
   Using System V shared memory (`sys/shm.h`), a memory segment is created with a unique key, allowing multiple processes (even unrelated ones) to access the same data. This approach enables the library to share its contents without requiring a `fork`.
   - **Strengths**: Flexible for sharing data across independent processes; no need for a parent-child relationship.
   - **Weaknesses**: Requires careful management of shared memory segments and keys to avoid errors or conflicts.
   - **Status**: Initial tests completed; further exploration needed.

3. **Pipes**
   Pipes provide a unidirectional communication channel using two file descriptors: one for reading and one for writing. In this test, pipes are used with `fork` to share data between a parent and child process. For unrelated processes, named pipes (`mkfifo`) could be used instead.
   - **Strengths**: Straightforward to implement for basic data transfer between related processes.
   - **Weaknesses**: Current implementation relies on `fork`, limiting its use to parent-child processes; named pipes would require additional setup.
   - **Status**: Basic pipe implementation tested; named pipe exploration possible.

## Application for libraries?

Sharing data between multiple instances of a library can enable scenarios like:
- **Shared Caching**: Multiple applications accessing a common cache to optimize performance.
- **State Synchronization**: Coordinating state across processes, such as in parallel or distributed systems.
- **Data Aggregation**: Collecting data from multiple sources into a shared memory region for processing.

However, the practicality of this approach depends on the use case. Challenges like synchronization (e.g., avoiding race conditions), performance overhead, and security implications need further investigation to determine its viability in real-world library applications.