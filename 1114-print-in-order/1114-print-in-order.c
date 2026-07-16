#include <pthread.h>
#include <stdlib.h>

// Explicitly declare the hidden LeetCode helper functions to fix the compiler error
extern void printFirst();
extern void printSecond();
extern void printThird();

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int turn;
} Foo;

Foo* fooCreate() {
    Foo* obj = (Foo*)malloc(sizeof(Foo));
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);
    obj->turn = 1; 
    return obj;
}

void first(Foo* obj) {
    pthread_mutex_lock(&obj->mutex);
    
    printFirst();
    
    obj->turn = 2; 
    pthread_cond_broadcast(&obj->cond); 
    
    pthread_mutex_unlock(&obj->mutex);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->mutex);
    
    while (obj->turn != 2) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    
    printSecond();
    
    obj->turn = 3; 
    pthread_cond_broadcast(&obj->cond); 
    
    pthread_mutex_unlock(&obj->mutex);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->mutex);
    
    while (obj->turn != 3) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    
    printThird();
    
    pthread_mutex_unlock(&obj->mutex);
}

void fooFree(Foo* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}