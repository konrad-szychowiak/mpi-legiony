//
// Created by konrad on 21.05.22.
//

#pragma once

#ifndef LEGIONY_PTHREAD_HXX
#define LEGIONY_PTHREAD_HXX

#include <csignal>

#define lock(sem) pthread_mutex_lock(sem)
#define unlock(sem) pthread_mutex_unlock(sem)

#define wait pthread_cond_wait
#define signal pthread_cond_signal
#define broadcast pthread_cond_broadcast

typedef pthread_cond_t Cond;
typedef pthread_mutex_t Mutex;
typedef pthread_t Thread;

#endif //LEGIONY_PTHREAD_HXX
