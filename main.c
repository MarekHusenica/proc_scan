#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

#include <string.h>
#include <ctype.h>


int main() {

    DIR *proc_dir = opendir("/proc");

    while (proc_dir) {
        errno = 0;
        struct dirent *proc_entry;
        if ((proc_entry = readdir(proc_dir)) != NULL) {

            int has_non_digit = 0;
            for (size_t i = 0; i < strlen(proc_entry->d_name); i++) {
                if (!isdigit(proc_entry->d_name[i])) {
                    has_non_digit = 1;
                    break;
                }
            }
            if (has_non_digit) continue;

            
        }
    }
}