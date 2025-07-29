#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stddef.h>

typedef int (*fcntl_func)(int, int, ...);

int fcntl(int fd, int cmd, ...)
{
    static fcntl_func real_fcntl = NULL;
    if (!real_fcntl) {
        real_fcntl = (fcntl_func)dlsym(RTLD_NEXT, "fcntl");
    }

    va_list args;
    va_start(args, cmd);
    void *arg = va_arg(args, void *);
    va_end(args);

    return real_fcntl(fd, cmd, arg);
}