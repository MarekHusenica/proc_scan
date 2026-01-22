#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <string.h>
#include <ctype.h>

#include <d_linked_list.h>

typedef struct process {
    char pid[16];
    char name[64];
} proc_t;


int main() {

    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        fprintf(stderr, "Failed to \"proc\" directory\n");
        closedir(proc_dir);
        return 1;
    }

    linked_list_t l_list = linked_list_init();
    
    struct dirent *proc_entry;
    do {
        if ((proc_entry = readdir(proc_dir)) != NULL) {

            int has_non_digit = 0;
            for (size_t i = 0; i < strlen(proc_entry->d_name); i++) {
                if (!isdigit(proc_entry->d_name[i])) {
                    has_non_digit = 1;
                    break;
                }
            }
            if (has_non_digit) continue;

            proc_t *proc = malloc(sizeof(proc_t));
            if (!proc) {
                printf("Couldn't allocate memory for process: %s\n", proc_entry->d_name);
                continue;
            }

            strncpy(proc->pid, proc_entry->d_name, 16);

            char f_path_buff[292];
            snprintf(f_path_buff, 292, "/proc/%s/comm", proc_entry->d_name);

            FILE *comm_file = fopen(f_path_buff, "r");
            if (!comm_file) {
                fprintf(stderr, "Couldn't open comm file for PID: %s\n", proc_entry->d_name);
                free(proc);
                continue;
            }
            fgets(proc->name, 64, comm_file);
            fclose(comm_file);

            size_t name_len = strlen(proc->name);
            if (proc->name[name_len - 1] == '\n')
                proc->name[name_len - 1] = '\0';

            linked_insert_last(&l_list, proc);
        }
    } while (proc_entry);

    closedir(proc_dir);

    printf("PID      name\n\n");

    while (linked_set_active_first(&l_list)) {
        node_t *active_node = linked_get_active(&l_list);
        proc_t *proc = active_node->item;
        printf("%-8s %-32s\n", proc->pid, proc->name);

        free(proc);
        linked_delete_active(&l_list);
    }
    linked_list_free(&l_list);
}