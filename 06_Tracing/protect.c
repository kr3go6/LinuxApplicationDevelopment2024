#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>

#define UNLINK "unlink"

static const char *needle = "PROTECT";

int unlink(const char *filename) {
    if (strstr(filename, needle)) {
        return 0;
    }

    if (!dlsym(RTLD_NEXT, UNLINK)) {
        return -1;
    }

    int (*_unlink)(const char *) = dlsym(RTLD_NEXT, UNLINK);
    return _unlink(filename);
}
