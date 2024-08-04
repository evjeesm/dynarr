/**
* @file
* @brief Describes dynarr public interface.
* @author Evgeni Semenov
*/

#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h>    /* bool, true, false */
#include <stddef.h>     /* size_t */
#include <sys/types.h>  /* ssize_t */

#include "vector.h"

/**
* @brief This is the main dynarr type.
*/
typedef struct vector_t dynarr_t;

/**
* @brief Dynarr creating options.
*/
typedef struct dynarr_opts_t
{
    size_t data_offset;     /**< @see vector_opts_t::data_offset */
    size_t element_size;    /**< @see vector_opts_t::element_size */
    size_t initial_cap;     /**< @see vector_opts_t::initial_cap */
    float grow_factor;      /**< @brief Multiplier that is applied to dynarr capactity on resize. */
    float grow_threshold;   /**< @brief Fraction of the capacity need to be used to trigger growing. */
    float shrink_threshold; /**< @brief Fraction of the capacity in use at which srink will be performed. */
    void *alloc_param;      /**< @see vector_opts_t::alloc_param */
}
dynarr_opts_t;

/**
* @brief Represents operation error codes.
*
* Can be extended farther.
* @see vector_status_t
*/
typedef enum dynarr_status_t
{
    DYNARR_SUCCESS     = VECTOR_SUCCESS,     /**< @brief Success status inherited from #VECTOR_SUCCESS. */
    DYNARR_ALLOC_ERROR = VECTOR_ALLOC_ERROR, /**< @brief Success status inherited from #VECTOR_ALLOC_ERROR. */
    DYNARR_GROW_ERROR  = VECTOR_STATUS_LAST, /**<
    * @brief Allocation error on grow.
    * @details Where dynarr specific status codes begin at. */
    DYNARR_SHRINK_ERROR, /**< @brief Success status inherited from #VECTOR_ALLOC_ERROR. */
    DYNARR_STATUS_LAST /**<
    * @brief Total number of valid dynarr status codes. 
    * @details Extension point for derived enum codes */
}
dynarr_status_t;

/**
* Represents dynarr default create values.
*/
#define DYNARR_DEFAULT_ARGS \
    .initial_cap = 10, \
    .shrink_threshold = 0.25f, \
    .grow_threshold = 0.75f, \
    .grow_factor = 1.5f

/**
* @addtogroup Dynarr_API Dynarr API
* @brief Main dynarr methods. 
* @ref Callbacks @{ */

/**
* The wrapper for `dynarr_create_` function that provides default values.
*
* @see vector_create
*/
#define dynarr_create(...) \
    dynarr_create_(&(dynarr_opts_t){ \
        DYNARR_DEFAULT_ARGS, \
        __VA_ARGS__ \
    }) \

<<<<<<< HEAD
/**
* Dynamic array constructor function that initializes array
* with properties packed in opts struct.
* Space for `initial_cap` elements will be reserved.
* Array will not be able to shrink below `initial_cap`.
* In case of allocation fail null pointer will be returned.
*/
dynarr_t *dynarr_create_(const dynarr_opts_t *const opts);


/**
* Returns a pointer to reserved header space for extension.
*/
void* dynarr_get_ext_header(const dynarr_t *const dynarr);


/**
* Makes a copy of the whole array.
*/
dynarr_t *dynarr_clone(const dynarr_t *const dynarr);


/**
* Deallocates dynamic array. After the call pointer will be invalidated.
*/
void dynarr_destroy(dynarr_t *const dynarr);


/**
* Removes all of the elements of the vector. But not performs any grow/shrink operations.
*/
void dynarr_clear(dynarr_t *const dynarr);


/**
* Reports current amount of elements containing within the vector.
*/
size_t dynarr_size(const dynarr_t *const dynarr);


/**
* Getter for initial capacity.
*/
size_t dynarr_initial_capacity(const dynarr_t *const dynarr);


/**
* Reports current capacity of the vector.
*/
size_t dynarr_capacity(const dynarr_t *const dynarr);



