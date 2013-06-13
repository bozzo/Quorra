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

void die (const char *prefix, GError *error)
{
	g_error("%s: %s", prefix, error->message);
	g_error_free (error);
	exit(1);
}

int main (int argc, char *argv[])
{
	/*gchar *filename;*/
	gchar ** plugins;
	gsize nbPlugins;
	gint cpt;
	GKeyFile * keyfile;

	GError * error = NULL;
	GOptionContext *context;

	QuorraPlugin ** quorra_plugins;
	GThread ** threads;
	GModule ** modules;

	DBusGConnection * connection;
	/*DBusGProxy * driver_proxy;*/
	gpointer data[2];

	QuorraMappingObject * quorraMapping;

	g_type_init();

	context = g_option_context_new ("- test tree model performance");
	g_option_context_add_main_entries (context, entries, NULL);
	/*g_option_context_add_group (context, gtk_get_option_group (TRUE));*/
	if (!g_option_context_parse (context, &argc, &argv, &error))
	{
		g_print ("option parsing failed: %s\n", error->message);
		return 1;
	}

	g_log_set_handler (QUORRA_LOG_DOMAIN, G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, quorra_log_handler, NULL);

	connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);

	if (connection == NULL)
	{
		die ("Failed to open connection to bus", error);
	}

	quorraMapping = (QuorraMappingObject *)g_object_new (QUORRA_MAPPINGOBJ_TYPE, NULL);

	quorra_mapping_object_setConnection(quorraMapping,connection);
	quorra_mapping_object_setSignalName(quorraMapping,"playlistSongChanged");
	quorra_mapping_object_setQuorraPath(quorraMapping,"/org/bozzo/Quorra/plg/QuorraSqueezeSlaveObject");
	quorra_mapping_object_setQuorraServiceName(quorraMapping,"org.bozzo.Quorra.plg.QuorraSqueezeSlaveObject");
	quorra_mapping_object_setQuorraInterfaceName(quorraMapping,"org.bozzo.quorra.plg.QuorraSqueezeSlaveInterface");
	quorra_mapping_object_insertData(quorraMapping, "name","Squeezeslave");

	data[0]=connection;
	data[1]="Squeezeslave";/*driver_proxy;*/

	keyfile = load_config(&error);
	/*filename = g_key_file_get_string (keyfile,"core","plugin",NULL);*/
	plugins = g_key_file_get_string_list(keyfile,"core","plugin",&nbPlugins,NULL);

	quorra_plugins = (QuorraPlugin **) g_malloc (nbPlugins * sizeof(QuorraPlugin *));
	threads = (GThread **) g_malloc (nbPlugins * sizeof(GThread *));
	modules = (GModule **) g_malloc (nbPlugins * sizeof(GModule *));

	for(cpt = 0; cpt < nbPlugins; cpt++)
	{
		modules[cpt] = g_module_open (plugins[cpt], G_MODULE_BIND_LAZY);
		if (!modules[cpt])
		{
			g_error ("g_module_open: %s", g_module_error ());
			return 1;
		}

		if (!g_module_symbol (modules[cpt], QUORRA_PLUGIN_METHOD, (gpointer *)&(quorra_plugins[cpt]) ))
		{
			g_error ("g_module_symbol %s: %s", plugins[cpt], g_module_error ());
			if (!g_module_close (modules[cpt]))
			{
				g_warning ("g_module_close %s: %s", plugins[cpt], g_module_error ());
			}
			return 1;
		}

		if (quorra_plugins[cpt] == NULL)
		{
			g_error ("symbol say_hello is NULL");
			if (!g_module_close (modules[cpt]))
			{
				g_warning ("g_module_close %s: %s", plugins[cpt], g_module_error ());
			}
			return 1;
		}

		/* call our function in the module */
		threads[cpt] = g_thread_new( g_strdup_printf("thread-%d",cpt),*((GThreadFunc *)&(quorra_plugins[cpt])),data);
	}

	g_usleep(3 * G_USEC_PER_SEC);

	/* start the listener thread */
	threads[++cpt] = g_thread_new("thread-listen",quorra_listen,(gpointer) quorraMapping);

	for(cpt = 0; cpt < nbPlugins + 1; cpt++)
	{
		g_thread_join(threads[cpt]);

		if (!g_module_close (modules[cpt]))
		{
			g_warning ("g_module_close %s: %s", plugins[cpt], g_module_error ());
		}
	}

	return 0;
}


