noinst_LTLIBRARIES = libdynarr_funcs.la
lib_LTLIBRARIES = libdynarr.la libdynarr_static.la


libdynarr_funcs_la_SOURCES = dynarr.c dynarr.h vector.h
libdynarr_funcs_la_CFLAGS = -I../vector/src


libdynarr_la_SOURCES =
libdynarr_la_CFLAGS = -I../vector/src/
libdynarr_la_LDFLAGS = -shared
libdynarr_la_LIBADD = libdynarr_funcs.la

libdynarr_static_la_SOURCES =
libdynarr_static_la_LDFLAGS = -static
libdynarr_static_la_LIBADD = libdynarr_funcs.la
