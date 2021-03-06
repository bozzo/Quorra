/*
 * QuorraSqueezeSlaveObject.h
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

#ifndef QUORRA_SQUEEZESLAVE_OBJECT_H_
#define QUORRA_SQUEEZESLAVE_OBJECT_H_

#include <glib-object.h>

typedef struct _QuorraSqueezeSlaveObject QuorraSqueezeSlaveObject;
typedef struct _QuorraSqueezeSlaveObjectClass QuorraSqueezeSlaveObjectClass;
typedef struct _QuorraSqueezeSlaveObjectPrivate QuorraSqueezeSlaveObjectPrivate;

#define QUORRA_SQUEEZESLAVEOBJ_TYPE 				(quorra_squeezeslave_object_get_type ())
#define QUORRA_SQUEEZESLAVEOBJ_CLASS(klass) 		(G_TYPE_CHECK_CLASS_CAST ((klass), QUORRA_SQUEEZESLAVEOBJ_TYPE, QuorraSqueezeSlaveObjectClass))
#define QUORRA_SQUEEZESLAVEOBJ_GET_PRIVATE(obj) 	(G_TYPE_INSTANCE_GET_PRIVATE ((obj), QUORRA_SQUEEZESLAVEOBJ_TYPE, QuorraSqueezeSlaveObjectPrivate))

#define QUORRA_SQUEEZESLAVEOBJ(obj)					(G_TYPE_CHECK_INSTANCE_CAST ((obj), QUORRA_SQUEEZESLAVEOBJ_TYPE, QuorraSqueezeSlaveObject))
#define IS_QUORRA_SQUEEZESLAVEOBJ(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), QUORRA_SQUEEZESLAVEOBJ_TYPE))
#define IS_QUORRA_SQUEEZESLAVEOBJ_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), QUORRA_SQUEEZESLAVEOBJ_TYPE))
#define QUORRA_SQUEEZESLAVEOBJ_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), QUORRA_SQUEEZESLAVEOBJ_TYPE, QuorraSqueezeSlaveObjectClass))

GType quorra_squeezeslave_object_get_type (void);

GType quorra_squeezeslave_pause_get_type (void);
GType quorra_squeezeslave_stop_get_type (void);
GType quorra_squeezeslave_nextsong_get_type (void);


struct _QuorraSqueezeSlaveObjectPrivate
{
	GSocket * socket;
	GIOChannel * channel;
};

struct _QuorraSqueezeSlaveObject
{
	GObject parent;

	/*< private >*/
	QuorraSqueezeSlaveObjectPrivate * priv;
};

struct _QuorraSqueezeSlaveObjectClass
{
	GObjectClass parent;
};

/*
 * Methods definition
 */
GIOChannel * quorra_squeezeslave_object_getChannel(QuorraSqueezeSlaveObject * obj);
gboolean quorra_squeezeslave_object_isConnected(QuorraSqueezeSlaveObject * obj);
GSocket * quorra_squeezeslave_object_getSocket(QuorraSqueezeSlaveObject * obj);
void quorra_squeezeslave_object_setSocket(QuorraSqueezeSlaveObject * obj, GSocket * socket);

gboolean quorra_squeezeslave_action_playlist(QuorraSqueezeSlaveObject * obj, gchar ** cmd);
gboolean quorra_squeezeslave_action_other(QuorraSqueezeSlaveObject * obj, gchar ** cmd);

/*
 * Listen to socket
 */
gboolean quorra_squeezeslave_object_listen_callback (GIOChannel * source, GIOCondition condition, gpointer data);
gboolean quorra_squeezeslave_listen(QuorraSqueezeSlaveObject * obj, gboolean * success, GError **error);

/*
 * DBus callback
 */
gboolean quorra_squeezeslave_pause(QuorraSqueezeSlaveObject * obj, gchar * name, GError **error);
gboolean quorra_squeezeslave_nextsong(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 hops, gboolean * success, GError **error);
gboolean quorra_squeezeslave_stop(QuorraSqueezeSlaveObject * obj, gchar * name, gint32 time, gboolean * success, GError **error);

gboolean playlistSongChanged(GObject *obj,gint id, gchar * name);
gboolean playlistSongAdded(GObject *obj,gint id, gchar * name);
gboolean playlistSongDeleted(GObject *obj,gint id, gchar * name);
gboolean playlistSongOpen(GObject *obj,gint id, gchar * name);
gboolean playlistSongJump(GObject *obj,gint id, gchar * name);
gboolean playlistStop(GObject *obj,gint id, gchar * name);
gboolean playlistPause(GObject *obj,gint id, gchar * name);

#endif /* QUORRA_SQUEEZESLAVE_OBJECT_H_ */
