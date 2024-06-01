#include "dynarr.h"

#include <assert.h> /* assert */
#include <string.h> /* memcpy, memset */
#include <math.h>   /* ceil, floor */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* abort */

typedef struct dynarr_header_t
{
    size_t size;
    float grow_factor;
    float grow_threshold;
    float shrink_threshold;
}
dynarr_header_t;


/**                          ***
* === Forward Declarations === *
**                            */

static dynarr_header_t *get_dynarr_header(const dynarr_t *const dynarr);
static bool grow(dynarr_t **const dynarr, const size_t times);
static bool shrink(dynarr_t **const dynarr, const size_t times);
static void free_space_at(dynarr_t *const dynarr, const size_t index, const size_t amount);
static void make_space_at(dynarr_t *const dynarr, const size_t index, size_t amount);
static void default_error_callback(const vector_t *const *const dynarr, const vector_error_t error, void *const param);


/**                          ***
* === API Implementation   === *
**                            */

void dynarr_create_(dynarr_t **const dynarr, const dynarr_opts_t *const opts)
{
    assert(dynarr);
    assert(opts);

    const size_t grow_at = ceil(opts->initial_cap * opts->grow_threshold);
    const size_t next_shrink_at = floor(grow_at * opts->shrink_threshold);
    assert(next_shrink_at <= grow_at);

    vector_error_callback_t error_callback = opts->error_handler.callback
        ? opts->error_handler.callback
        : default_error_callback;

    vector_create(*dynarr,
        .data_offset = sizeof(dynarr_header_t) + opts->data_offset,
        .element_size = opts->element_size,
        .initial_cap = opts->initial_cap,
        .error_handler = { .callback = error_callback }, /* custom error handling procedure */
    );

    dynarr_header_t *header = get_dynarr_header(*dynarr);
    *header = (dynarr_header_t){
        .size = 0,
        opts->grow_factor,
        opts->grow_threshold,
        opts->shrink_threshold
    };
}


void* dynarr_get_ext_header(const dynarr_t *const dynarr)
{
    assert(dynarr);
    assert((vector_data_offset(dynarr) > sizeof(dynarr_header_t)) && "extension header was not alloc'd.");

    return (char*) vector_get_ext_header(dynarr) + sizeof(dynarr_header_t);
}


dynarr_t *dynarr_clone(const dynarr_t *const dynarr)
{
    assert(dynarr);
    return vector_clone(dynarr);
}


void dynarr_destroy(dynarr_t *const dynarr)
{
    assert(dynarr);
    vector_destroy(dynarr);
}


void dynarr_clear(dynarr_t *const dynarr)
{
    assert(dynarr);
    get_dynarr_header(dynarr)->size = 0;
}


size_t dynarr_size(const dynarr_t *const dynarr)
{
    assert(dynarr);
    dynarr_header_t *header = get_dynarr_header(dynarr);
    return header->size;
}


size_t dynarr_capacity(const dynarr_t *const dynarr)
{
    assert(dynarr);
    return vector_capacity(dynarr);
}


void *dynarr_get(const dynarr_t *const dynarr, const size_t index)
{
    assert(dynarr);
    assert((index < dynarr_size(dynarr)) && "Index out of bounds.");
    return vector_get(dynarr, index);
}


void dynarr_set(dynarr_t *const dynarr, const size_t index, const void *value)
{
    assert(dynarr);
    assert((index < dynarr_size(dynarr)) && "Index out of bounds.");
    assert(value);
    vector_set(dynarr, index, value);
}


void dynarr_set_zero(dynarr_t *const dynarr, const size_t index)
{
    assert(dynarr);
    assert((index < dynarr_size(dynarr)) && "Index out of bounds.");
    vector_set_zero(dynarr, index);
}


void *dynarr_first(const dynarr_t *const dynarr)
{
    assert(dynarr);
    assert((0 < dynarr_size(dynarr)) && "No elements in the array!");
    return dynarr_get(dynarr, 0);
}


void *dynarr_last(const dynarr_t *const dynarr)
{
    assert(dynarr);
    assert((0 < dynarr_size(dynarr)) && "No elements in the array!");
    const size_t last = dynarr_size(dynarr) - 1;
    return dynarr_get(dynarr, last);
}


bool dynarr_append(dynarr_t **const dynarr, const void *const value)
{
    assert(dynarr && *dynarr);
    assert(value);

    return dynarr_insert(dynarr, dynarr_size(*dynarr), value);
}


bool dynarr_prepend(dynarr_t **const dynarr, const void *const value)
{
    assert(dynarr && *dynarr);
    assert(value);

    return dynarr_insert(dynarr, 0, value);
}


void dynarr_pop_back(dynarr_t **const dynarr)
{
    assert(dynarr && *dynarr);
    dynarr_remove(dynarr, dynarr_size(*dynarr) - 1);
}


void dynarr_pop_front(dynarr_t **const dynarr)
{
    assert(dynarr && *dynarr);
    dynarr_remove(dynarr, 0);
}


bool dynarr_insert(dynarr_t **const dynarr, const size_t index, const void *value)
{
    assert(dynarr && *dynarr);
    assert(index <= dynarr_size(*dynarr));
    assert(value);

    if (!grow(dynarr, 1))
    {
        return false;
    }

    make_space_at(*dynarr, index, 1);

    dynarr_set(*dynarr, index, value);
    return true;
}


