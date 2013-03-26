/*
 * Xbmc.h
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

#ifndef XBMC_H_
#define XBMC_H_


#define XBMC_DEFAULT_PORT 9090

gboolean xbmc_connect(QuorraSqueezeSlaveObject * obj, gchar * host, gint port, GCancellable * cancellable, GError ** error);

gboolean xbmc_close(QuorraSqueezeSlaveObject * obj, GError ** error);

gchar * xbmc_execute(QuorraSqueezeSlaveObject * obj, gchar * cmd, GCancellable * cancellable, GError ** error);



#endif /* XBMC_H_ */
