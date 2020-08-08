#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/mount.h>

// #define NAMESPACE "my_namespace"
// #define BINARY "/usr/bin/bash"

int main(int argc, char* argv[], char* envp[]) {
    // Set Namespace
    int NS = openat(AT_FDCWD, "/var/run/netns/" NAMESPACE, O_RDONLY|O_CLOEXEC);
    int err;
    if (err = setns(NS, CLONE_NEWNET) != 0) {
        fprintf(stderr, "setns failed: %d\n", err);
        return err;
    }
    if (err = close(NS) != 0) {
        fprintf(stderr, "close failed: %d\n", err);
        return err;
    }

    // Drop suid
    if (getuid() != geteuid()) {
        if (setuid(getuid()) != 0) {
            fprintf(stderr, "setuid failed: %d\n", err);
            return err;
        }
    }
    if (getgid() != getegid()) {
        if (setgid(getgid()) != 0) {
            fprintf(stderr, "setgid failed: %d\n", err);
            return err;
        }
    }

    // Exec compiled binary with args and environment of this executable
    argv[0] = BINARY;
    if (err = execve(BINARY, argv, envp) != 0) {
        fprintf(stderr, "execve failed: %d", err);
        return err;
    }
}