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
* @brief   This is the main dynarr type.
*/
typedef struct vector_t dynarr_t;

/**
* @brief   Dynarr creating options.
*/
typedef struct dynarr_opts_t
{
    alloc_opts_t alloc_opts;    /**< @see vector_opts_t::alloc_opts_t    */
    size_t ext_header_size;     /**< @see vector_opts_t::ext_header_size */
    size_t element_size;        /**< @see vector_opts_t::element_size */
    size_t initial_cap;         /**< @see vector_opts_t::initial_cap */
    float grow_factor;          /**< @brief Multiplier that is applied to dynarr capactity on resize. */
    float grow_threshold;       /**< @brief Fraction of the capacity need to be used to trigger growing. */
    float shrink_threshold;     /**< @brief Fraction of the capacity in use at which srink will be performed. */
}
dynarr_opts_t;

/**
* @brief   Represents operation error codes.
* @details Can be extended further.
*
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
* Represents dynarrs default create values.
*/
#define DYNARR_DEFAULT_ARGS \
    VECTOR_DEFAULT_ARGS, \
    .shrink_threshold = 0.25f, \
    .grow_threshold = 0.75f, \
    .grow_factor = 1.5f

/**
* @addtogroup Dynarr_API Dynarr API
* @brief   Main dynarr methods.
* @ref Callbacks @{ */

/**
* @addtogroup Lifetime
* @brief   Main dynarr methods. @{ */

/**
* @brief   Dynarr constructor.
* @details Wrapper over @ref dynarr_crate_ .
*          Provides default values.
*
* @see vector_create
*/
#define dynarr_create(...) \
    dynarr_create_(&(dynarr_opts_t){ \
        DYNARR_DEFAULT_ARGS, \
        __VA_ARGS__ \
    }) \

/**
* @brief   Constructor of the dynamic array.
* @details Dynamic array constructor function that initializes array
*          with properties packed in opts struct.
*          Space for @p initial_cap elements will be reserved.
*          Array will not be able to shrink below @p initial_cap.
*          In case of allocation fail null pointer will be returned.
* @param[in] opts Configuration of the dynarr to create.
*/
dynarr_t *dynarr_create_(const dynarr_opts_t *const opts);


/**
* @brief   Deallocates a dynamic array.
* @details After the call pointer will be invalidated.
*
* @param[in] dynarr Instance of a dynarr.
*/
void dynarr_destroy(dynarr_t *const dynarr);


/**
* @brief   Duplicate a dynarr.
* @details Makes an exact copy of the whole dynarr. (Allocation fail prone).
* 
* @param[in] dynarr Instance of a dynarr.
* @returns   new duplicated instance of a dynarr.
*/
dynarr_t *dynarr_clone(const dynarr_t *const dynarr);


/** @} @noop Lifetime */

/**
* @addtogroup Extension
* @brief Support for derived classes. @{ */

/**
* @brief   Retrieve a location of extended header.
* @details Provides a location in dynarr memory region,
*          where user can store a header of a derived data structure.
* @param[in] dynarr Instance of a dynarr.
* @returns   Location of extended header.
*/
void* dynarr_get_ext_header(const dynarr_t *const dynarr);

/** @} @noop Extension */

/**
* @addtogroup Properties
* @brief   Access properties of a dynarr. @{ */

/**
* @brief   Access size property of a dynarr.
* @details Reports current amount of elements containing within a dynarr.
*          Elements are stored sequentially.
*
* @param[in] dynarr Instance of a dynarr.
* @returns Amount of stored elements.
*/
size_t dynarr_size(const dynarr_t *const dynarr);


/**
* @brief   Access initial capacity property.
* @details Initial capacity if the dynarr.
*          Amount of elements reserved for dynarr from the beginning.
*          @note dynarr allocation cant shrink below this amount.
* @param[in] dynarr Instance of a dynarr.
* @returns   Initial capacity.
*/
size_t dynarr_initial_capacity(const dynarr_t *const dynarr);


/**
* @brief   Access current capacity of the dynarr.
*
* @param[in] dynarr Instance of a dynarr.
* @returns   Current capacity.
*/
size_t dynarr_capacity(const dynarr_t *const dynarr);

/** @} @noop Properties */

/**
 * @addtogroup Searches
 * @brief Methods for querying the dynarr. @{ */

