#include "dynarr.h"
#include "vector.h"

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
static dynarr_status_t grow(dynarr_t **const dynarr, const size_t amount_to_add);
static dynarr_status_t shrink(dynarr_t **const dynarr, const size_t amount_to_remove);
static void free_space_at(dynarr_t *const dynarr, const size_t index, const size_t amount);
static void make_space_at(dynarr_t *const dynarr, const size_t index, /*mut*/ size_t amount);

static size_t binary_find_insert_place(const dynarr_t *const dynarr,
        const void *value,
        const size_t start,
        const size_t end,
        const compare_t cmp,
        void *param);

/**                          ***
* === API Implementation   === *
**                            */

dynarr_t *dynarr_create_(const dynarr_opts_t *const opts)
{
    assert(opts);
    assert(opts->element_size);

    const size_t grow_at = ceil(opts->initial_cap * opts->grow_threshold);
    const size_t next_shrink_at = floor(grow_at * opts->shrink_threshold);
    assert(next_shrink_at <= grow_at);

    dynarr_t *dynarr = vector_create(
        .data_offset = sizeof(dynarr_header_t) + opts->data_offset,
        .element_size = opts->element_size,
        .initial_cap = opts->initial_cap,
    );

    if (NULL == dynarr) return NULL;

    dynarr_header_t *header = get_dynarr_header(dynarr);
    *header = (dynarr_header_t){
        .size = 0,
        opts->grow_factor,
        opts->grow_threshold,
        opts->shrink_threshold
    };

    return dynarr;
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
    return get_dynarr_header(dynarr)->size;
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


void *dynarr_binary_find(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param)
{
    assert(dynarr);
    assert(value);
    assert(cmp);
    return vector_binary_find(dynarr, value, dynarr_size(dynarr), cmp,
            param);
}


ssize_t dynarr_binary_find_index(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param)
{
    assert(dynarr);
    assert(value);
    assert(cmp);
    return vector_binary_find_index(dynarr, value, dynarr_size(dynarr),
            cmp, param);
}


dynarr_status_t dynarr_append(dynarr_t **const dynarr, const void *const value)
{
    assert(dynarr && *dynarr);
    assert(value);

    return dynarr_insert(dynarr, dynarr_size(*dynarr), value);
}


dynarr_status_t dynarr_prepend(dynarr_t **const dynarr, const void *const value)
{
    assert(dynarr && *dynarr);
    assert(value);

    return dynarr_insert(dynarr, 0, value);
}


dynarr_status_t dynarr_pop_back(dynarr_t **const dynarr)
{
    assert(dynarr && *dynarr);
    return dynarr_remove(dynarr, dynarr_size(*dynarr) - 1);
}


dynarr_status_t dynarr_pop_front(dynarr_t **const dynarr)
{
    assert(dynarr && *dynarr);
    return dynarr_remove(dynarr, 0);
}


dynarr_status_t dynarr_insert(dynarr_t **const dynarr,
        const size_t index,
        const void *value)
{
    assert(dynarr && *dynarr);
    assert(index <= dynarr_size(*dynarr));
    assert(value);

    dynarr_status_t status = grow(dynarr, 1);

    if (DYNARR_SUCCESS != status) return status;

    make_space_at(*dynarr, index, 1);
    dynarr_set(*dynarr, index, value);

    return DYNARR_SUCCESS;
}


dynarr_status_t dynarr_spread_insert(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount,
        const void *const value)
{
    assert(dynarr && *dynarr);
    assert(index <= dynarr_size(*dynarr));
    assert(value);

    dynarr_status_t status = grow(dynarr, amount);
    if (DYNARR_SUCCESS != status) return status;

    make_space_at(*dynarr, index, amount);
    dynarr_set(*dynarr, index, value);
    vector_spread(*dynarr, index, amount);

    return DYNARR_SUCCESS;
}


size_t dynarr_binary_find_insert_place(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *param)
{
    assert(dynarr);
    assert(value);
    assert(cmp);

    return binary_find_insert_place(dynarr, value, 0, dynarr_size(dynarr), cmp, param);
}


dynarr_status_t dynarr_binary_insert(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *param,
        size_t *const index)
{
    assert(dynarr && *dynarr);
    assert(value);
    assert(cmp);

    size_t place = dynarr_binary_find_insert_place(*dynarr, value, cmp, param);
    dynarr_status_t status = dynarr_insert(dynarr, place, value);

    if (DYNARR_SUCCESS != status) return status;

    if (index) *index = place; /* optionally return index of inserted element */
    return DYNARR_SUCCESS;
}


dynarr_status_t dynarr_binary_insert_uniq(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp, void *param,
        size_t *const index)
{
    assert(dynarr && *dynarr);
    assert(value);
    assert(cmp);

    ssize_t found = dynarr_binary_find_index(*dynarr, value, cmp, param);
    if (found) return DYNARR_SUCCESS;

    return dynarr_binary_insert(dynarr, value, cmp, param, index);
}


dynarr_status_t dynarr_binary_reserve(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param,
        size_t *const index)
{
    assert(dynarr && *dynarr);
    assert(value);
    assert(cmp);

    size_t place = dynarr_binary_find_insert_place(*dynarr, value, cmp, param);
    dynarr_status_t status = grow(dynarr, 1);

    if (DYNARR_SUCCESS != status) return status;

    make_space_at(*dynarr, place, 1);
    *index = place;

    return DYNARR_SUCCESS;
}


dynarr_status_t dynarr_remove(dynarr_t **const dynarr, const size_t index)
{
    assert(dynarr && *dynarr);
    return dynarr_remove_range(dynarr, index, 1);
}


dynarr_status_t dynarr_remove_range(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount)
{
    assert(dynarr && *dynarr);
    assert(amount > 0);

    if (0 == dynarr_size(*dynarr)) return DYNARR_SUCCESS; /* nothing to remove */

    free_space_at(*dynarr, index, amount);
    return shrink(dynarr, amount);
}


dynarr_status_t dynarr_remove_if(dynarr_t **const dynarr,
        const predicate_t predicate,
        const size_t limit,
        void *const param)
{
    assert(dynarr && *dynarr);

    size_t removed = 0;
    for (size_t i = dynarr_size(*dynarr); i > 0 && removed < limit; --i) /* going in reverse */
    {
        if (predicate(dynarr_get(*dynarr, i - 1), param))
        {
            free_space_at(*dynarr, i - 1, 1);
            ++removed;
        }
    }

    return shrink(dynarr, removed);
}

typedef struct merge_helper_data
{
    const compare_t cmp;
    void *const param;
}
merge_helper_data;

static int merge_helper(const void *const element, void *const acc, void *const param)
{
    dynarr_t **acc_ = (dynarr_t**)acc;
    merge_helper_data *data = param;
    return dynarr_binary_insert_uniq(acc_, element, data->cmp, data->param, NULL);
}

dynarr_t *dynarr_binary_merge(const dynarr_t *const first,
        const dynarr_t *const second,
        const compare_t cmp,
        void *const param)
{
    assert(first);
    assert(second);
    assert(cmp);

    dynarr_t *merged = dynarr_clone(first);
    if (!merged) return NULL;

    const size_t second_size = dynarr_size(second);
    merge_helper_data data = {.cmp = cmp, .param = param };
    dynarr_status_t status = dynarr_aggregate(second, merge_helper, &merged, &data);
    if (DYNARR_SUCCESS != status)
    {
        dynarr_destroy(merged);
        return NULL;
    }
    return merged;
}


int dynarr_foreach(const dynarr_t *const dynarr,
        const foreach_t func,
        void *const param)
{
    assert(dynarr);
    assert(func);
    return vector_foreach(dynarr, dynarr_size(dynarr), func, param);
}


int dynarr_aggregate(const dynarr_t *const dynarr,
        const aggregate_t func,
        void *const acc,
        void *const param)
{
    assert(dynarr);
    assert(func);

    return vector_aggregate(dynarr, dynarr_size(dynarr), func, acc, param);
}


int dynarr_transform(dynarr_t *const dynarr,
        const transform_t func,
        void *const param)
{
    assert(dynarr);
    assert(func);

    return dynarr_foreach(dynarr, (foreach_t)func, param);
}

/**                       ***
* === Static Functions  === *
**                         */

static dynarr_header_t *get_dynarr_header(const dynarr_t *const dynarr)
{
    return (dynarr_header_t*) vector_get_ext_header(dynarr);
}


static dynarr_status_t grow(dynarr_t **const dynarr, const size_t amount_to_add)
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
        return DYNARR_SUCCESS;
    }

    return (dynarr_status_t)vector_resize(dynarr, new_cap, (vector_status_t)DYNARR_GROW_ERROR);
}


static dynarr_status_t shrink(dynarr_t **const dynarr, const size_t amount_to_remove)
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
        return DYNARR_SUCCESS;
    }

    return (dynarr_status_t)vector_resize(dynarr, new_cap, (vector_status_t)DYNARR_SHRINK_ERROR);
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


static size_t binary_find_insert_place(const dynarr_t *const dynarr,
        const void *value,
        const size_t start,
        const size_t end,
        const compare_t cmp,
        void *param)
{
    if (start == end)
    {
        return start;
    }

    const size_t middle = (start + end) / 2;
    const void *middle_value = dynarr_get(dynarr, middle);

    if (0 == cmp(value, middle_value, param))
    {
        return middle + 1;
    }

    if (0 < cmp(value, middle_value, param))
    {
        return binary_find_insert_place(dynarr, value, middle + 1, end, cmp, param);
    }

    return binary_find_insert_place(dynarr, value, start, middle, cmp, param);
}

