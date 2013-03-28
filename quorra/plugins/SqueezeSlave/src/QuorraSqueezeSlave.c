/*
 * QuorraSqueezeSlave.c
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
 * Created on 14 mars 2013
 * By bozzo
 *
 **/
#include "QuorraSqueezeSlave.h"


static guint signalId;

G_DEFINE_TYPE(QuorraSqueezeSlaveObject, quorra_squeezeslave_object, G_TYPE_OBJECT)

static void quorra_squeezeslave_object_class_init (QuorraSqueezeSlaveObjectClass * quorra_squeezeslave_class)
{
	g_type_class_add_private (quorra_squeezeslave_class, sizeof (QuorraSqueezeSlaveObjectPrivate));

	signalId = g_signal_new("song_changed",
			G_OBJECT_CLASS_TYPE(quorra_squeezeslave_class),
			G_SIGNAL_RUN_LAST,
			0,
			NULL,
			NULL,
			g_cclosure_marshal_VOID__INT,
			G_TYPE_NONE,
			1,
			G_TYPE_INT);

	g_print("dummy_object_class_init : signalId = %d\n", signalId);
}

static void quorra_squeezeslave_object_init (QuorraSqueezeSlaveObject * quorra_squeezeslave)
{
	GError ** error = NULL;
	QuorraSqueezeSlaveObjectPrivate * priv;
	int fd;

	dbus_g_object_type_install_info (QUORRA_SQUEEZESLAVEOBJ_TYPE,	&dbus_glib_quorra_squeezeslave_object_object_info);

	quorra_squeezeslave->priv = priv = QUORRA_SQUEEZESLAVEOBJ_GET_PRIVATE (quorra_squeezeslave);
	quorra_squeezeslave->priv->socket = NULL;
	quorra_squeezeslave->priv->channel = NULL;

	if (! (squeezeserver_connect(quorra_squeezeslave,"millenium.bozzo.org",9090,NULL,error)))
	{
		g_error("quorra_squeezeslave_object_init : connect failed!");
		return;
	}

	if (! (fd = g_socket_get_fd(quorra_squeezeslave->priv->socket)))
	{
		g_error("quorra_squeezeslave_object_init : get FD failed!");
		return;
	}

	quorra_squeezeslave->priv->channel = g_io_channel_unix_new(fd);
}


GIOChannel * quorra_squeezeslave_object_getChannel(QuorraSqueezeSlaveObject * obj)
{
	QuorraSqueezeSlaveObjectPrivate * priv;

	priv = QUORRA_SQUEEZESLAVEOBJ_GET_PRIVATE (obj);

	if (priv)
	{
		return priv->channel;
	}
	return NULL;
}

GSocket * quorra_squeezeslave_object_getSocket(QuorraSqueezeSlaveObject * obj)
{
	QuorraSqueezeSlaveObjectPrivate * priv;

	priv = QUORRA_SQUEEZESLAVEOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		return priv->socket;
	}
	return NULL;
}

void quorra_squeezeslave_object_setSocket(QuorraSqueezeSlaveObject * obj, GSocket * socket)
{
	QuorraSqueezeSlaveObjectPrivate * priv;

	priv = QUORRA_SQUEEZESLAVEOBJ_GET_PRIVATE (obj);
	if (priv)
	{
		priv->socket = socket;
	}
}

gboolean quorra_squeezeslave_action_playlist(QuorraSqueezeSlaveObject * obj, gchar ** cmd)
{
	if (cmd == NULL)
	{
		g_error("quorra_squeezeslave_action_playlist : cmd is NULL!");
		return FALSE;
	}
	songChanged((GObject *)obj,1,"test");


	return TRUE;
}


gboolean quorra_squeezeslave_object_listen_callback (GIOChannel * source, GIOCondition condition, gpointer data)
{
	gsize bytes_read;
	gchar buff[1024];
	gint i;
	gchar ** tokens;
	gchar * tmp;
	QuorraSqueezeSlaveObject * obj;

	if (source == NULL)
	{
		g_error("quorra_squeezeslave_object_listen_callback : source is NULL!");
		return FALSE;
	}

	if (data == NULL)
		{
			g_error("quorra_squeezeslave_object_listen_callback : data is NULL!");
			return FALSE;
		}

	obj = (QuorraSqueezeSlaveObject *)data;

	do
	{
		g_io_channel_read_chars (source, buff, 1024, &bytes_read, NULL);
		if (bytes_read)
		{
			tmp = g_strndup(buff,bytes_read);
			tokens = g_strsplit(tmp," ",0);
			i = g_strv_length (tokens);
			if (i >= 2)
			{
				if (g_strcmp0 (tokens[1],"playlist") == 0)
				{
					quorra_squeezeslave_action_playlist(obj,tokens);
				}
			}

			for (i = 0; tokens[i] != NULL; i++)
			{
				g_print("--> %s\n",g_uri_unescape_string(tokens[i],""));
			}
			free(tmp);
			g_strfreev(tokens);
			g_print ("\n");
		}
	}
	while (bytes_read);

	return TRUE;
}

