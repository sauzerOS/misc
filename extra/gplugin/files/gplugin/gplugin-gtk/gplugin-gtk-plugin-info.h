/*
 * Copyright (C) 2011-2020 Gary Kramlich <grim@reaperworld.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#if !defined(GPLUGIN_GTK_GLOBAL_HEADER_INSIDE) && \
	!defined(GPLUGIN_GTK_COMPILATION)
#error "only <gplugin/gplugin-gtk.h> may be included directly"
#endif

#ifndef GPLUGIN_GTK_PLUGIN_INFO_H
#define GPLUGIN_GTK_PLUGIN_INFO_H

#include <glib.h>
#include <glib-object.h>

#include <gtk/gtk.h>

#include <gplugin.h>

G_BEGIN_DECLS

#define GPLUGIN_GTK_TYPE_PLUGIN_INFO (gplugin_gtk_plugin_info_get_type())
G_DECLARE_FINAL_TYPE(
	GPluginGtkPluginInfo,
	gplugin_gtk_plugin_info,
	GPLUGIN_GTK,
	PLUGIN_INFO,
	GtkBox)

GtkWidget *gplugin_gtk_plugin_info_new(void);

void gplugin_gtk_plugin_info_set_plugin(
	GPluginGtkPluginInfo *info,
	GPluginPlugin *plugin);
GPluginPlugin *gplugin_gtk_plugin_info_get_plugin(GPluginGtkPluginInfo *info);

G_END_DECLS

#endif /* GPLUGIN_GTK_PLUGIN_INFO_H */
