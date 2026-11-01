#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Structure for passing multiple arguments
typedef struct {
    int a;
    int b;
} ThreadArgs;

// Thread function
void* compute_sum(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;  // Cast to correct type
    int sum = args->a + args->b;

    printf("[Thread] Received a = %d, b = %d, sum = %d\n", args->a, args->b, sum);

    // Allocate memory for return value
    int* result = malloc(sizeof(int));
    *result = sum;

    // Return pointer to result
    pthread_exit((void*) result);
}

int main() {
    pthread_t thread;
    ThreadArgs args;
    args.a = 10;
    args.b = 25;

    // Create the thread and pass the arguments
    if (pthread_create(&thread, NULL, compute_sum, &args) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and get its return value
    int* ret_val;
    if (pthread_join(thread, (void**) &ret_val) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    printf("[Main] Thread returned sum = %d\n", *ret_val);

    // Free the memory allocated in the thread
    free(ret_val);

    printf("[Main] Done.\n");
    return 0;
}
