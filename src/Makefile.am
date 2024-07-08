noinst_LTLIBRARIES = libdynarr_funcs.la
lib_LTLIBRARIES = libdynarr.la libdynarr_static.la


libdynarr_funcs_la_SOURCES = dynarr.c dynarr.h
libdynarr_funcs_la_CFLAGS = -I$(top_srcdir)/vector/src
libdynarr_funcs_la_LDFLAGS = -L$(top_builddir)/vector/src

libdynarr_la_SOURCES =
libdynarr_la_LDFLAGS = -shared
libdynarr_la_LIBADD = libdynarr_funcs.la $(top_builddir)/vector/src/libvector.la

libdynarr_static_la_SOURCES =
libdynarr_static_la_LDFLAGS = -static
libdynarr_static_la_LIBADD = libdynarr_funcs.la $(top_builddir)/vector/src/libvector_static.la

include_HEADERS = dynarr.h
