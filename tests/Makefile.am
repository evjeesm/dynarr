
VALGRIND_memcheck_FLAGS = --leak-check=full --track-origins=yes
@VALGRIND_CHECK_RULES@

TESTS = dynarr_test dynarr_test_failures
check_PROGRAMS = dynarr_test dynarr_test_failures

dynarr_test_SOURCES = dynarr_test.c $(top_builddir)/src/dynarr.h
dynarr_test_CFLAGS = @CHECK_CFLAGS@ -I../vector/src/
dynarr_test_LDADD = $(top_builddir)/src/libdynarr.la @CHECK_LIBS@

dynarr_test_failures_SOURCES = dynarr_test_failures.c $(top_builddir)/src/dynarr.h
dynarr_test_failures_CFLAGS = @CHECK_CFLAGS@ -I../vector/src/
dynarr_test_failures_LDADD = $(top_builddir)/src/libdynarr.la @CHECK_LIBS@
