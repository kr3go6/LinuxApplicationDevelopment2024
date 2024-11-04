#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define kExpectedArgc 3
#define kBufferSize 4096

typedef enum {
    _,
    INVALID_ARGC,
    OPEN_FAIL,
    WRITE_FAIL,
    READ_FAIL
} ErrorCodes;

void ResetState(int in_fd, int out_fd, const char *filename) {
    if (in_fd) {
        close(in_fd);
    }

    if (out_fd) {
        close(out_fd);
    }

    if (filename) {
        unlink(filename);
    }
}

int ProcessError(int err, const char *msg, int in_fd, int out_fd, const char *filename) {
    perror(msg);
    ResetState(in_fd, out_fd, filename);
    exit(err);
}

int OpenFile(const char *pathname, int flags, int in_fd) {
    int fd = open(pathname, flags, 0666);

    if (fd < 0) {
        ProcessError(OPEN_FAIL, pathname, in_fd, 0, NULL);
    }

    return fd;
}

void WriteBuf(int out_fd, char *buffer, int bytes_left, int in_fd, const char *outfile) {
    int written_bytes = 0;

    while ((written_bytes = write(out_fd, buffer, bytes_left)) > 0) {
        if (written_bytes == bytes_left) {
            return;
        }

        bytes_left -= written_bytes;
        buffer += written_bytes;
    }

    ProcessError(WRITE_FAIL, "couldn't write to the outfile", in_fd, out_fd, outfile);
}

void MoveFile(int in_fd, int out_fd, const char *outfile) {
    char buffer[kBufferSize];
    int read_bytes;

    while ((read_bytes = read(in_fd, buffer, kBufferSize)) > 0) {
        WriteBuf(out_fd, buffer, read_bytes, in_fd, outfile);
    }

    if (read_bytes < 0) {
        ProcessError(READ_FAIL, "couldn't read from infile", in_fd, out_fd, outfile);
    }
}

int main(int argc, char **argv) {
    if (argc != kExpectedArgc) {
        fprintf(stderr, "Usage: ./move <infile> <outfile>\n");
        exit(INVALID_ARGC);
    }

    const char *infile = argv[1];
    int in_fd = OpenFile(infile, O_RDONLY, 0);

    const char *outfile = argv[2];
    int out_fd = OpenFile(outfile, O_WRONLY | O_TRUNC | O_CREAT, in_fd);

    MoveFile(in_fd, out_fd, outfile);

    ResetState(in_fd, out_fd, infile);
    return 0;
}
