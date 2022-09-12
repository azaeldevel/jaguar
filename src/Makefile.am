## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(PLUTON_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = pluton

pluton_SOURCES = \
	main.cc

pluton_LDFLAGS = 

pluton_LDADD = $(PLUTON_LIBS)


if NATIVE_WIN32
pluton_LDFLAGS += -mwindows
endif
