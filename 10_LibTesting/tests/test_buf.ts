#include <check.h>
#include "buf.h"

#suite Buf
    #tcase "Initialization, buf_free"
        #test test_init
            float *a = 0;
            ck_assert_int_eq(buf_capacity(a), 0);
            ck_assert_int_eq(buf_size(a), 0);
            buf_free(a);

        #test test_push_clear_free
            float *a = 0;
            float expected_val = 1.3f;
            buf_push(a, expected_val);
            ck_assert_int_eq(buf_size(a), 1);
            ck_assert_float_eq(a[0], expected_val);

            buf_clear(a);
            ck_assert_int_eq(buf_size(a), 0);
            ck_assert_ptr_nonnull(a);
            buf_free(a);
            ck_assert_ptr_null(a);

        #test test_clearing_null
            float *a = 0;
            buf_clear(a);
            ck_assert_int_eq(buf_size(a), 0);
            ck_assert_ptr_null(a);

    #tcase "bush_puf, [] operator"
        #test test_multiple_push
            long *ai = 0;
            int expected_sz = 10000;
            for (int i = 0; i < expected_sz; i++)
                buf_push(ai, i);
            ck_assert_int_eq(buf_size(ai), expected_sz);

            int matched = 0;
            for (int i = 0; i < expected_sz; i++) {
                matched += ai[i] == i;
            }
            ck_assert_int_eq(matched, expected_sz);
            buf_free(ai);

    #tcase "buf_grow(), buf_trunc()"
        #test buf_grow
            long *ai = 0;
            int expected_capacity = 1000;
            buf_grow(ai, expected_capacity);
            ck_assert_int_eq(buf_capacity(ai), expected_capacity);
            ck_assert_int_eq(buf_size(ai), 0);
            buf_free(ai);

        #test buf_doesnt_shrink
            long *ai = 0;
            buf_push(ai, 0);
            buf_push(ai, 0);
            buf_push(ai, 0);
            int expected_sz = 3;
            int min_expected_capacity = 3;
            buf_grow(ai, 1);
            ck_assert_int_ge(buf_capacity(ai), min_expected_capacity);
            ck_assert_int_eq(buf_size(ai), expected_sz);
            buf_free(ai);

        #test buf_trunc
            long *ai = 0;
            int init_capacity = 1000, expected_capacity = 100;
            buf_grow(ai, init_capacity);
            buf_trunc(ai, expected_capacity);
            ck_assert_int_eq(buf_capacity(ai), expected_capacity);
            buf_free(ai);

    #tcase "buf_pop"
        #test test_buf_pop
            float *a = 0;
            int sz = 4;
            float values[] = {1.1f, 1.2f, 1.3f, 1.4f};

            for (int i = 0; i < sz; i++) {
                buf_push(a, values[i]);
            }
            
            ck_assert_int_eq(buf_size(a), sz);

            for (int i = 0; i < sz; i++) {
                ck_assert_int_eq(buf_pop(a), values[sz - i - 1]);
            }

            ck_assert_int_eq(buf_size(a), 0);
            buf_free(a);
