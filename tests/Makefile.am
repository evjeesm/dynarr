
VALGRIND_memcheck_FLAGS = --leak-check=full --track-origins=yes
@VALGRIND_CHECK_RULES@

TESTS = dynarr_test
check_PROGRAMS = dynarr_test

dynarr_test_SOURCES = dynarr_test.c $(top_builddir)/src/dynarr.h
dynarr_test_CFLAGS = @CHECK_CFLAGS@ -I../vector/src/
dynarr_test_LDADD = $(top_builddir)/src/libdynarr_static.la $(top_builddir)/vector/src/libvector_static.la @CHECK_LIBS@