gboolean songChanged(GObject *obj,gint id, gchar * name)
{
	g_print("song_changed!\n");
	g_signal_emit(obj, signalId, 0, 1);
	return TRUE;
}

gboolean quorra_squeezeslave_listen(QuorraSqueezeSlaveObject * obj, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,"listen 1\n",NULL,error))
	{
		g_error("quorra_squeezeslave_pause : execute failed!");

		*success = FALSE;
		return FALSE;
	}

	*success = TRUE;
	return TRUE;
}

gboolean quorra_squeezeslave_stop(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 time, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,g_strconcat(name," stop\n",NULL),NULL,error))
	{
		g_print("quorra_squeezeslave_pause : execute failed!");

		*success = FALSE;
		return FALSE;
	}

	if (! squeezeserver_close(obj,error))
	{
		g_error("quorra_squeezeslave_stop : close failed!");

		*success = FALSE;
		return FALSE;
	}

	g_print ("quorra_squeezeslave_stop -> %s - %d sec\n",name,time);
	*success = TRUE;
	return TRUE;
}

gboolean quorra_squeezeslave_nextsong(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 hops, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,g_strdup_printf ("%s playlist index +%d",name,hops),NULL,error))
	{
		g_error("quorra_squeezeslave_nextsong : execute failed!");

		*success = FALSE;
		return FALSE;
	}

	g_print ("quorra_squeezeslave_nextsong -> %s %d hops\n",name,hops);
	*success = TRUE;
	return TRUE;
}

gboolean quorra_squeezeslave_pause(QuorraSqueezeSlaveObject * obj, gchar * name, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,g_strconcat(name," pause\n",NULL),NULL,error))
	{
		g_error("quorra_squeezeslave_pause : execute failed!");

		*success = FALSE;
		return FALSE;
	}

	g_print ("quorra_squeezeslave_pause -> %s\n",name);
	*success = TRUE;
	return TRUE;
}

void die (const char *prefix, GError *error)
{
	g_error("%s: %s", prefix, error->message);
	g_error_free (error);
	exit(1);
}

gpointer quorra_plugin_run(gpointer data)
{
	DBusGConnection *connection;
	GError *error = NULL;
	GObject *obj;
	DBusGProxy *driver_proxy;
	guint32 request_name_ret;
	GMainLoop * loop;
	GIOChannel * channel;
	gboolean success;
	gpointer * dataptr;

	g_type_init();

	loop = g_main_loop_new(NULL, FALSE);

	/*connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);

	if (connection == NULL)
	{
		die ("Failed to open connection to bus", error);
	}*/
	dataptr = (gpointer *)data;
	connection = (DBusGConnection *)(dataptr[0]);
	/*driver_proxy = (DBusGProxy *)(dataptr[1]);*/

	obj = g_object_new (QUORRA_SQUEEZESLAVEOBJ_TYPE, NULL);

	/* Note : l’appel à cette fonction va appeler les
	 * fonctions définies plus haut :
	 * - dummy_object_class_init
	 * - dummy_object_init
	 */

	dbus_g_connection_register_g_object(connection, QUORRA_SQUEEZESLAVE_PATH, obj);

	/* Une fois cet appel effectué :
	 * - les propriétés et les signaux sont
	 * accessibles &grave; distance.
	 * - les méthodes ne seront accessibles si, et
	 * seulement si le développeur n’a pas oublié l’appel
	 * &grave; l’installation de l’introspection. (cf un peu plus haut
	 * dbus_g_object_type_install_info)
	 */
	/* Récupération d’un proxy sur le bus */
	driver_proxy = dbus_g_proxy_new_for_name (connection, DBUS_SERVICE_DBUS, DBUS_PATH_DBUS, DBUS_INTERFACE_DBUS);

	/* On essaie de s’enregistrer sur le bus */
	if (!org_freedesktop_DBus_request_name (driver_proxy, QUORRA_SQUEEZESLAVE_SERVICE_NAME,	0, &request_name_ret, &error))
	{
		die ("Failed to get name", error);
	}

	if (request_name_ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
	{
		g_error ("Got result code %u from requesting name", request_name_ret);
		return NULL;
	}

	g_print ("GLib test service has name ‘%s’\n", QUORRA_SQUEEZESLAVE_SERVICE_NAME);
	g_print ("GLib test service entering main loop\n");

	/* Envoi du signal toutes les secondes */
	/*g_timeout_add (1000, (GSourceFunc)songChanged, obj);*/
	if (! (channel = quorra_squeezeslave_object_getChannel((QuorraSqueezeSlaveObject *)obj)))
	{
		g_error ("Error getting channel");
		return NULL;
	}
	g_io_add_watch(channel, G_IO_IN | G_IO_ERR | G_IO_HUP, quorra_squeezeslave_object_listen_callback, obj);

	if (! quorra_squeezeslave_listen((QuorraSqueezeSlaveObject *)obj, &success, &error))
	{
		g_error("Error listen");
	}

	/* Si tout s’est bien déroulé, on attend les connections */
	g_main_loop_run(loop);

	return NULL;
}

int main ()
{
	gpointer data = NULL;

	quorra_plugin_run(data);

	return 0;
}

