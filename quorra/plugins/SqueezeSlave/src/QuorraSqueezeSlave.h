/*
 * QuorraSqueezeSlave.h
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
 * along with com_mapfactory. If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on 14 mars 2013
 * By bozzo
 *
 **/

#ifndef QUORRASQUEEZESLAVE_H_
#define QUORRASQUEEZESLAVE_H_

#include <stdlib.h>
#include <glib.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>
#include <gio/gio.h>
#include <netdb.h>

#include "QuorraSqueezeSlaveObject.h"
#include "QuorraSqueezeSlaveGlue.h"

#define QUORRA_SQUEEZESLAVE_PATH "/org/bozzo/Quorra/plg/QuorraSqueezeSlaveObject"
#define QUORRA_SQUEEZESLAVE_SERVICE_NAME "org.bozzo.Quorra.plg.QuorraSqueezeSlaveObject"


gpointer quorra_plugin_run(gpointer data);


#endif /* QUORRASQUEEZESLAVE_H_ */
