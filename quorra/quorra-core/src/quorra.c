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
 * along with Quorra. If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on 18 mars 2013
 * By bozzo
 *
 **/
#include "quorra.h"


GKeyFile * load_config(GError ** error)
{
    GKeyFile * keyfile;

    keyfile = g_key_file_new();
    
    if (! g_key_file_load_from_file(keyfile,config_file,G_KEY_FILE_NONE,error))
    {
	g_error("Error while loading config from file. ");	
	return NULL;
    }
    return keyfile;
}

void quorra_log_handler (const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    g_printerr("--> %s\n",message);
}

int main (int argc, char *argv[])
{
    gchar *filename;
    GKeyFile * keyfile;

    GError * error = NULL;
    GOptionContext *context;

    quorra_plugin  say_hello;
    GModule      *module;

    context = g_option_context_new ("- test tree model performance");
    g_option_context_add_main_entries (context, entries, NULL);
    /*g_option_context_add_group (context, gtk_get_option_group (TRUE));*/
    if (!g_option_context_parse (context, &argc, &argv, &error))
    {
        g_print ("option parsing failed: %s\n", error->message);
        return 1;
    }

    g_log_set_handler (QUORRA_LOG_DOMAIN, G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, quorra_log_handler, NULL);

    keyfile = load_config(&error);
    filename = g_key_file_get_string (keyfile,"core","plugin",NULL);

    module = g_module_open (filename, G_MODULE_BIND_LAZY);
    if (!module)
    {
	g_error ("%s", g_module_error ());
	return 1;
    }

    if (!g_module_symbol (module, QUORRA_PLUGIN_METHOD, (gpointer *)&say_hello))
    {
	g_error ("%s: %s", filename, g_module_error ());
        if (!g_module_close (module))
        {
	    g_warning ("%s: %s", filename, g_module_error ());
	}
	return 1;
    }

    if (say_hello == NULL)
    {
        g_error ("symbol say_hello is NULL");
        if (!g_module_close (module))
        {
	    g_warning ("%s: %s", filename, g_module_error ());
        }
	return 1;
    }

  /* call our function in the module */
  say_hello (NULL);

  if (!g_module_close (module))
  {
    g_warning ("%s: %s", filename, g_module_error ());
  }	

  return 0;
}


