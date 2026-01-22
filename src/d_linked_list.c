#include "d_linked_list.h"
#include <stdlib.h>

linked_list_t linked_list_init() {
    linked_list_t list = {NULL, NULL, NULL};
    return list;
}

void linked_list_free(linked_list_t *l_list) {
    node_t *curr_node = linked_get_first(l_list);

    while (curr_node != NULL) {
        node_t *next_node = curr_node->next;
        free(curr_node->item);
        free(curr_node);
        curr_node = next_node;
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

int linked_insert_first(linked_list_t *l_list, void *item) {
    if (!l_list || !item) return 0;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return 0;
    new_node->item = item;

    new_node->prev = NULL;

    if (!(new_node->next = linked_get_first(l_list)))
        l_list->last = new_node;
    else
        new_node->next->prev = new_node;

    l_list->first = new_node;

    return 1;
}
int linked_insert_last(linked_list_t *l_list, void *item) {
    if (!l_list || !item) return 0;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return 0;
    new_node->item = item;

    new_node->next = NULL;

    if (!(new_node->prev = linked_get_last(l_list)))
        l_list->first = new_node;
    else
        new_node->prev->next = new_node;

    l_list->last = new_node;
    
    
    return 1;
}
int linked_insert_after_active(linked_list_t *l_list, void *item) {
    node_t *active_node = linked_get_active(l_list);
    if (!active_node || !l_list || !item)
        return 0;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return 0;
    new_node->item = item;

    if (!(new_node->next = active_node->next))
        l_list->last = new_node;
    else 
        new_node->next->prev = new_node;
    new_node->prev = active_node;
    active_node->next = new_node;

    return 1;
}
int linked_insert_before_active(linked_list_t *l_list, void *item) {
    node_t *active_node = linked_get_active(l_list);
    if (!active_node || !l_list || !item) return 0;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return 0;
    new_node->item = item;

    if (!(new_node->prev = active_node->prev))
        l_list->first = new_node;
    else
        new_node->prev->next = new_node;
    new_node->next = active_node;
    active_node->next = new_node;

    return 1;
}

int linked_delete_first(linked_list_t *l_list) {
    if (!l_list || !l_list->first) return 0;

    node_t *to_delete = l_list->first;

    if (to_delete == l_list->active)
        l_list->active = NULL;

    l_list->first = to_delete->next;

    if (l_list->first)
        l_list->first->prev = NULL;
    else 
        l_list->last = NULL;

    free(to_delete);
    to_delete = NULL;

    return 1;
}

int linked_delete_last(linked_list_t *l_list) {
    if (!l_list || !l_list->last) return 0;

    node_t *to_delete = l_list->last;

    if (to_delete == l_list->active)
        l_list->active = NULL;

    l_list->last = to_delete->prev;

    if (l_list->last)
        l_list->last->next = NULL;
    else
        l_list->last = NULL;

    free(to_delete);
    to_delete = NULL;

    return 1;
}

int linked_delete_active(linked_list_t *l_list) {
    if (!l_list || !l_list->active) return 0;

    node_t *to_delete = l_list->active;

    if (to_delete->prev) to_delete->prev->next = to_delete->next;
    else l_list->first = to_delete->next;

    if (to_delete->next) to_delete->next->prev = to_delete->prev;
    else l_list->last = to_delete->prev;

    l_list->active = NULL;
    
    free(to_delete);

    return 1;
}

int linked_set_active_next(linked_list_t *l_list) {
    if (!l_list->active || !l_list->active->next) return 0;
    
    l_list->active = l_list->active->next;
    return 1;
}
int linked_set_active_prev(linked_list_t *l_list) {
    if (!l_list->active || !l_list->active->prev) return 0;

    l_list->active = l_list->active->prev;
    return 1;
}
int linked_set_active_first(linked_list_t *l_list) {
    if (!(l_list->active = linked_get_first(l_list))) return 0;

    return 1;
}
int linked_set_active_last(linked_list_t *l_list) {
    if (!(l_list->active = linked_get_last(l_list))) return 0;

    return 1;
}

