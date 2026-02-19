#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker_thread(void* arg) {
    printf("Worker thread is running...\n");
    sleep(75); 
    return NULL;
}

int main() {
    pthread_t thread_id;

    printf("Main thread (PID: %d) create worker...\n", getpid());
    
    if (pthread_create(&thread_id, NULL, worker_thread, NULL) != 0) {
        perror("Error thread creating, returning 1");
        return 1;
    }

    printf("Main thread is waiting for worker...\n");
    pthread_join(thread_id, NULL);

    printf("Program closed.\n");
    return 0;
}
