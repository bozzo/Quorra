/*
 * QuorraDbObject.c
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
#include "QuorraDbObject.h"

G_DEFINE_TYPE(QuorraDbObject, quorra_db_object, G_TYPE_OBJECT)

static void quorra_db_object_class_init (QuorraDbObjectClass * quorra_db_class)
{
	g_type_class_add_private (quorra_db_class, sizeof (QuorraDbObjectPrivate));
}

static void quorra_db_object_init (QuorraDbObject * quorra_db)
{
	QuorraDbObjectPrivate * priv;

	priv = QUORRA_DBOBJ_GET_PRIVATE (quorra_db);
	if (priv)
	{
		priv->connection = NULL;
	}
}

PGconn * quorra_db_object_getConnection(QuorraDbObject * obj)
{
	QuorraDbObjectPrivate * priv;

	priv = QUORRA_DBOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->connection;
	}
	return NULL;
}

gboolean quorra_db_object_initConnection(QuorraDbObject * obj,
										gchar * pghost,
										gchar * pgport,
										gchar * dbName,
										gchar * login,
										gchar * pwd)
{
	QuorraDbObjectPrivate * priv;

	if (dbName == NULL)
	{
		g_warning("Connection to database failed: database isn't set!");
		return FALSE;
	}

	priv = QUORRA_DBOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->connection = PQsetdbLogin(pghost,pgport,NULL,NULL,dbName,login,pwd);

		/* Check to see that the backend connection was successfully made */
		if (PQstatus(priv->connection) != CONNECTION_OK)
		{
			g_warning("Connection to database failed: %s", PQerrorMessage(priv->connection));
		    PQfinish(priv->connection);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

gboolean quorra_db_object_closeConnection(QuorraDbObject * obj)
{
	QuorraDbObjectPrivate * priv;

	priv = QUORRA_DBOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		PQfinish(priv->connection);
		return TRUE;
	}
	return FALSE;
}
