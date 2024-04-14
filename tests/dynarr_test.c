#include <check.h>
#include <stdlib.h>
#include "../src/dynarr.h"

static ssize_t cmp(const void *a, const void *b, void *param)
{
    (void)param;
    return (ssize_t) *(int*)a - *(int*)b;
}

static bool pred(const void *a, const void *b, void *param)
{
    return *(int*)a == *(int*)b;
}

static dynarr_t *array;

static void setup_empty(void)
{
    dynarr_create(array,
       .element_size = sizeof(int),
       .initial_cap = 10,
       .shrink_threshold = 0.35f,
       .grow_threshold = 0.75f,
       .grow_factor = 1.5f
    );
}

static void teardown(void)
{
    dynarr_destroy(array);
}


START_TEST (test_dynarr_create)
{
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(dynarr_size(array), 0);
    ck_assert_uint_eq(dynarr_capacity(array), 10);
}
END_TEST


START_TEST (test_dynarr_append)
{
    const int expected_value = 69;
    const size_t expected_size = 1;

    ck_assert(dynarr_append(&array, &expected_value));
    ck_assert_int_eq(*(int*)dynarr_get(array, 0), expected_value);
    ck_assert_uint_eq(dynarr_size(array), expected_size);

    const size_t append_count = 7;
    const size_t expected_capacity = 10 * 1.5;

    for (int i = 0; i < append_count; ++i)
    {
        dynarr_append(&array, &i);
    }

    for (int i = 0; i < append_count; ++i)
    {
        int *elem = (int*) dynarr_get(array, i + 1);
        ck_assert_mem_eq(elem, &i, sizeof(int));
    }

    ck_assert_uint_eq(dynarr_capacity(array), expected_capacity);
}
END_TEST


START_TEST (test_dynarr_prepend)
{
    const int expected_value = 69;
    const size_t expected_size = 1;

    ck_assert(dynarr_prepend(&array, &expected_value));
    ck_assert_int_eq(*(int*)dynarr_get(array, 0), expected_value);
    ck_assert_uint_eq(dynarr_size(array), expected_size);

    const size_t append_count = 7;
    const size_t expected_capacity = 10 * 1.5;

    for (int i = 0; i < append_count; ++i)
    {
        dynarr_prepend(&array, &i);
    }

    for (int i = 0; i < append_count; ++i)
    {
        int *elem = (int*) dynarr_get(array, append_count - i - 1);
        ck_assert_mem_eq(elem, &i, sizeof(int));
    }

    ck_assert_uint_eq(dynarr_capacity(array), expected_capacity);
}
END_TEST


START_TEST (test_dynarr_clear)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert(dynarr_append(&array, &i));
    }
    size_t cap = dynarr_capacity(array);
    dynarr_clear(array);
    ck_assert_uint_eq(dynarr_size(array), 0);
    ck_assert_uint_eq(dynarr_capacity(array), cap);
}
END_TEST


