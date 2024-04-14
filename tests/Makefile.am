
VALGRIND_memcheck_FLAGS = --leak-check=full --track-origins=yes
@VALGRIND_CHECK_RULES@

TESTS = dynarr_test
check_PROGRAMS = dynarr_test

dynarr_test_SOURCES = dynarr_test.c $(top_builddir)/src/dynarr.h
dynarr_test_CFLAGS = @CHECK_CFLAGS@ -I../vector/src/
dynarr_test_LDADD = $(top_builddir)/src/libdynarr.la @CHECK_LIBS@

# vector_test_other_SOURCES = vector_test_other.c $(top_builddir)/src/vector.h
# vector_test_other_CFLAGS = @CHECK_CFLAGS@
# vector_test_other_LDADD = $(top_builddir)/src/libvector.la @CHECK_LIBS@
# 
# vector_test_failures_SOURCES = vector_test_failures.c $(top_builddir)/src/vector.h
# vector_test_failures_CFLAGS = @CHECK_CFLAGS@ -DMOCK_MALLOC
# vector_test_failures_LDADD = $(top_builddir)/src/libvector_mock.la @CHECK_LIBS@

# VALGRIND_SUPPRESSIONS_FILES = my-project.supp
# EXTRA_DIST = my-project.supp
