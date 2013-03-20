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
 * along with com_mapfactory. If not, see <http://www.gnu.org/licenses/>.
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
	/*signalId = g_signal_new("songChanged",
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

static void quorra_squeezeslave_object_init (QuorraSqueezeSlaveObject * quorra_squeezeslave)
{
	GError ** error = NULL;

	dbus_g_object_type_install_info (QUORRA_SQUEEZESLAVEOBJ_TYPE,	&dbus_glib_quorra_squeezeslave_object_object_info);
	if (! squeezeserver_connect(quorra_squeezeslave,"millenium.bozzo.org",9090,NULL,error))
	{
		g_print("quorra_squeezeslave_object_init : connect failed!");
	}
}

/*gboolean song_changed(GObject *obj)
{
	g_print("Sent hearbeat !\n");
	g_signal_emit(obj, signalId, 0, 1);
	return TRUE;
}*/

gboolean quorra_squeezeslave_stop(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 time, gboolean * success, GError **error)
{
	if (! squeezeserver_close(obj,error))
	{
		g_print("quorra_squeezeslave_stop : close failed!");

		*success = FALSE;
		return FALSE;
	}

	g_print ("quorra_squeezeslave_stop -> %s - %d sec\n",name,time);
	*success = TRUE;
	return TRUE;
}

gboolean quorra_squeezeslave_nextsong(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 hops, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,"nextsong",NULL,error))
	{
		g_print("quorra_squeezeslave_nextsong : execute failed!");

		*success = FALSE;
		return FALSE;
	}

	g_print ("quorra_squeezeslave_nextsong -> %s %d hops\n",name,hops);
	*success = TRUE;
	return TRUE;
}

gboolean quorra_squeezeslave_pause(QuorraSqueezeSlaveObject * obj, gchar * name, gboolean * success, GError **error)
{
	if (squeezeserver_execute(obj,g_strconcat(name,"pause\n",NULL),NULL,error))
	{
		g_print("quorra_squeezeslave_pause : execute failed!");

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

	g_type_init();

	loop = g_main_loop_new(NULL, FALSE);

	connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);

	if (connection == NULL)
	{
		die ("Failed to open connection to bus", error);
	}

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
		exit (1);
	}

	g_print ("GLib test service has name ‘%s’\n", QUORRA_SQUEEZESLAVE_SERVICE_NAME);
	g_print ("GLib test service entering main loop\n");

	/* Envoi du signal toutes les secondes */
	//g_timeout_add (1000, (GSourceFunc)song_changed, obj);

	/* Si tout s’est bien déroulé, on attend les connections */
	g_main_loop_run (loop);
	return NULL;
}

int main ()
{
	gpointer data = NULL;

	quorra_plugin_run(data);

	return 0;
}

