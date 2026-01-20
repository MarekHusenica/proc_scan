#include "d_linked_list.h"
#include <stdlib.h>

struct node {
    void *item;
    node_t *next;
    node_t *prev;
};

struct linked_list {
    node_t *first;
    node_t *last;
    node_t *active;
};

linked_list_t linked_list_init() {
    linked_list_t list = {NULL, NULL, NULL};
    return list;
}

void linked_list_free(linked_list_t *l_list) {
    if (linked_set_active_first(l_list)) return;

    node_t *active_node;
    while ((active_node = linked_get_active(l_list)) != NULL) {
        linked_set_active(l_list, active_node->next);
        free(active_node->item);
        active_node->item = NULL;
        free(active_node);
        active_node = NULL;
    }

    l_list->first = NULL;
    l_list->last = NULL;
    l_list->active = NULL;
}

node_t *linked_get_first(linked_list_t *l_list) {
    return l_list->first;
}
node_t *linked_get_last(linked_list_t *l_list) {
    return l_list->last;
}
node_t *linked_get_active(linked_list_t *l_list) {
    return l_list->active;
}
node_t *linked_get_after_active(linked_list_t *l_list) {
    return l_list->active->next;
}
node_t *linked_get_before_active(linked_list_t *l_list) {
    return l_list->active->prev;
}

int linked_insert_first(linked_list_t *l_list, void *item) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->prev = NULL;

    if (!(new_node->next = linked_get_first(l_list)))
        l_list->last = new_node;

    l_list->first = new_node;
}
int linked_insert_last(linked_list_t *l_list, void *item) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->next = NULL;

    if (!(new_node->prev = linked_get_first(l_list)))
        l_list->first = new_node;
    
    l_list->last = new_node;
}
int linked_insert_after_active(linked_list_t *l_list, void *item) {
    node_t *new_node = malloc(sizeof(node_t));
}
int linked_insert_before_active(linked_list_t *l_list, void *item);

