#define TESTING
#include <check.h>
#include "bin_search.c"

#suite ArabicToRoman
    #tcase "arabic to roman"
        #test test_ok
            ck_assert_str_eq(arabicToRoman(100), "C");
        #test test_out_of_bounds
            ck_assert_ptr_eq(arabicToRoman(1000), NULL);
