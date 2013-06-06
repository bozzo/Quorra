/*
 * QuorraXbmcPlugin.c
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

#include "QuorraXbmcPlugin.h"

static guint sigPlayerOnPlay;
static guint sigPlayerOnPause;
static guint sigPlayerOnStop;
static guint sigPlayerOnSeek;
static guint sigPlaylistOnClear;
static guint sigPlaylistOnAdd;
static guint sigSystemOnQuit;
static guint sigVideoLibraryOnUpdate;
static guint sigGUIOnScreensaverDeactivated;
static guint sigGUIOnScreensaverActivated;


G_DEFINE_TYPE(QuorraXbmcObject, quorra_xbmc_object, G_TYPE_OBJECT)

static void quorra_xbmc_object_class_init (QuorraXbmcObjectClass * quorra_xbmc_class)
{
	g_type_class_add_private (quorra_xbmc_class, sizeof (QuorraXbmcObjectPrivate));

	/*sigPlayerOnPlay = g_signal_new("PlayerOnPlay",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigPlayerOnPause = g_signal_new("PlayerOnPause",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigPlayerOnStop = g_signal_new("PlayerOnStop",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigPlayerOnSeek = g_signal_new("PlayerOnSeek",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigPlaylistOnClear = g_signal_new("PlaylistOnClear",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigPlaylistOnAdd = g_signal_new("PlaylistOnAdd",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigSystemOnQuit = g_signal_new("SystemOnQuit",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigVideoLibraryOnUpdate = g_signal_new("VideoLibraryOnUpdate",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigGUIOnScreensaverDeactivated = g_signal_new("GUIOnScreensaverDeactivated",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
        sigGUIOnScreensaverActivated = g_signal_new("GUIOnScreensaverActivated",G_OBJECT_CLASS_TYPE(quorra_xbmc_class),G_SIGNAL_RUN_LAST,
                        0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);*/

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

	if (! (xbmc_connect(quorra_xbmc,"r4.bozzo.org",9090,NULL,error)))
	{
		g_warning("quorra_xbmc_object_init : connect failed!");
	}
	else
	{
		if (! (fd = g_socket_get_fd(quorra_xbmc->priv->socket)))
		{
			g_warning("quorra_xbmc_object_init : get FD failed!");
		}
		else
		{
			quorra_xbmc->priv->channel = g_io_channel_unix_new(fd);
		}
	}
}

void die (const char *prefix, GError *error)
{
	g_warning("%s: %s", prefix, error->message);
	g_error_free (error);
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

	obj = g_object_new (QUORRA_XBMCOBJ_TYPE, NULL);

	if (! quorra_xbmc_object_isConnected(obj))
	{
		g_warning ("XBMC not connected, return.");
		return NULL;
	}
	g_print("XBMC connected!");
	/* Note : l’appel à cette fonction va appeler les
	 * fonctions définies plus haut :
	 * - dummy_object_class_init
	 * - dummy_object_init
	 */

	dbus_g_connection_register_g_object(connection, QUORRA_XBMC_PATH, obj);

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
	if (!org_freedesktop_DBus_request_name (driver_proxy, QUORRA_XBMC_SERVICE_NAME,	0, &request_name_ret, &error))
	{
		die ("Failed to get name", error);
	}

	if (request_name_ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
	{
		g_warning ("Got result code %u from requesting name", request_name_ret);
		return NULL;
	}

	g_print ("GLib test service has name ‘%s’\n", QUORRA_XBMC_SERVICE_NAME);
	g_print ("GLib test service entering main loop\n");

	/* Envoi du signal toutes les secondes */
	/*g_timeout_add (1000, (GSourceFunc)songChanged, obj);*/
	if (! (channel = quorra_xbmc_object_getChannel((QuorraXbmcObject *)obj)))
	{
		g_warning ("Error getting channel");
		return NULL;
	}
	g_io_add_watch(channel, G_IO_IN | G_IO_ERR | G_IO_HUP, quorra_xbmc_object_listen_callback, obj);

	/* Si tout s’est bien déroulé, on attend les connections */
	g_main_loop_run(loop);

	return NULL;
}
