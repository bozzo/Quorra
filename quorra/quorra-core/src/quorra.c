/*
 * quorra.c
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
 * Created on 18 mars 2013
 * By bozzo
 *
 **/
#include <gmodule.h>
#include <glib.h>

#define QUORRA_PLUGIN_METHOD "quorra_plugin_run"
#define QUORRA_CONFIG_FILE "/etc/quorra/quorra.conf"

typedef gpointer (* quorra_plugin) (gpointer data);

GKeyFile * load_config(GError ** error)
{
    GKeyFile * keyfile;

    keyfile = g_key_file_new();
    
    if (! g_key_file_load_from_file(keyfile,QUORRA_CONFIG_FILE,G_KEY_FILE_NONE,error))
    {
	g_error("Error while loading config from file. ");	
	return NULL;
    }
    return keyfile;
}

int main (int argc, char *argv[])
{
    gchar *filename;/* = "/home/bozzo/git/Quorra/quorra/plugins/SqueezeSlave/src/plg_squeezeslave-1.0.la";*/
    GError **error;
    GKeyFile * keyfile;

    keyfile = load_config(error);
    filename = g_key_file_get_string (keyfile,"core","plugin",NULL);

    quorra_plugin  say_hello;
    GModule      *module;

    module = g_module_open (filename, G_MODULE_BIND_LAZY);
    if (!module)
    {
	g_error ("%s", g_module_error ());
	return FALSE;
    }

    if (!g_module_symbol (module, QUORRA_PLUGIN_METHOD, (gpointer *)&say_hello))
    {
	g_error ("%s: %s", filename, g_module_error ());
        if (!g_module_close (module))
        {
	    g_warning ("%s: %s", filename, g_module_error ());
	}
	return FALSE;
    }

    if (say_hello == NULL)
    {
        g_error ("symbol say_hello is NULL");
        if (!g_module_close (module))
        {
	    g_warning ("%s: %s", filename, g_module_error ());
        }
	return FALSE;
    }

  /* call our function in the module */
  say_hello (NULL);

  if (!g_module_close (module))
  {
    g_warning ("%s: %s", filename, g_module_error ());
  }	

  return 0;
}


