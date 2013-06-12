/*
 * listener.c
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
 * Created on 10 juin 2013
 * By bozzo
 *
 **/

#include "listener.h"

/* Pareil que pour le serveur */
static void die (const char *prefix, GError *error)
{
	g_warning("%s: %s", prefix, error->message);
	g_error_free (error);
}

static GMainLoop *loop = NULL;

gpointer quorra_listen(gpointer data)
{
	GError *error = NULL;
	DBusGConnection *connection;
	DBusGProxy *proxy;
	gboolean out = FALSE;
	int ret_signal;
	gpointer * dataptr;
	gchar * signalName,* quorraPath,* quorraServiceName,* quorraInterfaceName;

	g_type_init ();

	loop = g_main_loop_new (NULL, FALSE);

	/* Récupération d’une connection sur le bus session,
	 * sur lequel on sait que le service tourne
	 */
	/*connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	if (connection == NULL)
		die ("Failed to open connection to bus", error);
	 */
	dataptr = (gpointer *)data;
	connection = (DBusGConnection *)(dataptr[0]);
	/* FIXME get signal name from dataptr */
	signalName = "playlistSongChanged";
	quorraPath =  "/org/bozzo/Quorra/plg/QuorraSqueezeSlaveObject";
	quorraServiceName =  "org.bozzo.Quorra.plg.QuorraSqueezeSlaveObject";
	quorraInterfaceName =  "org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface";


	g_print("listen : connected to dbus.\n");

	/* Création d’un objet proxy pour interroger un objet distant */
	proxy = dbus_g_proxy_new_for_name (connection, quorraServiceName, quorraPath, quorraInterfaceName);

	/* Si le proxy est nul, on arrête tout */
	if (proxy == NULL)
		die ("Failed to create proxy for name owner", error);

	g_print("listen : get proxy.\n");

	/* Fonction qui appelle la méthode "HelloWorld" de façon synchrone.
	 * - Ensuite vient la liste de tous les arguments d’entrée
	 * selon ce schéma : (TYPE, valeur).
	 * Cette liste se termine par la constante : G_TYPE_INVALID
	 * - Ensuite la liste des arguments de sortie qui se termine par
	 * une seconde constante : G_TYPE_INVALID
	 */
	/*if (!dbus_g_proxy_call (proxy, "Pause", &error,
			G_TYPE_STRING, "squeezeslave", G_TYPE_INVALID,
			 G_TYPE_INVALID))
		die ("Call to dbus_g_proxy_call HelloWorld failed", error);
	 */
	g_print("listen : method called.\n");

	//attach to a signal
	dbus_g_proxy_add_signal(proxy,
			/* Nom du signal */
			signalName,
			/* Un argument de type entier */
			G_TYPE_INT,
			/* Fin de la liste des arguments */
			G_TYPE_INVALID);

	dbus_g_proxy_connect_signal(proxy,
			/* Nom du signal */
			signalName,
			/* Nom de la fonction de rappel
			 * à la réception
			 * d’un signal
			 */
			G_CALLBACK(pingReceptionHandler),
			NULL,
			NULL);

	g_main_loop_run(loop);
	return NULL;
}

/* fonction de rappel */
static void pingReceptionHandler(DBusGProxy* proxy, int ret)
{
	g_printf("signal <-- playlistSongChanged\n", ret);
}
