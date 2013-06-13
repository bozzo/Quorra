/*
 * QuorraMappingObject.h
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
 * Created on 13 juin 2013
 * By bozzo
 *
 **/

#ifndef QUORRAMAPPINGOBJECT_H_
#define QUORRAMAPPINGOBJECT_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>
#include <netdb.h>
#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>

typedef struct _QuorraMappingObject QuorraMappingObject;
typedef struct _QuorraMappingObjectClass QuorraMappingObjectClass;
typedef struct _QuorraMappingObjectPrivate QuorraMappingObjectPrivate;

#define QUORRA_MAPPINGOBJ_TYPE 				(quorra_mapping_object_get_type ())
#define QUORRA_MAPPINGOBJ_CLASS(klass) 		(G_TYPE_CHECK_CLASS_CAST ((klass), QUORRA_MAPPINGOBJ_TYPE, QuorraMappingObject))
#define QUORRA_MAPPINGOBJ_GET_PRIVATE(obj) 	(G_TYPE_INSTANCE_GET_PRIVATE ((obj), QUORRA_MAPPINGOBJ_TYPE, QuorraMappingObjectPrivate))

#define QUORRA_MAPPINGOBJ(obj)					(G_TYPE_CHECK_INSTANCE_CAST ((obj), QUORRA_MAPPINGOBJ_TYPE, QuorraMappingObject))
#define IS_QUORRA_MAPPINGOBJ(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), QUORRA_MAPPINGOBJ_TYPE))
#define IS_QUORRA_MAPPINGOBJ_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), QUORRA_MAPPINGOBJ_TYPE))
#define QUORRA_MAPPINGOBJ_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), QUORRA_MAPPINGOBJ_TYPE, QuorraMappingObjectClass))

GType quorra_mapping_object_get_type (void);

GType quorra_mapping_playpause_get_type (void);
GType quorra_mapping_stop_get_type (void);


struct _QuorraMappingObjectPrivate
{
	DBusGConnection * connection;
	gchar * signalName;
	gchar * quorraPath;
	gchar * quorraServiceName;
	gchar * quorraInterfaceName;

	GHashTable * data;
};

struct _QuorraMappingObject
{
	GObject parent;

	/*< private >*/
	QuorraMappingObjectPrivate * priv;
};

struct _QuorraMappingObjectClass
{
	GObjectClass parent;
};

/*
 * Methods definition
 */
DBusGConnection * quorra_mapping_object_getConnection(QuorraMappingObject * obj);
gboolean quorra_mapping_object_setConnection(QuorraMappingObject * obj,DBusGConnection * connection);

gchar * quorra_mapping_object_getSignalName(QuorraMappingObject * obj);
gboolean quorra_mapping_object_setSignalName(QuorraMappingObject * obj,gchar * signalName);

gchar * quorra_mapping_object_getQuorraPath(QuorraMappingObject * obj);
gboolean quorra_mapping_object_setQuorraPath(QuorraMappingObject * obj,gchar * quorraPath);

gchar * quorra_mapping_object_getQuorraServiceName(QuorraMappingObject * obj);
gboolean quorra_mapping_object_setQuorraServiceName(QuorraMappingObject * obj,gchar * quorraServiceName);

gchar * quorra_mapping_object_getQuorraInterfaceName(QuorraMappingObject * obj);
gboolean quorra_mapping_object_setQuorraInterfaceName(QuorraMappingObject * obj,gchar * quorraInterfaceName);

GHashTable * quorra_mapping_object_getData(QuorraMappingObject * obj);
gpointer quorra_mapping_object_findData(QuorraMappingObject * obj, gchar * key);
gboolean quorra_mapping_object_setData(QuorraMappingObject * obj,GHashTable * data);
gboolean quorra_mapping_object_insertData(QuorraMappingObject * obj,gchar * key, gpointer value);

#endif /* QUORRAMAPPINGOBJECT_H_ */
