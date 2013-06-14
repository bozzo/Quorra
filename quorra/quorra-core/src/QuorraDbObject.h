/*
 * QuorraDbObject.h
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
 * Created on 14 juin 2013
 * By bozzo
 *
 **/

#ifndef QUORRADBOBJECT_H_
#define QUORRADBOBJECT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>
#include <netdb.h>
#include <glib-object.h>
#include <libpq-fe.h>

typedef struct _QuorraDbObject QuorraDbObject;
typedef struct _QuorraDbObjectClass QuorraDbObjectClass;
typedef struct _QuorraDbObjectPrivate QuorraDbObjectPrivate;

#define QUORRA_DBOBJ_TYPE 				(quorra_db_object_get_type ())
#define QUORRA_DBOBJ_CLASS(klass) 		(G_TYPE_CHECK_CLASS_CAST ((klass), QUORRA_DBOBJ_TYPE, QuorraDbObject))
#define QUORRA_DBOBJ_GET_PRIVATE(obj) 	(G_TYPE_INSTANCE_GET_PRIVATE ((obj), QUORRA_DBOBJ_TYPE, QuorraDbObjectPrivate))

#define QUORRA_DBOBJ(obj)					(G_TYPE_CHECK_INSTANCE_CAST ((obj), QUORRA_DBOBJ_TYPE, QuorraDbObject))
#define IS_QUORRA_DBOBJ(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), QUORRA_DBOBJ_TYPE))
#define IS_QUORRA_DBOBJ_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), QUORRA_DBOBJ_TYPE))
#define QUORRA_DBOBJ_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), QUORRA_DBOBJ_TYPE, QuorraDbObjectClass))

GType quorra_db_object_get_type (void);


struct _QuorraDbObjectPrivate
{
	PGconn * connection;
};

struct _QuorraDbObject
{
	GObject parent;

	/*< private >*/
	QuorraDbObjectPrivate * priv;
};

struct _QuorraDbObjectClass
{
	GObjectClass parent;
};

/*
 * Methods definition
 */
PGconn * quorra_db_object_getConnection(QuorraDbObject * obj);
gboolean quorra_db_object_initConnection(QuorraDbObject * obj,
										gchar * pghost,
										gchar *pgport,
										gchar *dbName,
										gchar *login,
										gchar *pwd);

gboolean quorra_db_object_closeConnection(QuorraDbObject * obj);

#endif /* QUORRADBOBJECT_H_ */
