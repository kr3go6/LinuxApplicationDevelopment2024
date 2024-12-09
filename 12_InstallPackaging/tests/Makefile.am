TESTS = test_bin_search
check_PROGRAMS = test_bin_search

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir) @CHECK_CFLAGS@
LDADD = @CHECK_LIBS@
