#include <check.h>
#include <stdlib.h>

#include "../src/dynarr.h"

#define TOTAL_HEADER_SIZE 72
#define MAX_ELEMENTS 20
#define MOCK_MEMORY_MAX MAX_ELEMENTS * sizeof(int) + TOTAL_HEADER_SIZE

static char memory[MOCK_MEMORY_MAX];
static size_t limit = MOCK_MEMORY_MAX;
static size_t allocd = 0;

void* vector_alloc(size_t size)
{
    if (allocd + size > limit)
    {
        return NULL;
    }
    
    void *block = &memory[allocd];
    allocd += size;
    return block;
}

void *vector_realloc(void *ptr, size_t size)
{
    (void) ptr;
    if (allocd + size > limit)
    {
        return NULL;
    }
    
    void *block = &memory[allocd];
    memcpy(block, &memory[0], allocd);
    allocd += size;
    return block;
}

void vector_free(void *ptr)
{
    (void) ptr;
}


START_TEST (test_dynarr_manual_success)
{
    dynarr_t *dynarr;
    dynarr_error_t error = DYNARR_NO_ERROR;

    dynarr_create_manual_errhdl(dynarr, &error,
        .element_size = sizeof(int),
        .initial_cap = MAX_ELEMENTS
    );

    ck_assert(error == DYNARR_NO_ERROR);

    dynarr_destroy(dynarr);
}
END_TEST


START_TEST (test_dynarr_manual_fail)
{
    dynarr_t *dynarr;
    dynarr_error_t error = DYNARR_NO_ERROR;

    dynarr_create_manual_errhdl(dynarr, &error,
        .element_size = sizeof(int),
        .initial_cap = MAX_ELEMENTS + 1 /* exceeds max capacity */
    );

    ck_assert(error == DYNARR_ALLOC_ERROR);
}
END_TEST


Suite * vector_other_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Vector Failures");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dynarr_manual_success);
    tcase_add_test(tc_core, test_dynarr_manual_fail);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = vector_other_suite();
    sr = srunner_create(s);

    /* srunner_set_fork_status(sr, CK_NOFORK); */
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
