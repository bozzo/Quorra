/*
 * QuorraXbmcObject.h
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

#ifndef QUORRAXBMCOBJECT_H_
#define QUORRAXBMCOBJECT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>
#include <netdb.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

typedef struct _QuorraXbmcObject QuorraXbmcObject;
typedef struct _QuorraXbmcObjectClass QuorraXbmcObjectClass;
typedef struct _QuorraXbmcObjectPrivate QuorraXbmcObjectPrivate;

#define QUORRA_XBMCOBJ_TYPE 				(quorra_xbmc_object_get_type ())
#define QUORRA_XBMCOBJ_CLASS(klass) 		(G_TYPE_CHECK_CLASS_CAST ((klass), QUORRA_XBMCOBJ_TYPE, QuorraXbmcObject))
#define QUORRA_XBMCOBJ_GET_PRIVATE(obj) 	(G_TYPE_INSTANCE_GET_PRIVATE ((obj), QUORRA_XBMCOBJ_TYPE, QuorraXbmcObjectPrivate))

#define QUORRA_XBMCOBJ(obj)					(G_TYPE_CHECK_INSTANCE_CAST ((obj), QUORRA_XBMCOBJ_TYPE, QuorraXbmcObject))
#define IS_QUORRA_XBMCOBJ(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), QUORRA_XBMCOBJ_TYPE))
#define IS_QUORRA_XBMCOBJ_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), QUORRA_XBMCOBJ_TYPE))
#define QUORRA_XBMCOBJ_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), QUORRA_XBMCOBJ_TYPE, QuorraXbmcObjectClass))

GType quorra_xbmc_object_get_type (void);

GType quorra_xbmc_playpause_get_type (void);
GType quorra_xbmc_stop_get_type (void);


struct _QuorraXbmcObjectPrivate
{
	GSocket * socket;
	GIOChannel * channel;
	/* Signals */
	guint sigPlayerOnPlay;
	guint sigPlayerOnPause;
	guint sigPlayerOnStop;
        guint sigPlayerOnSeek;
        guint sigPlaylistOnClear;
        guint sigPlaylistOnAdd;
        guint sigSystemOnQuit;
        guint sigVideoLibraryOnUpdate;
        guint sigGUIOnScreensaverDeactivated;
        guint sigGUIOnScreensaverActivated;
};

struct _QuorraXbmcObject
{
	GObject parent;

	/*< private >*/
	QuorraXbmcObjectPrivate * priv;
};

struct _QuorraXbmcObjectClass
{
	GObjectClass parent;
};

/*
 * Methods definition
 */
GIOChannel * quorra_xbmc_object_getChannel(QuorraXbmcObject * obj);
gboolean quorra_xbmc_object_isConnected(QuorraXbmcObject * obj);
GSocket * quorra_xbmc_object_getSocket(QuorraXbmcObject * obj);
void quorra_xbmc_object_setSocket(QuorraXbmcObject * obj, GSocket * socket);
gboolean quorra_xbmc_action_playlist(QuorraXbmcObject * obj, gchar * cmd);

/*
 * Listen to socket
 */
gboolean quorra_xbmc_object_listen_callback (GIOChannel * source, GIOCondition condition, gpointer data);

/*
 * DBus callback
 */
gboolean quorra_xbmc_playpause(QuorraXbmcObject * obj, gint playerid, gboolean * success, GError **error);
gboolean quorra_xbmc_stop(QuorraXbmcObject * obj, gint playerid, gboolean * success, GError **error);

/*
 * DBus Signals
 */
gboolean PlayerOnPlay(GObject *obj, gchar * sender);
gboolean PlayerOnPause(GObject *obj, gchar * sender);
gboolean PlayerOnStop(GObject *obj, gchar * sender);
gboolean PlayerOnSeek(GObject *obj, gchar * sender);
gboolean PlaylistOnClear(GObject *obj, gchar * sender);
gboolean PlaylistOnAdd(GObject *obj, gchar * sender);
gboolean SystemOnQuit(GObject *obj, gchar * sender);
gboolean VideoLibraryOnUpdate(GObject *obj, gchar * sender);
gboolean GUIOnScreensaverDeactivated(GObject *obj, gchar * sender);
gboolean GUIOnScreensaverActivated(GObject *obj, gchar * sender);


#endif /* QUORRAXBMCOBJECT_H_ */
