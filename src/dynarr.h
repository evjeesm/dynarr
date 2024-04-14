#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h> /* bool, true, false */
#include <stddef.h>  /* size_t */
#include <sys/types.h> /* ssize_t */

#include "vector.h"

typedef enum dynarr_error_t
{
    ERR
}
dynarr_error_t;

typedef struct vector_t dynarr_t;

typedef struct dynarr_opts_t
{
    size_t element_size; /* size of the element */
    size_t initial_cap;
    float grow_factor;
    float grow_threshold;
    float shrink_threshold;
}
dynarr_opts_t;


/*
* The wrapper for `dynarr_create_` function that provides default values.
*/
#define dynarr_create(dynarr_p, ...) {\
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"") \
    dynarr_create_(&dynarr_p, &(dynarr_opts_t){ \
        .element_size = sizeof(int), \
        .initial_cap = 10, \
        .shrink_threshold = 0.25f, \
        .grow_threshold = 0.75f, \
        .grow_factor = 1.5f, \
        __VA_ARGS__ \
    }); \
    _Pragma("GCC diagnostic pop") \
}


/*
* Dynamic array constructor function that initializes array
* with properties packed in opts struct.
* Space for `initial_cap` elements will be reserved.
* Array will not be able to shrink below `initial_cap`.
* In case of allocation fail null pointer will be returned.
*/
void dynarr_create_(dynarr_t **const dynarr, const dynarr_opts_t *const opts);


/*
* Makes a copy of the whole array.
*/
dynarr_t *dynarr_clone(const dynarr_t *const dynarr);


/*
* Deallocates dynamic array. After the call pointer will be invalidated.
*/
void dynarr_destroy(dynarr_t *const dynarr);


/*
* Removes all of the elements of the vector. But not performs any grow/shrink operations.
*/
void dynarr_clear(dynarr_t *const dynarr);


/*
* Reports current amount of elements containing within the vector.
*/
size_t dynarr_size(const dynarr_t *const dynarr);


/*
* Reports current capacity of the vector.
*/
size_t dynarr_capacity(const dynarr_t *const dynarr);


/*
* Returns pointer for the element at `index`.
*/
void *dynarr_get(const dynarr_t *const dynarr, const size_t index);


/*
* sets element at given `index` to a `value`.
*/
void dynarr_set(dynarr_t *const dynarr, const size_t index, const void *value);


/*
* Sets element at given `index` to a zero value.
*/
void dynarr_set_zero(dynarr_t *const dynarr, const size_t index);


/*
* Returns pointer for the first element in the array,
* assuming that array contains at least one element.
*/
void *dynarr_first(const dynarr_t *const dynarr);


/*
* Returns pointer for the last element in the array,
* assuming that array contains at least one element.
*/
void *dynarr_last(const dynarr_t *const dynarr);


/*
* Appends element at array's tail, growing on demand.
*/
bool dynarr_append(dynarr_t **const dynarr, const void *const value);


/*
* Appends element at array's head by shifting one element forward
* and growing vector on demand.
*/
bool dynarr_prepend(dynarr_t **const dynarr, const void *const value);


/*
* Removes element from the back, shrinking array on demand.
*/
void dynarr_pop_back(dynarr_t **const dynarr);


/*
* Removes element from the head by shifting one element to the left
* and shrinking array on demand.
*/
void dynarr_pop_front(dynarr_t **const dynarr);


/*
* Inserts new element at given `index`, shifting one element forward
* from that index.
*/
bool dynarr_insert(dynarr_t **const dynarr, const size_t index, const void *value);


/*
* Removes element at given `index`.
*/
void dynarr_remove(dynarr_t **const dynarr, const size_t index);


/*
* Removes range of elements of `amount` length at given `index`.
*/
void dynarr_remove_range(dynarr_t **const dynarr, const size_t index, const size_t amount);


/*
* Inserts range of `value` copies `amount` times at specific `index`.
*/
bool dynarr_spread_insert(dynarr_t **const dynarr, const size_t index, const size_t amount, const void *const value);


/*
* Binary insert. Works only if previous elements
* that contained in the vector are ordered in same way.
* (Allocation may fail, so returning operation status)
*/
bool dynarr_binary_insert(dynarr_t **const dynarr, const void *value, const compare_t cmp, void *param, size_t *const index);



#if 0
/*
* Checks whenever the vector contains a value via byte to byte comparison.
*/
bool vector_contains(const vector_t *vector, const void *value);


/*
* Linear search for a value in the vector with parametrized predicate.
* If no matching element found returns null pointer,
* otherwise pointer to a legit location in vector's memory span.
*/
void *vector_find(const vector_t *vector, const void *value, predicate_t predicate, void *param);


/*
* Binary search for a value in the vector with parametrized compare function.
* If no matching element found returns null pointer,
* otherwise pointer to a legit location in vector's memory span.
*/
void *vector_binary_find(const vector_t *vector, compare_t cmp, const void *value, void *param);



/*
* Reverse order of elements in the vector 
*/
bool vector_reverse(vector_t **vector);
#endif

#endif/*_DYNARR_H_*/
