
VALGRIND_memcheck_FLAGS = --leak-check=full --track-origins=yes
@VALGRIND_CHECK_RULES@

TESTS = dynarr_test
check_PROGRAMS = dynarr_test

dynarr_test_SOURCES = dynarr_test.c $(top_srcdir)/src/dynarr.h
dynarr_test_LDADD = $(top_builddir)/src/libdynarr.la \
					$(top_builddir)/vector/src/libvector.la \
					@CHECK_LIBS@
dynarr_test_LIBS = $(CODE_COVERAGE_LIBS)
dynarr_test_CPPFLAGS = -I$(top_srcdir)/vector/src/ $(CODE_COVERAGE_CPPFLAGS)
dynarr_test_CFLAGS = @CHECK_CFLAGS@ $(CODE_COVERAGE_CFLAGS)
dynarr_test_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS)

