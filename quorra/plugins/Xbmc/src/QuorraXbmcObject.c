/*
 * QuorraXbmcObject.c
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
 * Created on 26 mars 2013
 * By bozzo
 *
 **/

#include "QuorraXbmcObject.h"


/*static guint signalId;*/

G_DEFINE_TYPE(QuorraXbmcObject, quorra_xbmc_object, G_TYPE_OBJECT)

static void quorra_xbmc_object_class_init (QuorraXbmcObjectClass * quorra_squeezeslave_class)
{
	g_type_class_add_private (quorra_squeezeslave_class, sizeof (QuorraXbmcObjectPrivate));

	/*signalId = g_signal_new("song_changed",
			G_OBJECT_CLASS_TYPE(quorra_squeezeslave_class),
			G_SIGNAL_RUN_LAST,
			0,
			NULL,
			NULL,
			g_cclosure_marshal_VOID__INT,
			G_TYPE_NONE,
			1,
			G_TYPE_INT);

	g_print("dummy_object_class_init : signalId = %d\n", signalId);*/
}

static void quorra_xbmc_object_init (QuorraXbmcObject * quorra_xbmc)
{
	GError ** error = NULL;
	QuorraXbmcObjectPrivate * priv;
	int fd;

	dbus_g_object_type_install_info (QUORRA_XBMCOBJ_TYPE,	&dbus_glib_quorra_xbmc_object_object_info);

	quorra_xbmc->priv = priv = QUORRA_XBMCOBJ_GET_PRIVATE (quorra_xbmc);
	quorra_xbmc->priv->socket = NULL;
	quorra_xbmc->priv->channel = NULL;

	if (! (squeezeserver_connect(quorra_xbmc,"r4.bozzo.org",9090,NULL,error)))
	{
		g_error("quorra_xbmc_object_init : connect failed!");
		return;
	}

	if (! (fd = g_socket_get_fd(quorra_xbmc->priv->socket)))
	{
		g_error("quorra_xbmc_object_init : get FD failed!");
		return;
	}

	quorra_xbmc->priv->channel = g_io_channel_unix_new(fd);
}


GIOChannel * quorra_xbmc_object_getChannel(QuorraXbmcObject * obj)
{
	QuorraXbmcObjectPrivate * priv;

	priv = QUORRA_XBMCOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->channel;
	}
	return NULL;
}

GSocket * quorra_xbmc_object_getSocket(QuorraXbmcObject * obj)
{
	QuorraXbmcObjectPrivate * priv;

	priv = QUORRA_XBMCOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		return priv->socket;
	}
	return NULL;
}

void quorra_xbmc_object_setSocket(QuorraXbmcObject * obj, GSocket * socket)
{
	QuorraXbmcObjectPrivate * priv;

	priv = QUORRA_XBMCOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->socket = socket;
	}
}

gboolean quorra_xbmc_action_playlist(QuorraXbmcObject * obj, gchar ** cmd)
{
	if (cmd == NULL)
	{
		g_error("quorra_xbmc_action_playlist : cmd is NULL!");
		return FALSE;
	}
	/*songChanged((GObject *)obj,1,"test");*/


	return TRUE;
}


gboolean quorra_xbmc_object_listen_callback (GIOChannel * source, GIOCondition condition, gpointer data)
{
	gsize bytes_read;
	gchar buff[1024];
	gint i;
	gchar ** tokens;
	gchar * tmp;
	QuorraXbmcObject * obj;

	if (source == NULL)
	{
		g_error("quorra_xbmc_object_listen_callback : source is NULL!");
		return FALSE;
	}

	if (data == NULL)
		{
			g_error("quorra_xbmc_object_listen_callback : data is NULL!");
			return FALSE;
		}

	obj = (QuorraXbmcObject *)data;

	do
	{
		g_io_channel_read_chars (source, buff, 1024, &bytes_read, NULL);
		if (bytes_read)
		{
			/*tmp = g_strndup(buff,bytes_read);
			tokens = g_strsplit(tmp," ",0);
			i = g_strv_length (tokens);
			if (i >= 2)
			{
				if (g_strcmp0 (tokens[1],"playlist") == 0)
				{
					quorra_xbmc_action_playlist(obj,tokens);
				}
			}

			for (i = 0; tokens[i] != NULL; i++)
			{
				g_print("--> %s\n",g_uri_unescape_string(tokens[i],""));
			}
			free(tmp);
			g_strfreev(tokens);
			g_print ("\n");*/
		}
	}
	while (bytes_read);

	return TRUE;
}

gboolean quorra_xbmc_stop(QuorraXbmcObject * obj, gint playerid, gboolean * success, GError **error)
{
	g_print ("quorra_xbmc_stop -> %d\n",playerid);
	*success = TRUE;
	return TRUE;
}

gboolean quorra_xbmc_playpause(QuorraXbmcObject * obj, gint playerid, gboolean * success, GError **error)
{
	g_print ("quorra_xbmc_playpause -> %d\n",playerid);
	*success = TRUE;
	return TRUE;
}


