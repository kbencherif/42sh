/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** iterator prototype
*/

#ifndef PROTOTYPE
#define PROTOTYPE
#include <stdlib.h>
#include <stdbool.h>

#define define_prototype(type) \
    \
    struct iter_##type; \
    \
    typedef struct iter_elem_##type \
{ \
    type *data; \
    struct iter_elem_##type *next; \
} iter_elem_##type; \
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
bool iter_is_empty_##type(const Iter_##type *iter); \
size_t iter_len_##type(const Iter_##type *iter); \
void iter_push_front_##type(Iter_##type *iter, type *elem); \
void iter_push_to_end_##type(Iter_##type *iter, type *elem); \
void iter_reset_##type(Iter_##type *iter); \
type *iter_next_##type(Iter_##type *iter); \
void iter_map_##type(Iter_##type *iter, void (*mapped_func) \
        (Iter_##type *iter)); \
void iter_delete_##type(Iter_##type *iter, type *elem_data) \
\

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
