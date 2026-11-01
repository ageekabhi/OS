#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function 1
void* thread_func1(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread 1 Started, thread ID: %lu\n", tid);

    for (int i = 0; i < 5; i++) {
        printf("Thread 1 Working... %d\n", i + 1);
        sleep(1);
    }

    printf("Thread 1 Finished work.\n");
    return NULL;
}

// Thread function 2
void* thread_func2(void* arg) {
    printf("Thread 2 Waiting to be canceled...\n");
    for (int i = 0; i < 10; i++) {
        printf("Thread 2 Running... %d\n", i + 1);
        sleep(1);

        // Explicitly check if cancel was requested
        pthread_testcancel();
    }

    printf("Thread 2 Exiting normally (won’t reach here if canceled).\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr;

    // Initialize and set attributes
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // or PTHREAD_CREATE_DETACHED

    // Create first thread with attributes
    if (pthread_create(&t1, &attr, thread_func1, NULL) != 0) {
        perror("Failed to create thread 1");
        exit(1);
    }

    // Create second thread normally
    if (pthread_create(&t2, NULL, thread_func2, NULL) != 0) {
        perror("Failed to create thread 2");
        exit(1);
    }

    pthread_detach(t1);
    printf("[Main] Detached thread 1.\n");

    sleep(3);
    printf("[Main] Canceling thread 2...\n");
    pthread_cancel(t2);

    void* res;
    pthread_join(t2, &res);
    if (res == PTHREAD_CANCELED)
        printf("[Main] Thread 2 was canceled successfully.\n");
    else
        printf("[Main] Thread 2 exited normally.\n");

    pthread_attr_destroy(&attr);

    printf("[Main] All done!\n");
    return 0;
}
