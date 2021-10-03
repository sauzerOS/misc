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

#include <gplugin/gplugin-plugin.h>

#include <gplugin/gplugin-core.h>
#include <gplugin/gplugin-enums.h>
#include <gplugin/gplugin-private.h>

/**
 * SECTION:gplugin-plugin
 * @Title: Plugin Interface
 * @Short_description: The plugin interface that all plugins must implement.
 *
 * #GPluginPlugin is an interface that defines the behavior of plugins.  It
 * is implemented by each loader which add additional data for their
 * implementation.
 */

/**
 * GPluginPluginState:
 * @GPLUGIN_PLUGIN_STATE_UNKNOWN: The state of the plugin is unknown.
 * @GPLUGIN_PLUGIN_STATE_ERROR: There was an error loading or unloading the
 *  plugin.
 * @GPLUGIN_PLUGIN_STATE_QUERIED: The plugin has been queried but not loaded.
 * @GPLUGIN_PLUGIN_STATE_REQUERY: The plugin should be requeried.
 * @GPLUGIN_PLUGIN_STATE_LOADED: The plugin is loaded.
 * @GPLUGIN_PLUGIN_STATE_LOAD_FAILED: The plugin failed to load.
 * @GPLUGIN_PLUGIN_STATE_UNLOAD_FAILED: The plugin failed to unload.
 *
 * The known states of a plugin.
 */

/**
 * GPLUGIN_TYPE_PLUGIN:
 *
 * The standard _get_type macro for #GPluginPlugin.
 */

/**
 * GPluginPlugin:
 *
 * #GPluginPlugin is an opaque data structure and should not be used directly.
 */

/**
 * GPluginPluginInterface:
 * @state_changed: The class closure for the #GPluginPlugin::state-changed
 *                 signal.
 *
 * The interface that defines the behavior of plugins, including properties and
 * signals.
 */

/******************************************************************************
 * Enums
 *****************************************************************************/
enum {
	SIG_STATE_CHANGED,
	SIG_LAST,
};
static guint signals[SIG_LAST] = {
	0,
};

G_DEFINE_INTERFACE(GPluginPlugin, gplugin_plugin, G_TYPE_INVALID);

/******************************************************************************
 * Object Stuff
 *****************************************************************************/
