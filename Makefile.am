
AUTOMAKE_OPTIONS = foreign


SUBDIRS = src examples 

#in order to maintain so10.h in tools directory!
myincludesubdir=$(pkgincludedir)/tools
pkginclude_HEADERS = $(top_srcdir)/include/progressStatus.h $(top_srcdir)/include/dlist.h  $(top_srcdir)/include/braket.h $(top_srcdir)/include/timer.h $(top_srcdir)/include/index.h $(top_srcdir)/include/form.h  $(top_srcdir)/include/son.h $(top_srcdir)/include/enum.h
myincludesub_HEADERS = $(top_srcdir)/include/tools/so10.h


#MAINTAINERCLEANFILES = Makefile.in

include Makefile.am.doxygen
