# what flags you want to pass to the C compiler & linker
AM_CFLAGS = $(GLIB_CFLAGS) -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/lib/glib-2.0/include -I/usr/include/dbus-1.0 --pedantic -Wall -O3 -rdynamic
AM_LDFLAGS =  $(GLIB_LIBS) -lgthread-2.0 -lglib-2.0 -ldbus-1 -lgobject-2.0 -ldbus-glib-1 -lgmodule-2.0
INCLUDES = -DG_LOG_DOMAIN=\"Quorra\"
# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = quorra
quorra_SOURCES = quorra.c