/**
* @brief   Binary search for the element with matching value.
* @details Searches for an element that matches @p value.
*
* @param[in] dynarr Instance of a dynarr.
* @param[in] value  Value to be used as reference for comparison.
* @param[in] cmp    Compare callback.
* @param     param  Parameter that will be passed to callback.
* @returns Pointer to a location of the matching element or @c NULL,
*          when nothing matched.
*/
void *dynarr_binary_find(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param);


/**
* @brief   Binary search for the element with matching value.
* @details Searches for an element that matches @p value.
*
* @param[in] dynarr Instance of a dynarr.
* @param[in] value  Value to be used as reference for comparison.
* @param[in] cmp    Compare callback.
* @param     param  Parameter that will be passed to callback.
* @returns Index of matching element or @c -1 when no element matched.
*/
ssize_t dynarr_binary_find_index(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param);

/** @} @noop Searches */

/**
* @addtogroup Elements
* @brief Access and manipulate elements of a dynarr. @{ */

/**
* @brief   Clean (reset) contents of the dynarr.
* @details Drops amount of stored elements to zero,
*          while not affecting a capacity.
*
* @param[in] dynarr Instance of a dynarr.
*/
void dynarr_clear(dynarr_t *const dynarr);


/**
* @brief   Returns pointer for the element at @p index.
*
* @param[in] dynarr Pointer to a dynarr instance.
* @param[in] index  Denotes an element to be accessed.
* @returns          A pointer to a dynarr element at @c index.

*/
void *dynarr_get(const dynarr_t *const dynarr, const size_t index);


/**
* @brief    Sets element at given @c index to a @c value.
*
* @param[in] dynarr Pointer to a dynarr instance.
* @param[in] index  Denotes an element to be overriden by @c value.
* @param[in] value  Value to be stored at the @c index.
*/
void dynarr_set(dynarr_t *const dynarr, const size_t index, const void *value);


/**
* @brief   Sets element at given @c index to a zero value.
*
* @param[in] dynarr Pointer to a dynarr instance.
* @param[in] index  Denotes an element to be zeroed.
*/
void dynarr_set_zero(dynarr_t *const dynarr, const size_t index);


/**
* @brief   Access first element of a dynarr.
* @details Function assumes that element exists. 
*          Calling this function when @code size == 0 @endcode
*          results in undefined behavior.
*
* @param[in] dynarr Instance of a dynarr.
* @returns Pointer for the first element in the array,
*          assuming that array contains at least one element.
*/
void *dynarr_first(const dynarr_t *const dynarr);


/**
* @brief   Access last element if a dynarr.
* @details Function assumes that dynarr is not empty.
*          Calling this function when @code size == 0 @endcode
*          results in undefined behavior.
*
* @param[in] dynarr Instance of a dynarr.
* @returns Pointer for the last element in the array,
*          assuming that array contains at least one element.
*/
void *dynarr_last(const dynarr_t *const dynarr);


/**
* @brief   Appends an element to the tail of a dynarr.
* @details Probes size-capacity ratio if reaches grow threshold.
*          If it does, then grow allocation.
*          Appends and element to the end and inc size by one.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in] value  Value to be appended.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_GROW_ERROR]
*/
dynarr_status_t dynarr_append(dynarr_t **const dynarr, const void *const value);


/**
* @brief   Prepends an element to the head of a dynarr.
* @details Probes size-capacity ratio if reaches grow threshold.
*          If it does, then grow allocation.
*          Appends and element to the end and inc size by one.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in] value  Value to be appended.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_GROW_ERROR]
*/
dynarr_status_t dynarr_prepend(dynarr_t **const dynarr, const void *const value);


/**
* @brief   Removes an element from the tail of a dynarr.
* @details Decrements size by one.
*          Probes size-capacity ratio if reaches shrink threshold.
*          If it does, then shrinks array allocation.
*          @note Wont fail if there is nothing to remove.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_SHRINK_ERROR]
*/
dynarr_status_t dynarr_pop_back(dynarr_t **const dynarr);


/**
* @brief   Removes an element from the head of a dynarr.
* @details Decrements size by one.
*          Shifts all elements to the left by one position.
*          Probes size-capacity ratio if reaches shrink threshold.
*          If it does, then shrinks array allocation.
*          @note Wont fail if there is nothing to remove.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_SHRINK_ERROR]
*/
dynarr_status_t dynarr_pop_front(dynarr_t **const dynarr);


