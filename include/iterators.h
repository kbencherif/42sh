/*
** EPITECH PROJECT, 2019
** navy
** File description:
** player info include file
*/

#ifndef ITERATOR_H_
#define ITERATOR_H_
#include <stdlib.h>
#include <stdbool.h>

#define define_iter(type) \
\
typedef struct iter_elem_##type \
{ \
    type *data; \
    struct iter_elem_##type *next; \
} iter_elem_##type; \
\
struct iter_##type; \
\
typedef struct \
{ \
    bool (*is_empty)(const struct iter_##type *); \
    size_t (*len)(const struct iter_##type *); \
    void (*push_front)(struct iter_##type *, type *); \
    void (*push_to_end)(struct iter_##type *, type *); \
    void (*reset)(struct iter_##type *); \
    type *(*next)(struct iter_##type *); \
    void (*map)(struct iter_##type *, void (*mapped_func) \
            (struct iter_##type *)); \
    void (*delete)(struct iter_##type *, type *); \
} iter_functions_##type; \
\
typedef struct iter_##type \
{ \
    size_t len; \
    size_t elem_nb; \
    iter_elem_##type *first; \
    iter_elem_##type *elem; \
    iter_functions_##type *functions; \
} Iter_##type; \
\
Iter_##type *new_iter_##type(); \
bool Iter_is_empty_##type(const Iter_##type *iter); \
size_t Iter_len_##type(const Iter_##type *iter); \
void Iter_push_front_##type(Iter_##type *iter, type *elem); \
void Iter_push_to_end_##type(Iter_##type *iter, type *elem); \
void Iter_reset_##type(Iter_##type *iter); \
type *Iter_next_##type(Iter_##type *iter); \
void Iter_map_##type(Iter_##type *iter, void (*mapped_func) \
        (Iter_##type *iter)); \
void iter_delete_##type(Iter_##type *iter, type *elem_data); \
\
bool iter_is_empty_##type(const Iter_##type *iter) \
{ \
    return iter->len == 0; \
} \
\
size_t iter_len_##type(const Iter_##type *iter) \
{ \
    return iter->len; \
} \
\
void iter_push_front_##type(Iter_##type *iter, type *elem) \
{ \
    iter_elem_##type *element = (iter_elem_##type *) \
    malloc(sizeof(iter_elem_##type)); \
    if (iter->elem == NULL) { \
        iter->first = element; \
        iter->elem = element; \
        element->data = elem; \
        element->next = NULL; \
    } else { \
        element->data = elem; \
        element->next = iter->elem; \
        iter->elem = element; \
        iter->first = element; \
    } \
    iter->len++; \
} \
\
void iter_push_to_end_##type(Iter_##type *iter, type *elem) \
{ \
    iter_elem_##type *element = (iter_elem_##type *) \
    malloc(sizeof(iter_elem_##type)); \
    iter_elem_##type *tmp = iter->elem; \
    \
    if (iter->elem == NULL) { \
        iter->first = element; \
        iter->elem = element; \
        element->data = elem; \
        element->next = NULL; \
    } else { \
        element->data = elem; \
        element->next = NULL; \
        while (tmp->next != NULL) \
        tmp = tmp->next; \
        tmp->next = element; \
    } \
    iter->len++; \
} \
void iter_reset_##type(Iter_##type *iter) \
{ \
    iter->elem = iter->first; \
    iter->elem_nb = 0; \
} \
type *iter_next_##type(Iter_##type *iter) \
{ \
    type *data = NULL; \
    \
    if (iter->elem) { \
        data = iter->elem->data; \
        iter->elem = iter->elem->next; \
    } else \
        iter->elem = iter->first; \
    iter->elem_nb++; \
    return data; \
} \
void iter_map_##type(Iter_##type *iter, void (*mapped_func) \
        (Iter_##type *iter)) \
{ \
    Iter_##type tmp = *iter; \
    \
    while (iter->elem) { \
        (*mapped_func)(iter); \
        next(iter); \
    } \
    *iter = tmp; \
} \
void iter_delete_##type(Iter_##type *iter, type *elem_data) \
{ \
    iter_elem_##type *tmp = NULL; \
\
    iter_reset_##type(iter); \
    if (iter->elem->data == elem_data) { \
        iter->elem = iter->elem->next; \
        iter->first = iter->first->next; \
        return; \
    } \
    while (iter->elem && iter->elem->next->data != elem_data) \
        iter_next_##type(iter); \
    if (!iter->elem) \
        return; \
    tmp = iter->elem->next->next; \
    free(iter->elem->next); \
    iter->elem->next = tmp;\
    iter->len--; \
} \
iter_functions_##type iter_funcs_##type = { \
    &iter_is_empty_##type, \
    &iter_len_##type, \
    &iter_push_front_##type, \
    &iter_push_to_end_##type, \
    &iter_reset_##type, \
    &iter_next_##type, \
    &iter_map_##type, \
    &iter_delete_##type, \
}; \
\
Iter_##type *new_iter_##type() \
{ \
    Iter_##type *res = (Iter_##type *) malloc(sizeof(Iter_##type)); \
    res->len = 0; \
    res->elem_nb = 0; \
    res->elem = NULL; \
    res->first = NULL; \
    res->functions = &iter_funcs_##type; \
    return res; \
}

#define Iter(type) \
    Iter_##type

#define new_iter(type) \
    new_iter_##type()

#define is_empty(collection) \
    collection->functions->is_empty(collection)

#define len(collection) \
    collection->functions->len(collection)

#define push_front(collection, elem) \
    collection->functions->push_front(collection, elem)

#define push_to_end(collection, elem) \
    collection->functions->push_to_end(collection, elem)

#define next(collection) \
    collection->functions->next(collection)

#define map(collection, function) \
    collection->functions->map(collection, function)

#define delete(collection, data) \
    collection->functions->delete(collection, data)

#define reset(collection) \
    collection->functions->reset(collection)

#endif
