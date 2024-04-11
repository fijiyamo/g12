#include <stdio.h>
#include <pthread.h>

int count = 100000;

pthread_mutex_t change_lock = PTHREAD_MUTEX_INITIALIZER;
void* change() {
    for (int i = 0; i < 10000; i++) {
	pthread_mutex_lock(&change_lock);
        count = count - 1;
	pthread_mutex_unlock(&change_lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[10];
    
    printf("Счетчик равен %i\n", count);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, change, NULL);
    }

    void *result;

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], &result);
    }

    printf("Счетчик равен %i\n", count);
    
    return 0;
}
