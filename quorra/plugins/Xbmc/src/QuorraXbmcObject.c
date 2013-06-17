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

gboolean quorra_xbmc_object_isConnected(QuorraXbmcObject * obj)
{
	QuorraXbmcObjectPrivate * priv;

	priv = QUORRA_XBMCOBJ_GET_PRIVATE (obj);

	if (priv != NULL && priv->socket != NULL)
	{
		return TRUE;
	}
	return FALSE;
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

gboolean quorra_xbmc_action_playlist(QuorraXbmcObject * obj, gchar * cmd)
{
	if (cmd == NULL)
	{
		g_warning("quorra_xbmc_action_playlist : cmd is NULL!");
		return FALSE;
	}
	/*songChanged((GObject *)obj,1,"test");*/
	g_print("%s\n",cmd);

	return TRUE;
}


gboolean quorra_xbmc_object_listen_callback (GIOChannel * source, GIOCondition condition, gpointer data)
{
	gsize bytes_read;
	gchar buff[1024];
	gint i;
	gchar ** tokens;
	gchar * tmp, * tmp2, * input;
	QuorraXbmcObject * obj;
	JsonParser * parser;
	JsonReader * reader;

	if (source == NULL)
	{
		g_warning("quorra_xbmc_object_listen_callback : source is NULL!");
		return FALSE;
	}

	if (data == NULL)
	{
		g_warning("quorra_xbmc_object_listen_callback : data is NULL!");
		return FALSE;
	}

	obj = (QuorraXbmcObject *)data;

	parser = json_parser_new ();

	tmp = NULL;
	input = NULL;

	g_io_channel_read_chars (source, buff, 1024, &bytes_read, NULL);

	if (bytes_read)
	{
		input = g_strndup(buff,bytes_read);
	}

	while (bytes_read)
	{
		g_io_channel_read_chars (source, buff, 1024, &bytes_read, NULL);
		if (bytes_read)
		{
			tmp2 = g_strndup(buff,bytes_read);

			tmp = g_strconcat(input,tmp2,NULL);
			g_free(input);
			g_free(tmp2);

			input = g_strdup(tmp);
			g_free(tmp);
		}
	}

	if (! json_parser_load_from_data (parser, input, -1, NULL))
	{
		g_warning("Unable to parse input!\n");
	}

	reader = json_reader_new (json_parser_get_root (parser));
	if (! reader)
	{
		g_warning("Unable create reader!\n");
	}

	json_reader_read_member (reader, "method");

	quorra_xbmc_action_playlist(obj,json_reader_get_string_value (reader));

	json_reader_end_member (reader);

	g_object_unref (reader);
	g_object_unref (parser);

	g_free(input);

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

/*
 * DBus Signals
 */
gboolean PlayerOnPlay(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean PlayerOnPause(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean PlayerOnStop(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean PlayerOnSeek(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean PlaylistOnClear(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean PlaylistOnAdd(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean SystemOnQuit(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean VideoLibraryOnUpdate(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean GUIOnScreensaverDeactivated(GObject *obj, gchar * sender)
{

	return TRUE;
}

gboolean GUIOnScreensaverActivated(GObject *obj, gchar * sender)
{

	return TRUE;
}


