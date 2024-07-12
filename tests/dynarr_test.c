#include <check.h>
#include <stdlib.h>
#include "../src/dynarr.h"
#include "vector.h"

static dynarr_t *array;

static ssize_t cmp(const void *a, const void *b, void *param)
{
    (void)param;
    return (ssize_t) *(int*)a - *(int*)b;
}

static void setup_empty(void)
{
    array = dynarr_create(
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

    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &expected_value));
    ck_assert_int_eq(*(int*)dynarr_get(array, 0), expected_value);
    ck_assert_uint_eq(dynarr_size(array), expected_size);

    const int append_count = 7;
    const size_t expected_capacity = 10 * 1.5;

    for (int i = 0; i < append_count; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
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

    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_prepend(&array, &expected_value));
    ck_assert_int_eq(*(int*)dynarr_get(array, 0), expected_value);
    ck_assert_uint_eq(dynarr_size(array), expected_size);

    const int append_count = 7;
    const size_t expected_capacity = 10 * 1.5;

    for (int i = 0; i < append_count; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_prepend(&array, &i));
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
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
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

    int expected_size = 8;
    size_t expected_cap = 15;

    for (int i = 0; i < expected_size; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    const int pop_num = 5;
    expected_size -= pop_num;
    expected_cap = 10;

    for (int i = 0; i < pop_num; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_pop_back(&array));
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

    int expected_size = 14;
    size_t expected_cap = 23;

    for (int i = 0; i < expected_size; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
    }

    ck_assert_uint_eq(dynarr_size(array), expected_size);
    ck_assert_uint_eq(dynarr_capacity(array), expected_cap);

    const int pop_num = 7;
    expected_size -= pop_num;
    expected_cap = 15;

    for (int i = 0; i < pop_num; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_pop_front(&array));
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
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_insert(&array, 0, TMP_REF(int, 999)));
    ck_assert_uint_eq(dynarr_size(array), 1);
    ck_assert_mem_eq(dynarr_get(array, 0), TMP_REF(int, 999), sizeof(int));

    for (int i = 1; i < 9; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_insert(&array, i, &i));
    }

    /* insert at index 5 */
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_insert(&array, 5, TMP_REF(int, 777)));
    ck_assert_mem_eq(dynarr_get(array, 5), TMP_REF(int, 777), sizeof(int));

    for (int i = 6; i < 9; ++i) /* check that rest of the elements shifted */
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, i - 1), sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_spread_insert)
{
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_spread_insert(&array, 0, 10, TMP_REF(int, 999)));

    size_t size = dynarr_size(array);
    ck_assert_uint_eq(size, 10);

    for (size_t i = 0; i < size; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, 999), sizeof(int));
    }
}
END_TEST


START_TEST (test_dynarr_spread_insert_inbetween)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
    }
    const int initial_size = dynarr_size(array);
    const int insert_idx = 9;
    const int amount = 5;

    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_spread_insert(&array, insert_idx, amount, TMP_REF(int, 999)));

    const int size = dynarr_size(array);
    ck_assert_uint_eq(size, amount + initial_size);

    for (int i = 0, k = 0; i < size; ++i)
    {
        if (i >= insert_idx && i < (insert_idx + amount))
        {
            ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, 999), sizeof(int));
        }
        else
        {
            ck_assert_mem_eq(dynarr_get(array, i), &k, sizeof(int));
            ++k;
        }
    }
}
END_TEST


START_TEST (test_dynarr_remove)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
    }
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_remove(&array, 5));
    ck_assert_uint_eq(dynarr_size(array), 19);
    
    for (int i = 5; i < 19; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, i + 1), sizeof(int));
    }
}
END_TEST


static bool is_even(const void *const element, void *const param)
{
    (void) param;
    return *(int*)element % 2 == 0;
}

START_TEST (test_dynarr_remove_if)
{
    for (int i = 0; i < 20; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_append(&array, &i));
    }
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_remove_if(&array, is_even, dynarr_size(array), NULL));
    ck_assert_uint_eq(dynarr_size(array), 10);

    for (int i = 0; i < 10; ++i)
    {
        ck_assert_mem_eq(dynarr_get(array, i), TMP_REF(int, i*2 + 1), sizeof(int));
    }
}
END_TEST


static ssize_t cmp_int_asc(const void *value, const void *element, void *param)
{
    (void) param;
    return *(int*) value - *(int*) element;
}