bool dynarr_spread_insert(dynarr_t **const dynarr, const size_t index, const size_t amount, const void *const value)
{
    assert(dynarr && *dynarr);
    assert(index <= dynarr_size(*dynarr));
    assert(value);

    if (!grow(dynarr, amount))
    {
        return false;
    }

    make_space_at(*dynarr, index, amount);
    dynarr_set(*dynarr, index, value);
    vector_spread(*dynarr, index, amount);

    return true;
}


bool dynarr_binary_insert(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *param, size_t *const index)
{
    assert(dynarr && *dynarr);
    assert(value);
    assert(cmp);

    size_t place = vector_binary_find_insert_place(*dynarr, value, dynarr_size(*dynarr), cmp, param);
    if (!dynarr_insert(dynarr, place, value))
    {
        return false;
    }

    if (index) *index = place;
    return true;
}


bool dynarr_binary_reserve(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index)
{
    assert(dynarr && *dynarr);
    assert(value);
    assert(cmp);

    size_t place = vector_binary_find_insert_place(*dynarr, value, dynarr_size(*dynarr), cmp, param);
    if (!grow(dynarr, 1))
    {
        return false;
    }

    make_space_at(*dynarr, place, 1);
    *index = place;
    return true;
}


void dynarr_remove(dynarr_t **const dynarr, const size_t index)
{
    assert(dynarr && *dynarr);
    dynarr_remove_range(dynarr, index, 1);
}


void dynarr_remove_range(dynarr_t **const dynarr, const size_t index, const size_t amount)
{
    assert(dynarr && *dynarr);
    assert(amount > 0);

    const size_t size = dynarr_size(*dynarr);
    if (0 == size)
    {
        return;
    }

    free_space_at(*dynarr, index, amount);

    assert(shrink(dynarr, amount));
}


/**                       ***
* === Static Functions  === *
**                         */

static dynarr_header_t *get_dynarr_header(const dynarr_t *const dynarr)
{
    return (dynarr_header_t*) vector_get_ext_header(dynarr);
}


static bool grow(dynarr_t **const dynarr, const size_t amount_to_add)
{
    const dynarr_header_t *const header = get_dynarr_header(*dynarr);
    const size_t size = dynarr_size(*dynarr) + amount_to_add;
    double capacity = dynarr_capacity(*dynarr);
    size_t grow_at = capacity * header->grow_threshold;

    while (size >= grow_at)
    {
        capacity *= header->grow_factor;
        grow_at = capacity * header->grow_threshold;
    }

    const size_t new_cap = ceil(capacity);
    if (new_cap == dynarr_capacity(*dynarr))
    {
        return true;
    }

    return vector_truncate(dynarr, new_cap, (vector_error_t)DYNARR_GROW_ERROR);
}


static bool shrink(dynarr_t **const dynarr, const size_t amount_to_remove)
{
    const dynarr_header_t *const header = get_dynarr_header(*dynarr);
    const size_t size = dynarr_size(*dynarr) - amount_to_remove;
    double capacity = dynarr_capacity(*dynarr);
    size_t shrink_at = capacity * header->shrink_threshold;

    while (size < shrink_at)
    {
        capacity /= header->grow_factor;
        shrink_at = capacity * header->shrink_threshold;
    }

    const size_t initial_cap = vector_initial_capacity(*dynarr);
    size_t new_cap = floor(capacity);
    new_cap = new_cap < initial_cap ? initial_cap : new_cap;

    if (dynarr_capacity(*dynarr) == new_cap)
    {
        return true;
    }

    return vector_truncate(dynarr, new_cap, (vector_error_t)DYNARR_SHRINK_ERROR);
}


static void free_space_at(dynarr_t *const dynarr, const size_t index, const size_t amount)
{
    const size_t size = dynarr_size(dynarr);
    dynarr_header_t *header = get_dynarr_header(dynarr);

    if (index >= size)
    {
        return; // already free
    }

    const size_t rest_from_index = size - index;

    if (amount >= rest_from_index)
    {
        header->size -= rest_from_index;
    }
    else
    {
        const size_t element_size = vector_element_size(dynarr);
        size_t rest = rest_from_index - amount;
        char *to = (char*) dynarr_get(dynarr, 0) + element_size * index;
        char *from = to + element_size * amount;

        memmove(to, from, element_size * rest);
        header->size -= amount;
    }
}


static void make_space_at(dynarr_t *const dynarr, const size_t index, size_t amount)
{
    const size_t size = dynarr_size(dynarr);
    dynarr_header_t *header = get_dynarr_header(dynarr);

    if (index > size)
    {
        amount += index - size;
    }

    if (index < size)
    {
        const size_t element_size = vector_element_size(dynarr);
        char *from = (char*) dynarr_get(dynarr, 0) + element_size * index;
        char *to = from + element_size * amount;

        memmove(to, from, element_size * (size - index));
    }

    header->size += amount;
}


static void default_error_callback(const vector_t *const *const dynarr, const vector_error_t error, void *const param)
{
    (void) param;

    switch ((dynarr_error_t)error)
    {
        case DYNARR_ALLOC_ERROR:
            fprintf(stderr, "Dynarr :: Alloc error occured! abort()\n");
            abort();

        case DYNARR_GROW_ERROR:
            fprintf(stderr, "Dynarr [ %p ] :: Grow error occured! abort()\n", (void*)*dynarr);
            abort();

        case DYNARR_SHRINK_ERROR:
            fprintf(stderr, "Dynarr [ %p ] :: Shrink error occured, keep going...\n", (void*)*dynarr);
            break;

        default:
            fprintf(stderr, "Dynarr [ %p ] :: Unexpected error occured! abort()\n", (void*)*dynarr);
            abort();
    }
}
