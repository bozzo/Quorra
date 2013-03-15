/*
 * QuorraSqueezeSlaveObject.h
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

#ifndef QUORRA_SQUEEZESLAVE_OBJECT_H_
#define QUORRA_SQUEEZESLAVE_OBJECT_H_

#include <glib-object.h>

typedef struct QuorraSqueezeSlaveObject QuorraSqueezeSlaveObject;
typedef struct QuorraSqueezeSlaveObjectClass QuorraSqueezeSlaveObjectClass;

GType stop_get_type (void);
GType pause_get_type (void);


struct QuorraSqueezeSlaveObject
{
	GObject parent;
};

struct QuorraSqueezeSlaveObjectClass
{
	GObjectClass parent;
};

#define QUORRA_SQUEEZESLAVEOBJ_TYPE (quorra_squeezeslave_object_get_type ())
/*#define QUORRA_SQUEEZESLAVEOBJ_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HELLOWORLD_TYPE, QuorraSqueezeSlaveObjectClass))*/

gboolean stop(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 time, gboolean * success, GError **error);

gboolean pause(QuorraSqueezeSlaveObject * obj, gchar * name, gboolean * success, GError **error);

#endif /* QUORRA_SQUEEZESLAVE_OBJECT_H_ */
