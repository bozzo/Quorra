# what flags you want to pass to the C compiler & linker
AM_CFLAGS = $(GLIB_CFLAGS) -I../../../quorra-core/src -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/lib64/glib-2.0/include -I/usr/include/dbus-1.0 --pedantic -Wall -O3 -rdynamic
AM_LDFLAGS =  $(GLIB_LIBS) -lgthread-2.0 -lglib-2.0 -ldbus-1 -lgobject-2.0 -ldbus-glib-1 -lgio-2.0
INCLUDES = -DG_LOG_DOMAIN=\"Quorra\"
ACLOCAL_AMFLAGS = -I m4

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
#bin_PROGRAMS = quorra_plg_squeezeslave
#quorra_plg_squeezeslave_SOURCES = SqueezeServer.c SqueezeServer.h QuorraSqueezeSlave.c QuorraSqueezeSlave.h QuorraSqueezeSlaveObject.h QuorraSqueezeSlaveGlue.h
lib_LTLIBRARIES = plg_hue-1.0.la
#plg_xbmc_1_0_la_SOURCES = QuorraHueObject.h QuorraHueObject.c QuorraHuePlugin.c QuorraHuePlugin.h Hue.c Hue.h QuorraHueGlue.h
plg_hue_1_0_la_SOURCES = QuorraHueGlue.h
plg_hue_1_0_la_LDFLAGS = -module
