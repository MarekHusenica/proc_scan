#ifndef D_LINKED_LIST_H
#define D_LINKED_LIST_H

typedef struct node node_t;

struct node {
    void *item;
    struct node *next;
    struct node *prev;
};

typedef struct linked_list {
    node_t *first;
    node_t *last;
    node_t *active;
} linked_list_t;

linked_list_t linked_list_init();
void linked_list_free(linked_list_t *l_list);

node_t *linked_get_first(linked_list_t *l_list);
node_t *linked_get_last(linked_list_t *l_list);
node_t *linked_get_active(linked_list_t *l_list);

int linked_insert_first(linked_list_t *l_list, void *item);
int linked_insert_last(linked_list_t *l_list, void *item);
int linked_insert_after_active(linked_list_t *l_list, void *item);
int linked_insert_before_active(linked_list_t *l_list, void *item);

int linked_delete_first(linked_list_t *l_list);
int linked_delete_last(linked_list_t *l_list);
int linked_delete_active(linked_list_t *l_list);

int linked_set_active_next(linked_list_t *l_list);
int linked_set_active_prev(linked_list_t *l_list);
int linked_set_active_first(linked_list_t *l_list);
int linked_set_active_last(linked_list_t *l_list);



#endif