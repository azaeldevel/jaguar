

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(PLUTON_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libjaguar.la

libjaguar_la_CXXFLAGS = $(JAGUAR_CFLGAS)
libjaguar_la_LIBADD = $(JAGUAR_LIBS)
libjaguar_la_SOURCES = jaguar.cc

bin_PROGRAMS = jaguar

jaguar_SOURCES = main.cc
jaguar_LDFLAGS = 
jaguar_LDADD = $(JAGUAR_LIBS) libjaguar.la

if NATIVE_WIN32
jaguar_LDFLAGS += -mwindows
endif
