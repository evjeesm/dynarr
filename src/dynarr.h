#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h> /* bool, true, false */
#include <stddef.h>  /* size_t */
#include <sys/types.h> /* ssize_t */

#include "vector.h"

#define DYNARR_DEFAULT_ERROR_HANDLER \
    { .callback = dynarr_default_error_callback }

#define DYNARR_MANUAL_ERROR_HANDLER(error_out) \
    { .callback = dynarr_manual_error_callback, .param = error_out }

typedef struct vector_t dynarr_t;

typedef enum dynarr_error_t
{
    DYNARR_NO_ERROR    = VECTOR_NO_ERROR,
    DYNARR_ALLOC_ERROR = VECTOR_ALLOC_ERROR,
    DYNARR_GROW_ERROR  = VECTOR_ERROR_LAST,
    DYNARR_SHRINK_ERROR,
    DYNARR_ERROR_LAST
}
dynarr_error_t;


typedef struct dynarr_opts_t
{
    size_t data_offset;  /* size of extended header */
    size_t element_size; /* size of the element     */
    size_t initial_cap;
    float grow_factor;
    float grow_threshold;
    float shrink_threshold;
    vector_error_handler_t error_handler;
}
dynarr_opts_t;


/*
* The wrapper for `dynarr_create_` function that provides default values.
*/
#define dynarr_create(dynarr_p, ...) {\
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"") \
    dynarr_create_(&dynarr_p, &(dynarr_opts_t){ \
        .initial_cap = 10, \
        .shrink_threshold = 0.25f, \
        .grow_threshold = 0.75f, \
        .grow_factor = 1.5f, \
        .error_handler = DYNARR_DEFAULT_ERROR_HANDLER, \
        __VA_ARGS__ \
    }); \
    _Pragma("GCC diagnostic pop") \
}


#define dynarr_create_manual_errhdl(dynarr_p, error_out, ...) \
    dynarr_create(dynarr_p, \
        .error_handler = DYNARR_MANUAL_ERROR_HANDLER(error_out), \
        __VA_ARGS__ \
    )


/*
* Dynamic array constructor function that initializes array
* with properties packed in opts struct.
* Space for `initial_cap` elements will be reserved.
* Array will not be able to shrink below `initial_cap`.
* In case of allocation fail null pointer will be returned.
*/
void dynarr_create_(dynarr_t **const dynarr, const dynarr_opts_t *const opts);


/*
* Returns a pointer to reserved header space for extension.
*/
void* dynarr_get_ext_header(const dynarr_t *const dynarr);


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
bool dynarr_binary_insert(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index);


/*
* Similar to insert except it stores no data, leaving slot in undefined state.
*/
bool dynarr_binary_reserve(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index);


/*
* Error callbacks:
*/
void dynarr_default_error_callback(const vector_error_t error, void *const param);

void dynarr_manual_error_callback(const vector_error_t error, void *const param);


#if 0

/*
* Reverse order of elements in the vector 
*/
bool vector_reverse(vector_t **vector);
#endif

#endif/*_DYNARR_H_*/
