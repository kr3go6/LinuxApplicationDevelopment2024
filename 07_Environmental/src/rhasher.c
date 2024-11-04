#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "config.h"
#include "rhash.h"

#ifdef LREADLINE_ENABLE
#include <readline/readline.h>
#endif


#define MD5 "MD5"
#define SHA1 "SHA1"
#define TTH "TTH"

int SupportedHash(const char *algorithm) {
    if (strncasecmp(algorithm, MD5, sizeof(MD5)) == 0) {
        return RHASH_MD5;
    }

    if (strncasecmp(algorithm, SHA1, sizeof(SHA1)) == 0) {
        return RHASH_SHA1;
    }
    
    if (strncasecmp(algorithm, TTH, sizeof(TTH)) == 0) {
        return RHASH_TTH;
    }

    return 0;
}

int main(int /*argc*/, char **/*argv*/) {
    char *command = NULL;

    printf("> ");

    unsigned char digest[64];
    char output[130];

    rhash_library_init();

#ifdef LREADLINE_ENABLE
    while (command = (char *)readline(NULL), command != NULL) {
#else
    long unsigned len = 0;

    while (getline(&command, &len, stdin) != -1) {
#endif
        char *hash_algorithm = strtok(command, " ");

        if (hash_algorithm == NULL || !SupportedHash(hash_algorithm)) {
            fprintf(stderr, "Неопознанная команда: %s\n", hash_algorithm);
            printf("> ");
            continue;
        }

        char *arg = strtok(NULL, " ");

        if (arg == NULL) {
            fprintf(stderr, "Отсутствует второй параметр: %s\n", hash_algorithm);
            printf("> ");
            continue;
        }

        int hash = SupportedHash(hash_algorithm);

        int res;

        #ifdef LREADLINE_ENABLE
        #else
            if (arg[strlen(arg) - 1] == '\n') {
                arg[strlen(arg) - 1] = 0;
            }
        #endif
        
        if (arg[0] == '"') {
            arg++;
            res = rhash_msg(hash, arg, strlen(arg), digest);
        } else {
            res = rhash_file(hash, arg, digest);
        }

        if (res < 0) {
            fprintf(stderr, "LibRHash error: %s\n", strerror(errno));
            printf("> ");
            continue;
        }

        int repr = isupper(hash_algorithm[0]) ? RHPR_HEX : RHPR_BASE64;

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash), repr);
        printf("%s\n> ", output);
    }

    free(command);
    return 0;
}
