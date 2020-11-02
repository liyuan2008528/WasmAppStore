#ifndef __THREAD_TYPES_H__
#define __THREAD_TYPES_H__

#include <stdint.h>

typedef uint64_t cref_t;
typedef struct {
	cref_t thread;
	void *stack;
} hm_thread;

#endif