static void
gplugin_plugin_default_init(GPluginPluginInterface *iface)
{
	GParamSpec *pspec = NULL;

	/**
	 * GPluginPlugin:filename:
	 *
	 * The absolute path to the plugin on disk.
	 */
	pspec = g_param_spec_string(
		"filename",
		"filename",
		"The filename of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
	g_object_interface_install_property(iface, pspec);

	/**
	 * GPluginPlugin:loader:
	 *
	 * The #GPluginLoader that loaded this plugin.
	 */
	pspec = g_param_spec_object(
		"loader",
		"loader",
		"The loader for this plugin",
		GPLUGIN_TYPE_LOADER,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
	g_object_interface_install_property(iface, pspec);

	/**
	 * GPluginPlugin:info:
	 *
	 * The #GPluginPluginInfo from this plugin.
	 */
	pspec = g_param_spec_object(
		"info",
		"info",
		"The information for the plugin",
		GPLUGIN_TYPE_PLUGIN_INFO,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
	g_object_interface_install_property(iface, pspec);

	/**
	 * GPluginPlugin:state:
	 *
	 * The #GPluginPluginState that this plugin is in.
	 */
	pspec = g_param_spec_enum(
		"state",
		"state",
		"The state of the plugin",
		GPLUGIN_TYPE_PLUGIN_STATE,
		GPLUGIN_PLUGIN_STATE_UNKNOWN,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	g_object_interface_install_property(iface, pspec);

	/**
	 * GPluginPlugin:error:
	 *
	 * A #GError returned the plugin if it failed to load or unload.
	 */
	pspec = g_param_spec_boxed(
		"error",
		"error",
		"A GError returned from the load or unload function",
		G_TYPE_ERROR,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	g_object_interface_install_property(iface, pspec);

	/**
	 * GPluginPlugin::state-changed:
	 * @plugin: The #GPluginPlugin that changed states.
	 * @oldstate: The old #GPluginPluginState.
	 * @newstate: The new state of @plugin.
	 *
	 * Emitted when @plugin changes state.
	 */
	signals[SIG_STATE_CHANGED] = g_signal_new(
		"state-changed",
		GPLUGIN_TYPE_PLUGIN,
		G_SIGNAL_RUN_LAST,
		G_STRUCT_OFFSET(GPluginPluginInterface, state_changed),
		NULL,
		NULL,
		NULL,
		G_TYPE_NONE,
		2,
		GPLUGIN_TYPE_PLUGIN_STATE,
		GPLUGIN_TYPE_PLUGIN_STATE);
}

/******************************************************************************
 * GPluginPlugin API
 *****************************************************************************/

/**
 * gplugin_plugin_get_filename:
 * @plugin: The #GPluginPlugin instance.
 *
 * Returns the filename that @plugin was loaded from.
 *
 * Returns: (transfer full): The filename of @plugin.
 */
gchar *
gplugin_plugin_get_filename(GPluginPlugin *plugin)
{
	gchar *filename = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN(plugin), NULL);

	g_object_get(G_OBJECT(plugin), "filename", &filename, NULL);

	return filename;
}

/**
 * gplugin_plugin_get_loader:
 * @plugin: The #GPluginPlugin instance.
 *
 * Returns the #GPluginLoader that loaded @plugin.
 *
 * Returns: (transfer full): The #GPluginLoader that loaded @plugin.
 */
GPluginLoader *
gplugin_plugin_get_loader(GPluginPlugin *plugin)
{
	GPluginLoader *loader = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN(plugin), NULL);

	g_object_get(G_OBJECT(plugin), "loader", &loader, NULL);

	return loader;
}

/**
 * gplugin_plugin_get_info:
 * @plugin: The #GPluginPlugin instance.
 *
 * Returns the #GPluginPluginInfo for @plugin.
 *
 * Returns: (transfer full): The #GPluginPluginInfo instance for @plugin.
 */
GPluginPluginInfo *
gplugin_plugin_get_info(GPluginPlugin *plugin)
{
	GPluginPluginInfo *info = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN(plugin), NULL);

	g_object_get(G_OBJECT(plugin), "info", &info, NULL);

	return info;
}

/**
 * gplugin_plugin_get_state:
 * @plugin: The #GPluginPlugin instance.
 *
 * Gets the current state of @plugin.
 *
 * Returns: (transfer full): The current state of @plugin.
 */
GPluginPluginState
gplugin_plugin_get_state(GPluginPlugin *plugin)
{
	GPluginPluginState state = GPLUGIN_PLUGIN_STATE_UNKNOWN;

	g_return_val_if_fail(
		GPLUGIN_IS_PLUGIN(plugin),
		GPLUGIN_PLUGIN_STATE_UNKNOWN);

	g_object_get(G_OBJECT(plugin), "state", &state, NULL);

	return state;
}

/**
 * gplugin_plugin_set_state:
 * @plugin: The #GPluginPlugin instance.
 * @state: A new #GPluginPluginState for @plugin.
 *
 * Changes the state of @plugin to @state.  This function should only be called
 * by loaders.
 */
void
gplugin_plugin_set_state(GPluginPlugin *plugin, GPluginPluginState state)
{
	GPluginPluginState oldstate = GPLUGIN_PLUGIN_STATE_UNKNOWN;

	g_return_if_fail(GPLUGIN_IS_PLUGIN(plugin));

	oldstate = gplugin_plugin_get_state(plugin);

	g_object_set(G_OBJECT(plugin), "state", state, NULL);

	if(gplugin_get_flags() & GPLUGIN_CORE_FLAGS_LOG_PLUGIN_STATE_CHANGES) {
		GPluginPluginInfo *info = gplugin_plugin_get_info(plugin);

		g_message(
			"plugin %s state changed from %s to %s: filename=%s",
			gplugin_plugin_info_get_id(info),
			gplugin_plugin_state_to_string(oldstate),
			gplugin_plugin_state_to_string(state),
			gplugin_plugin_get_filename(plugin));

		g_clear_object(&info);
	}

	g_signal_emit(plugin, signals[SIG_STATE_CHANGED], 0, oldstate, state);
}

/**
 * gplugin_plugin_get_error:
 * @plugin: The #GPluginPlugin instance.
 *
 * Gets the #GError, if any, that the plugin returned during load or unload.
 *
 * Returns: (transfer full): The #GError the plugin returned during load or
 *          unload, or %NULL if no error occurred.
 */
GError *
gplugin_plugin_get_error(GPluginPlugin *plugin)
{
	GError *error = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN(plugin), NULL);

	g_object_get(G_OBJECT(plugin), "error", &error, NULL);

	return error;
}

/**
 * gplugin_plugin_state_to_string:
 * @state: The #GPluginPluginState.
 *
 * Gets a string representation of @state.
 *
 * Returns: The string representation of @state.
 *
 * Since: 0.32.0
 */
const gchar *
gplugin_plugin_state_to_string(GPluginPluginState state)
{
	const gchar *state_str = NULL;

	switch(state) {
		case GPLUGIN_PLUGIN_STATE_QUERIED:
			state_str = "queried";
			break;
		case GPLUGIN_PLUGIN_STATE_REQUERY:
			state_str = "requery";
			break;
		case GPLUGIN_PLUGIN_STATE_LOADED:
			state_str = "loaded";
			break;
		case GPLUGIN_PLUGIN_STATE_LOAD_FAILED:
			state_str = "load-failed";
			break;
		case GPLUGIN_PLUGIN_STATE_UNLOAD_FAILED:
			state_str = "unload-failed";
			break;
		default:
			state_str = "unknown";
			break;
	}

	return state_str;
}
