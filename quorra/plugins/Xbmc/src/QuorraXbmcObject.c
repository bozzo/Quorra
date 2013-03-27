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


