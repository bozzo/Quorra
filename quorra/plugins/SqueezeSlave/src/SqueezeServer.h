/*
 * SqueezeServer.h
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
 * Created on 20 mars 2013
 * By bozzo
 *
 **/

#ifndef SQUEEZESERVER_H_
#define SQUEEZESERVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>
#include <netdb.h>

#include "QuorraSqueezeSlaveObject.h"

#define SQUEEZE_DEFAULT_PORT 9090

gboolean squeezeserver_connect(QuorraSqueezeSlaveObject * obj, gchar * host, gint port, GCancellable * cancellable, GError ** error);

gboolean squeezeserver_close(QuorraSqueezeSlaveObject * obj, GError ** error);

gchar * squeezeserver_execute(QuorraSqueezeSlaveObject * obj, gchar * cmd, GCancellable * cancellable, GError ** error);

#endif /* SQUEEZESERVER_H_ */
