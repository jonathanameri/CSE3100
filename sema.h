#ifndef __SEMA_H
#define __SEMA_H

#include <pthread.h>
#include <errno.h>

typedef struct pthread_sema {
   // TODO
} pthread_sema_t;

int pthread_sema_init(pthread_sema_t* sem,unsigned int v);
int pthread_sema_destroy(pthread_sema_t* sem);
int pthread_sema_post(pthread_sema_t* sem);
int pthread_sema_wait(pthread_sema_t* sem);

#endif
