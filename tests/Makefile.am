
VALGRIND_memcheck_FLAGS = --leak-check=full --track-origins=yes
@VALGRIND_CHECK_RULES@

TESTS = dynarr_test
check_PROGRAMS = dynarr_test

dynarr_test_SOURCES = dynarr_test.c $(top_srcdir)/src/dynarr.h
dynarr_test_LDADD = $(top_builddir)/src/libdynarr_static.la \
					$(top_builddir)/vector/src/libvector_static.la \
					@CHECK_LIBS@
dynarr_test_LIBS = $(CODE_COVERAGE_LIBS)
dynarr_test_CPPFLAGS = -I$(top_srcdir)/vector/src/ $(CODE_COVERAGE_CPPFLAGS)
dynarr_test_CFLAGS = @CHECK_CFLAGS@ $(CODE_COVERAGE_CFLAGS)
dynarr_test_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS)

debug-dynarr-test: $(top_builddir)/src/libdynarr_static.la dynarr_test
	LD_LIBRARY_PATH=$(top_builddir)/srcs:/usr/local/lib CK_FORK=no gdb -tui dynarr_test

