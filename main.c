#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>


#define INITIAL_SIZE 64


int main() {

    DIR *proc_dir = opendir("/proc");
    struct dirent **entries = malloc(sizeof(struct dirent) * INITIAL_SIZE);

    while (proc_dir) {
        errno = 0;
        struct dirent *proc_entry;
        if ((proc_entry = readdir(proc_dir)) != NULL) {
            if (isdigit)

        }
    }
}