/**
* @brief   Inserts new element into a dynarr.
* @details Inserts an element at given @p index,
*          after shifting all elements from that @p index forward.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in]     index  Designating index of a new element.
* @param[in]     value  Location that stores elements value to be stored.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_GROW_ERROR]
*/
dynarr_status_t dynarr_insert(dynarr_t **const dynarr,
        const size_t index,
        const void *value);


/**
* @brief   Removes an element from a dynarr.
* @details An element at given @p index will be removed
*          by shifting all elements from that @p index backwards
*          and decrementing the size.
*          @note operation wont fail if index exceeds size.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in]     index  Designating index of an element to remove.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_SHRINK_ERROR]
*/
dynarr_status_t dynarr_remove(dynarr_t **const dynarr, const size_t index);


/**
* @brief   Removes range of elements from a dynarr.
* @details Element range at given @p index, @p amount elements long
*          will be removed by shifting all elements from that @p index
*          backwards by @amount and subtracting that @p amount from size.
*          @note operation wont fail if index exceeds size.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in]     index  Designating index of ranges first element.
* @param[in]     amount Length of the range to remove.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_SHRINK_ERROR]
*/
dynarr_status_t dynarr_remove_range(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount);


/**
* @brief   Removes @p limit elements that match predicate.
* @details Element removal performed form tail to head of the array
*          in order to reduce memory movement during the process.
*          Array reallocation performed at most once per call.
*
* @param[in,out] dynarr    Reference to a dynarr pointer.
* @param[in]     predicate Callback that selects matching element for removal.
* @param[in]     limit     Maximum elements to remove in total.
* @param         param     User defined param that is passed to predicate.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_SHRINK_ERROR]
*/
dynarr_status_t dynarr_remove_if(dynarr_t **const dynarr,
        const predicate_t predicate,
        const size_t limit,
        void *const param);


/**
* @brief   Non-destructive merge of two sorted dynarrs.
* @details Creates empty dynarr with options of the @p first 
*          and feeds it with the data from both (sorted) dynarrs in order.
*          An order is defined by @p cmp callback.
*          In case of allocation error @c NULL will be returned.
*
* @param[in] first  First sorted array.
* @param[in] second Second sorted array.
* @param[in] cmp    Callback for element comparison.
* @param     param  Parameter that wll be passed to a @cmp callback.
* @returs New dynarr with merged data or @c NULL on failure.
*/
dynarr_t *dynarr_binary_merge(const dynarr_t *const first,
        const dynarr_t *const second,
        const compare_t cmp,
        void *const param);


/**
* @brief   Insert single value as an element range.
* @details Inserts range of @p value copys @p amount elements long at given @p index.
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in]     index  Designating index of ranges first element.
* @param[in]     amount Length of the range to spread value on.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_GROW_ERROR]
*/
dynarr_status_t dynarr_spread_insert(dynarr_t **const dynarr,
        const size_t index,
        const size_t amount,
        const void *const value);


/**
* @brief   Binary search for binary insert support.
* @details Returns index of the insert position for a new value
*          that satisfies @p cmp ordering.
*          Function never fails.
*
* @param[in] dynarr Instance of a dynarr.
* @param[in] value  Value for new element to be inserted.
* @param[in] cmp    Compare callback.
* @param     param  Parameter that will be passed to callback.
* @returns Index of insert position for new element.
*/
size_t dynarr_binary_find_insert_place(const dynarr_t *const dynarr,
        const void *const value,
        const compare_t cmp,
        void *param);


/**
* @brief   Binary insert.
* @details Works only if previous elements
*          that contained with-in the vector are ordered in same way.
*          (Allocation may fail, so returning operation status)
*
* @param[in,out] dynarr Reference to a dynarr pointer.
* @param[in] value      Value for new element to be inserted.
* @param[in] cmp        Compare callback.
* @param     param      Parameter that will be passed to callback.
* @returns Status of the operation:
*          [#DYNARR_SUCCESS | #DYNARR_GROW_ERROR]
*/
dynarr_status_t dynarr_binary_insert(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param,
        size_t *const index);


/**
* @brief   Binary unique insert.
* @details Same as @ref dynarr_binary_insert except ignores duplicated.
*/
dynarr_status_t dynarr_binary_insert_uniq(dynarr_t **const dynarr,
        const void *const value,
        const compare_t cmp,
        void *const param,
        size_t *const index);


/**
* @brief   Similar to insert except it stores no data, leaving slot in undefined state.
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

/** @} @noop Elements */

/** @} @noop Dynarr_API */

#endif/*_DYNARR_H_*/
