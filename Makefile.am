ACLOCAL_AMFLAGS = -I m4 -I/usr/share/aclocal
SUBDIRS = vector src tests

include $(top_srcdir)/aminclude_static.am
clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

# debug-vector-test-other: ./src/libvector.la ./tests/vector_test_other
# 	LD_LIBRARY_PATH=./src/.libs:/usr/local/lib CK_FORK=no gdb -tui ./tests/.libs/vector_test_other
# 
# debug-vector-test-failures: ./src/libvector_mock.la ./tests/vector_test_failures
# 	LD_LIBRARY_PATH=./src/.libs:/usr/local/lib CK_FORK=no gdb -tui ./tests/.libs/vector_test_failures
