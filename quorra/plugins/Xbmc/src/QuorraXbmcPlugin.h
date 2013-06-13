/*
 * QuorraXbmcPlugin.h
 *
 * This file is part of Quorra.
 *
 * Quorra is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Quorra is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Quorra. If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on 27 mars 2013
 * By bozzo
 *
 **/

#ifndef QUORRAXBMCPLUGIN_H_
#define QUORRAXBMCPLUGIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>
#include <gio/gio.h>
#include <netdb.h>
#include <glib/gprintf.h>

#include "QuorraMappingObject.h"
#include "QuorraXbmcObject.h"
#include "QuorraXbmcGlue.h"
#include "Xbmc.h"

#define QUORRA_XBMC_PATH "/org/bozzo/Quorra/plg/QuorraXbmcObject"
#define QUORRA_XBMC_SERVICE_NAME "org.bozzo.Quorra.plg.QuorraXbmcObject"


gpointer quorra_plugin_run(gpointer data);


#endif /* QUORRAXBMCPLUGIN_H_ */
