noinst_LTLIBRARIES = libdynarr_funcs.la
libdynarr_funcs_la_SOURCES = dynarr.c dynarr.h
libdynarr_funcs_la_CFLAGS = -I$(top_srcdir)/vector/src
libdynarr_funcs_la_LDFLAGS = -L$(top_builddir)/vector/src

lib_LTLIBRARIES = libdynarr_static.la
if !MINGW
lib_LTLIBRARIES += libdynarr.la
endif

libdynarr_la_SOURCES =
libdynarr_la_LDFLAGS = -shared
libdynarr_la_LIBADD = libdynarr_funcs.la $(top_builddir)/vector/src/libvector.la
libdynarr_la_LIBS = $(CODE_COVERAGE_LIBS)
libdynarr_la_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)
libdynarr_la_CFLAGS = $(CODE_COVERAGE_CFLAGS)
libdynarr_la_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS)

libdynarr_static_la_SOURCES =
libdynarr_static_la_LDFLAGS = -static -lm
libdynarr_static_la_LIBADD = libdynarr_funcs.la $(top_builddir)/vector/src/libvector_static.la
libdynarr_static_la_LIBS = $(CODE_COVERAGE_LIBS)
libdynarr_static_la_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)
libdynarr_static_la_CFLAGS = $(CODE_COVERAGE_CFLAGS)
libdynarr_static_la_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS)

include_HEADERS = dynarr.h
