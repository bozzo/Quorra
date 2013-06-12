/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_quorra_squeezeslave_object_MARSHAL_H__
#define __dbus_glib_marshal_quorra_squeezeslave_object_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_schar (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#define g_marshal_value_peek_variant(v)  g_value_get_variant (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_variant(v)  (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:STRING,POINTER */
extern void dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                                                  GValue       *return_value,
                                                                                  guint         n_param_values,
                                                                                  const GValue *param_values,
                                                                                  gpointer      invocation_hint,
                                                                                  gpointer      marshal_data);
void
dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                                      GValue       *return_value G_GNUC_UNUSED,
                                                                      guint         n_param_values,
                                                                      const GValue *param_values,
                                                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                                                      gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_POINTER) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,INT,POINTER,POINTER */
extern void dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_INT_POINTER_POINTER (GClosure     *closure,
                                                                                              GValue       *return_value,
                                                                                              guint         n_param_values,
                                                                                              const GValue *param_values,
                                                                                              gpointer      invocation_hint,
                                                                                              gpointer      marshal_data);
void
dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_INT_POINTER_POINTER (GClosure     *closure,
                                                                                  GValue       *return_value G_GNUC_UNUSED,
                                                                                  guint         n_param_values,
                                                                                  const GValue *param_values,
                                                                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                  gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_INT_POINTER_POINTER) (gpointer     data1,
                                                                        gpointer     arg_1,
                                                                        gint         arg_2,
                                                                        gpointer     arg_3,
                                                                        gpointer     arg_4,
                                                                        gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_INT_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_INT_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_int (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       g_marshal_value_peek_pointer (param_values + 4),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

G_END_DECLS

#endif /* __dbus_glib_marshal_quorra_squeezeslave_object_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_quorra_squeezeslave_object_methods[] = {
  { (GCallback) quorra_squeezeslave_pause, dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_POINTER, 0 },
  { (GCallback) quorra_squeezeslave_nextsong, dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_INT_POINTER_POINTER, 67 },
  { (GCallback) quorra_squeezeslave_stop, dbus_glib_marshal_quorra_squeezeslave_object_BOOLEAN__STRING_INT_POINTER_POINTER, 162 },
};

const DBusGObjectInfo dbus_glib_quorra_squeezeslave_object_object_info = {  1,
  dbus_glib_quorra_squeezeslave_object_methods,
  3,
"org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0Pause\0S\0name\0I\0s\0\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0NextSong\0S\0name\0I\0s\0hops\0I\0i\0success\0O\0F\0N\0b\0\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0Stop\0S\0name\0I\0s\0time\0I\0i\0success\0O\0F\0N\0b\0\0\0",
"org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistSongChanged\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistSongAdded\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistSongDeleted\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistSongOpen\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistSongJump\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistStop\0org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface\0playlistPause\0\0",
"\0"
};