/**
* Returns pointer for the element at `index`.
*/
void *dynarr_get(const dynarr_t *const dynarr, const size_t index);


/**
* sets element at given `index` to a `value`.
*/
void dynarr_set(dynarr_t *const dynarr, const size_t index, const void *value);


/**
* Sets element at given `index` to a zero value.
*/
void dynarr_set_zero(dynarr_t *const dynarr, const size_t index);


/**
* Returns pointer for the first element in the array,
* assuming that array contains at least one element.
*/
void *dynarr_first(const dynarr_t *const dynarr);


/**
* Returns pointer for the last element in the array,
* assuming that array contains at least one element.
*/
void *dynarr_last(const dynarr_t *const dynarr);


/**
* Wrapper for vector binary find
*/
void *dynarr_binary_find(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param);


/**
* Binary search, returns index of the element that matches or (-1) when not found.
*/
ssize_t dynarr_binary_find_index(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param);


/**
* Appends element at array's tail, growing on demand.
*/
dynarr_status_t dynarr_append(dynarr_t **const dynarr, const void *const value);


/**
* Appends element at array's head by shifting one element forward
* and growing vector on demand.
*/
dynarr_status_t dynarr_prepend(dynarr_t **const dynarr, const void *const value);


/**
* Removes element from the back, shrinking array on demand.
*/
dynarr_status_t dynarr_pop_back(dynarr_t **const dynarr);


/**
* Removes element from the head by shifting one element to the left
* and shrinking array on demand.
*/
dynarr_status_t dynarr_pop_front(dynarr_t **const dynarr);


/**
* Inserts new element at given `index`, shifting one element forward
* from that index.
*/
dynarr_status_t dynarr_insert(dynarr_t **const dynarr,
        const size_t index,
        const void *value);


/**
* Removes element at given `index`.
*/
dynarr_status_t dynarr_remove(dynarr_t **const dynarr, const size_t index);


/**
* Removes range of elements of `amount` length at given `index`.
*/
dynarr_status_t dynarr_remove_range(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount);


/**
* Removes `limit` elements that match predicate.
* Element removal performed form tail to head of the array
* in order to reduce memory movement during the process.
*
* Array reallocation performed at most once per call.
*/
dynarr_status_t dynarr_remove_if(dynarr_t **const dynarr,
        const predicate_t predicate,
        const size_t limit,
        void *const param);


/**
* Merge two dynarrs together
*/
dynarr_t *dynarr_binary_merge(const dynarr_t *const first,
        const dynarr_t *const second,
        const compare_t cmp,
        void *const param);


/**
* Inserts range of `value` copies `amount` times at specific `index`.
*/
dynarr_status_t dynarr_spread_insert(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount,
        const void *const value);


/**
* Binary search that returns index of the insert position for a new value
* that satisfies `cmp` ordering.
*/
size_t dynarr_binary_find_insert_place(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *param);


/**
* Binary insert. Works only if previous elements
* that contained in the vector are ordered in same way.
* (Allocation may fail, so returning operation status)
*/
dynarr_status_t dynarr_binary_insert(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param,
        size_t *const index);

/**
* @brief Same as @ref dynarr_binary_insert except does not inserts duplicates.
*/ 
dynarr_status_t dynarr_binary_insert_uniq(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp, void *param,
        size_t *const index);


/**
* Similar to insert except it stores no data, leaving slot in undefined state.
*/
dynarr_status_t dynarr_binary_reserve(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param,
        size_t *const index);


/** @see vector_foreach */
int dynarr_foreach(const dynarr_t *const dynarr,
        const foreach_t func,
        void *const param);


/** @see vector_aggregate */
int dynarr_aggregate(const dynarr_t *const dynarr,
        const aggregate_t func,
        void *const acc,
        void *const param);

/** @see vector_transform */
int dynarr_transform(dynarr_t *const dynarr,
        const transform_t func,
        void *const param);

/** @} @noop Dynarr_API */

#endif/*_DYNARR_H_*/
