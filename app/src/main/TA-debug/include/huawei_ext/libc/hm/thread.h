#ifndef __LIBC_HM_THREAD_H__
#define __LIBC_HM_THREAD_H__

#include <stddef.h>
#include "hm/threadtypes.h"

// errno.h is confilict with system errno.h.
// after rework the errno, this should be remove
#ifndef EBUSY
#define EBUSY 16
#endif

#ifndef EDEADLK
#define EDEADLK 35
#endif

#ifndef EPERM
# define EPERM 1
#endif

// Hongmeng thread
int set_thread_priority(cref_t thread, int priority);
unsigned long thread_tid();

#endif
