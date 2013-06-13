/*
 * QuorraMappingObject.c
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
#include "QuorraMappingObject.h"

G_DEFINE_TYPE(QuorraMappingObject, quorra_mapping_object, G_TYPE_OBJECT)

static void quorra_mapping_object_class_init (QuorraMappingObjectClass * quorra_mapping_class)
{
	g_type_class_add_private (quorra_mapping_class, sizeof (QuorraMappingObjectPrivate));
}

static void quorra_mapping_object_init (QuorraMappingObject * quorra_mapping)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (quorra_mapping);
	if (priv)
	{
		priv->data = g_hash_table_new(g_str_hash,g_str_equal);
	}
}

DBusGConnection * quorra_mapping_object_getConnection(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->connection;
	}
	return NULL;
}

gboolean quorra_mapping_object_setConnection(QuorraMappingObject * obj,DBusGConnection * connection)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->connection = connection;
		return TRUE;
	}
	return FALSE;
}

gchar * quorra_mapping_object_getSignalName(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->signalName;
	}
	return NULL;
}

gboolean quorra_mapping_object_setSignalName(QuorraMappingObject * obj,gchar * signalName)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->signalName = signalName;
		return TRUE;
	}
	return FALSE;
}

gchar * quorra_mapping_object_getQuorraPath(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->quorraPath;
	}
	return NULL;
}

gboolean quorra_mapping_object_setQuorraPath(QuorraMappingObject * obj,gchar * quorraPath)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->quorraPath = quorraPath;
		return TRUE;
	}
	return FALSE;
}

gchar * quorra_mapping_object_getQuorraServiceName(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->quorraServiceName;
	}
	return NULL;
}

gboolean quorra_mapping_object_setQuorraServiceName(QuorraMappingObject * obj,gchar * quorraServiceName)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->quorraServiceName = quorraServiceName;
		return TRUE;
	}
	return FALSE;
}

gchar * quorra_mapping_object_getQuorraInterfaceName(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->quorraInterfaceName;
	}
	return NULL;
}

gboolean quorra_mapping_object_setQuorraInterfaceName(QuorraMappingObject * obj,gchar * quorraInterfaceName)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->quorraInterfaceName = quorraInterfaceName;
		return TRUE;
	}
	return FALSE;
}

GHashTable * quorra_mapping_object_getData(QuorraMappingObject * obj)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->data;
	}
	return NULL;
}

gpointer quorra_mapping_object_findData(QuorraMappingObject * obj, gchar * key)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return g_hash_table_lookup(priv->data, key);
	}
	return NULL;
}

gboolean quorra_mapping_object_setData(QuorraMappingObject * obj,GHashTable * data)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->data = data;
		return TRUE;
	}
	return FALSE;
}

gboolean quorra_mapping_object_insertData(QuorraMappingObject * obj,gchar * key, gpointer value)
{
	QuorraMappingObjectPrivate * priv;

	priv = QUORRA_MAPPINGOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		g_hash_table_insert(priv->data, key, value);
		return TRUE;
	}
	return FALSE;
}

