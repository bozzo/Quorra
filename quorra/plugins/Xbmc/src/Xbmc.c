/*
 * Xbmc.c
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

#include "Xbmc.h"


gboolean xbmc_connect(QuorraXbmcObject * obj, gchar * host, gint port, GCancellable * cancellable, GError ** error)
{
	GSocketConnectable * connectable;
	GSocketAddressEnumerator *enumerator;
	GSocketAddress  *address;
	gboolean success = FALSE;
	GSocket * socket;

	socket = g_socket_new (G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_STREAM, 0, error);

	connectable = g_network_address_parse (g_strdup_printf ("%s:%d",host,port), XBMC_DEFAULT_PORT, error);
	if (connectable == NULL)
	{
		g_error("Unable to parse network address!");
		return FALSE;
	}

	enumerator = g_socket_connectable_enumerate (connectable);
	while (!(success) &&
			(address = g_socket_address_enumerator_next (enumerator, cancellable, error)))
	{
		if (! g_socket_connect (socket, address, cancellable, error))
		{
			/*g_message ("Connection to failed: %s, trying next\n", (*error)->message);*/
			g_clear_error (error);
		}
		else
		{
			success = TRUE;
		}
		g_object_unref (address);
	}
	g_object_unref (enumerator);

	if (success)
	{
		quorra_xbmc_object_setSocket(obj,socket);
		return TRUE;
	}
	return FALSE;
}

gboolean xbmc_close(QuorraXbmcObject * obj, GError ** error)
{
	return g_socket_close(quorra_xbmc_object_getSocket(obj),error);
}

gchar * xbmc_execute(QuorraXbmcObject * obj, gchar * cmd, GCancellable * cancellable, GError ** error)
{
	gchar buff[1024];
	gssize a;
	gint32 i;
	gchar ** tokens;

	GSocket * socket;

	socket = quorra_xbmc_object_getSocket(obj);

	if (socket == NULL)
	{
	    g_error("xbmc_execute : socket is NULL!");
	    return NULL;
	}

	a = g_socket_send(socket,cmd,strlen(cmd)*sizeof(gchar),cancellable,error);
	if (a < 0)
	{
	    g_error("xbmc_execute : error on send command!");
            return NULL;
	}

	a = g_socket_receive(socket,buff,1024,cancellable,error);
        if (a < 0)
        {
            g_error("xbmc_execute : error on receive command result!");
            return NULL;
        }

	tokens = g_strsplit(buff," ",0);
	for (i = 0; tokens[i] != NULL; i++)
	{
		g_print("data : %s\n",g_uri_unescape_string(tokens[i],""));
	}
	g_strfreev(tokens);
	return NULL;
}
