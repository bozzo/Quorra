/*
 * quorra.h
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
 * Created on 22 mars 2013
 * By bozzo
 *
 **/
#ifndef QUORRA_H_
#define QUORRA_H_

#include "listener.h"
#include <gmodule.h>
#include <glib.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>

#define QUORRA_PLUGIN_METHOD "quorra_plugin_run"
#define QUORRA_CONFIG_FILE "/etc/quorra/quorra.conf"
#define QUORRA_LOG_DOMAIN "Quorra"

typedef gpointer (* QuorraPlugin) (gpointer data);

static gchar * config_file = QUORRA_CONFIG_FILE;
static gint log_level = 7;
static gboolean verbose = FALSE;

static GOptionEntry entries[] =
{
  { "config-file", 'c', 0, G_OPTION_ARG_FILENAME, &config_file, "Set the configuration file", NULL },
  { "log-level", 'l', 0, G_OPTION_ARG_INT, &log_level, "Define the log level 0 (Emergency) to 7 (Debug)", NULL },
  { "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Be verbose", NULL },
  { NULL }
};

void quorra_log_handler (const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);

GKeyFile * load_config(GError ** error);

int main (int argc, char *argv[]);

#endif