START_TEST (test_dynarr_pop_back)
{
    dynarr_pop_back(&array);

    size_t expected_size = 8;
    size_t expected_cap = 15;

    for (int i = 0; i < expected_size; ++i)
    {
        ck_assert(dynarr_append(&array, &i));
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    const size_t pop_num = 5;
    expected_size -= pop_num;
    expected_cap = 10;

    for (int i = 0; i < pop_num; ++i)
    {
        dynarr_pop_back(&array);
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    for (int i = 0; i < expected_size; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), &i, sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_pop_front)
{
    dynarr_pop_back(&array);

    size_t expected_size = 14;
    size_t expected_cap = 23;

    for (int i = 0; i < expected_size; ++i)
    {
        ck_assert(dynarr_append(&array, &i));
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    const size_t pop_num = 7;
    expected_size -= pop_num;
    expected_cap = 15;

    for (int i = 0; i < pop_num; ++i)
    {
        dynarr_pop_front(&array);
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    for (int i = 0; i < expected_size; ++i)
    {
        int expected = i + pop_num;
        ck_assert_mem_eq(dynarr_get(array, i), &expected, sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_insert)
{
    ck_assert(dynarr_insert(&array, 0, TMP_REF(int, 999)));
    ck_assert_uint_eq(dynarr_size(array), 1);
    ck_assert_mem_eq(dynarr_get(array, 0), TMP_REF(int, 999), sizeof(int));

    for (int i = 1; i < 9; ++i)
    {
        ck_assert(dynarr_insert(&array, i, &i));
    }

    /* insert at index 5 */
    ck_assert(dynarr_insert(&array, 5, TMP_REF(int, 777)));
    ck_assert_mem_eq(dynarr_get(array, 5), TMP_REF(int, 777), sizeof(int));

    for (int i = 6; i < 9; ++i) /* check that rest of the elements shifted */
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, i - 1), sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_spread_insert)
{
    bool status = dynarr_spread_insert(&array, 0, 10, TMP_REF(int, 999));
    ck_assert(status);

    size_t size = dynarr_size(array);
    ck_assert_uint_eq(size, 10);

    for (int i = 0; i < size; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, 999), sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_remove)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert(dynarr_append(&array, &i));
    }
    dynarr_remove(&array, 5);
    ck_assert_uint_eq(dynarr_size(array), 19);
    
    for (int i = 5; i < 19; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, i + 1), sizeof(int));
    }
}


END_TEST
#if 0





START_TEST (test_vector_binary_insert)
{
    int table[] = {10, 23, 31, 1, 4, 22, 34, 71, 15, 18, 0, 5, 45, 99, 2, 0, 71, 22};
    size_t size = sizeof(table)/sizeof(*table);

    for (int i = 0; i < size; ++i)
    {
        ck_assert(vector_binary_insert(&vector, cmp, &table[i], NULL, NULL));
    }

    ck_assert_uint_eq(size, vector_size(vector));

    bool ordered = true;
    int curr = 0;
    int prev = *(int*)vector_first(vector);
    vector_pop_front(&vector);

    while (ordered && (0 < vector_size(vector)))
    {
        curr = *(int*)vector_first(vector);
        vector_pop_front(&vector);
        ordered = prev <= curr;
        prev = curr;
    }
    ck_assert_msg(ordered, "Binary insert has to preserve `cmp` order.");
}
END_TEST


START_TEST (test_vector_binary_insert_random)
{
    srand(3011);
    int random;

    for (int i = 0; i < 100; ++i)
    {
        random = rand();
        vector_binary_insert(&vector, cmp, &random, NULL, NULL);
    }
}
END_TEST


START_TEST (test_vector_binary_find)
{
    int table[] = {10, 23, 31, 1, 4, 34, 71, 15, 18, 5, 45, 99, 2, 0, 71, 22};
    size_t size = sizeof(table)/sizeof(*table);

    for (int i = 0; i < size; ++i)
    {
        ck_assert(vector_binary_insert(&vector, cmp, &table[i], NULL, NULL));
    }

    for (int i = 0; i < size; ++i)
    {
        void *p = vector_binary_find(vector, cmp, &table[i], NULL);
        ck_assert_mem_eq(p, &table[i], sizeof(int));
    }
}
END_TEST




START_TEST (test_vector_insert_fill_inbetween)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert(vector_append_back(&vector, &i));
    }
    const size_t initial_size = vector_size(vector);
    const size_t insert_idx = 9;
    const size_t amount = 5;

    bool status = vector_insert_fill(&vector, insert_idx, amount, TMP_REF(int, 999));
    ck_assert(status);

    const size_t size = vector_size(vector);
    ck_assert_uint_eq(size, amount + initial_size);

    for (int i = 0, k = 0; i < size; ++i)
    {
        if (i >= insert_idx && i < (insert_idx + amount))
        {
            ck_assert_mem_eq(vector_get(vector, i), TMP_REF(int, 999), sizeof(int));
        }
        else
        {
            ck_assert_mem_eq(vector_get(vector, i), &k, sizeof(int));
            ++k;
        }
    }
}
END_TEST

#endif

Suite *dynarr_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Vector");
    
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup_empty, teardown);
    tcase_add_test(tc_core, test_dynarr_create);
    tcase_add_test(tc_core, test_dynarr_append);
    tcase_add_test(tc_core, test_dynarr_prepend);
    tcase_add_test(tc_core, test_dynarr_clear);
    tcase_add_test(tc_core, test_dynarr_pop_back);
    tcase_add_test(tc_core, test_dynarr_pop_front);
    tcase_add_test(tc_core, test_dynarr_insert);
    tcase_add_test(tc_core, test_dynarr_spread_insert);
    tcase_add_test(tc_core, test_dynarr_remove);
#if 0
    tcase_add_test(tc_core, test_vector_first);
    tcase_add_test(tc_core, test_vector_last);
    tcase_add_test(tc_core, test_vector_get);
    tcase_add_test(tc_core, test_vector_set);
    tcase_add_test(tc_core, test_vector_contains);
    tcase_add_test(tc_core, test_vector_find);
    tcase_add_test(tc_core, test_vector_remove);
    tcase_add_test(tc_core, test_vector_binary_insert);
    tcase_add_test(tc_core, test_vector_binary_insert_random);
    tcase_add_test(tc_core, test_vector_binary_find);
    tcase_add_test(tc_core, test_vector_insert_fill_inbetween);
#endif
    suite_add_tcase(s, tc_core);

    return s;
}


int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = dynarr_suite();
    sr = srunner_create(s);

    /* srunner_set_fork_status(sr, CK_NOFORK); */
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

