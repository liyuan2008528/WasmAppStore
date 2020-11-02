#ifndef __LIBC_HM_IO_H_
#define __LIBC_HM_IO_H_

#include <stdint.h>

int putchar(int c);

int getchar(void);

int puts(const char *s);
char *gets(char *s);

int printf(const char *format, ...);

#endif /* __LIBC_HM_IO_H_ */