START_TEST (test_dynarr_binary_find_insert_place)
{
    const int data[] = {-100, -1, 0, 10, 12, 20, 21, 30, 34, 60};
    for (size_t i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        dynarr_append(&array, &data[i]);
    }

    size_t index = 0;

    index = dynarr_binary_find_insert_place(array, TMP_REF(int, -200), cmp_int_asc, NULL);
    ck_assert_uint_eq(0, index);

    index = dynarr_binary_find_insert_place(array, TMP_REF(int, -20), cmp_int_asc, NULL);
    ck_assert_uint_eq(1, index);

    index = dynarr_binary_find_insert_place(array, TMP_REF(int, 0), cmp_int_asc, NULL);
    ck_assert_uint_eq(3, index); /* skips equal numbers according to current cmp implementation */

    index = dynarr_binary_find_insert_place(array, TMP_REF(int, 1), cmp_int_asc, NULL);
    ck_assert_uint_eq(3, index);
}
END_TEST


START_TEST (test_dynarr_binary_insert)
{
    int table[] = {10, 23, 31, 1, 4, 22, 34, 71, 15, 18, 0, 5, 45, 99, 2, 0, 71, 22};
    size_t size = sizeof(table)/sizeof(*table);

    for (size_t i = 0; i < size; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_binary_insert(&array, &table[i], cmp, NULL, NULL));
    }

    ck_assert_uint_eq(size, dynarr_size(array));

    bool ordered = true;
    int curr = 0;
    int prev = *(int*)dynarr_first(array);
    ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_pop_front(&array));

    while (ordered && (0 < dynarr_size(array)))
    {
        curr = *(int*)dynarr_first(array);
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_pop_front(&array));
        ordered = prev <= curr;
        prev = curr;
    }
    ck_assert_msg(ordered, "Binary insert has to preserve `cmp` order.");
}
END_TEST


START_TEST (test_dynarr_binary_find)
{
    int table[] = {10, 23, 31, 1, 4, 34, 71, 15, 18, 5, 45, 99, 2, 0, 71, 22};
    size_t size = sizeof(table)/sizeof(*table);

    for (size_t i = 0; i < size; ++i)
    {
        ck_assert_uint_eq(DYNARR_SUCCESS, dynarr_binary_insert(&array, &table[i], cmp, NULL, NULL));
    }

    for (size_t i = 0; i < size; ++i)
    {
        void *p = vector_binary_find(array, &table[i], dynarr_size(array), cmp, NULL);
        ck_assert_mem_eq(p, &table[i], sizeof(int));
    }
}
END_TEST


START_TEST(test_dynarr_binary_merge)
{
    const int data1[] = {-10, -4, 0, 2, 5, 6, 10, 22, 23, 30};
    const int data2[] = {-11, -9, 1, 2, 7, 11, 15, 23, 31, 40, 41, 42};
    const int data_res[] = {-11, -10, -9, -4, 0, 1, 2, 5, 6, 7, 10, 11, 15, 22, 23, 30, 31, 40, 41, 42};
    const size_t data_res_size = sizeof(data_res)/sizeof(data_res[0]);

    dynarr_t *first = dynarr_create(.element_size = sizeof(int));
    dynarr_t *second = dynarr_create(.element_size = sizeof(int));

    for (size_t i = 0; i < sizeof(data1)/sizeof(data1[0]); ++i)
        dynarr_append(&first, &data1[i]);

    for (size_t i = 0; i < sizeof(data2)/sizeof(data2[0]); ++i)
        dynarr_append(&second, &data2[i]);

    dynarr_t *result = dynarr_binary_merge(first, second, cmp_int_asc, NULL);

    ck_assert_uint_eq(dynarr_size(result), data_res_size);

    for (size_t i = 0; i < data_res_size; ++i)
        ck_assert_int_eq(*(int*)dynarr_get(result, i), data_res[i]);
}
END_TEST


Suite *dynarr_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Dynamic Array");

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
    tcase_add_test(tc_core, test_dynarr_spread_insert_inbetween);
    tcase_add_test(tc_core, test_dynarr_binary_find_insert_place);
    tcase_add_test(tc_core, test_dynarr_remove);
    tcase_add_test(tc_core, test_dynarr_remove_if);
    tcase_add_test(tc_core, test_dynarr_binary_insert);
    tcase_add_test(tc_core, test_dynarr_binary_find);
    tcase_add_test(tc_core, test_dynarr_binary_merge);
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

