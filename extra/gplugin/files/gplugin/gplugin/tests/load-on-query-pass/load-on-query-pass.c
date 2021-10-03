/*
 * Copyright (C) 2011-2021 Gary Kramlich <grim@reaperworld.com>
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

#include <gplugin.h>
#include <gplugin-native.h>

static GPluginPluginInfo *
loq_pass_query(G_GNUC_UNUSED GError **error)
{
	/* clang-format off */
	return gplugin_plugin_info_new(
		"gplugin/load-on-query",
		GPLUGIN_NATIVE_PLUGIN_ABI_VERSION,
		"load-on-query", TRUE,
		NULL);
	/* clang-format on */
}

static gboolean
loq_pass_load(G_GNUC_UNUSED GPluginPlugin *plugin, G_GNUC_UNUSED GError **error)
{
	return TRUE;
}

static gboolean
loq_pass_unload(
	G_GNUC_UNUSED GPluginPlugin *plugin,
	G_GNUC_UNUSED GError **error)
{
	return TRUE;
}

GPLUGIN_NATIVE_PLUGIN_DECLARE(loq_pass)
