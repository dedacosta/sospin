

AM_CPPFLAGS =-I$(top_srcdir)/include

 #defines AM_CPPFLAGS =-I$(top_srcdir)/include

# Defines which program executables will be produced
noinst_PROGRAMS=so4 so4_higherdim so10_v1 so10_v2 so10_144




#so4_LDADD = $(top_srcdir)/lib/libsospin.a
so4_LDADD = ../lib/libsospin.a
so4_SOURCES=so4.cpp
so4_higherdim_LDADD = ../lib/libsospin.a
so4_higherdim_SOURCES=so4_higherdim.cpp


so10_v1_LDADD = ../lib/libsospin.a
so10_v1_SOURCES=so10_v1.cpp
so10_v2_LDADD = ../lib/libsospin.a
so10_v2_SOURCES=so10_v2.cpp
so10_144_LDADD = ../lib/libsospin.a
so10_144_SOURCES=so10_144.cpp



clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	rm -f *.frm
