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

#include <gplugin/gplugin-core.h>
#include <gplugin/gplugin-enums.h>
#include <gplugin/gplugin-plugin-info.h>
#include <gplugin/gplugin-private.h>

/**
 * SECTION:gplugin-plugin-info
 * @Title: Plugin Info Objects
 * @Short_description: information about plugins.
 *
 * #GPluginPluginInfo holds metadata for plugins.
 */

/**
 * GPLUGIN_TYPE_PLUGIN_INFO:
 *
 * The standard _get_type macro for #GPluginPluginInfo.
 */

/**
 * GPluginPluginInfo:
 *
 * #GPluginPluginInfo holds all of the data about a plugin.  It is created when
 * a plugin is queried.
 */

/**
 * GPluginPluginInfoClass:
 *
 * The class structure for #GPluginPluginInfo.
 */

/******************************************************************************
 * Structs
 *****************************************************************************/
typedef struct {
	gchar *id;

	gchar **provides;
	gint priority;

	gchar *name;

	gchar *version;

	gchar *license_id;
	gchar *license_text;
	gchar *license_url;

	gchar *icon_name;

	gchar *summary;
	gchar *description;
	gchar *category;
	gchar **authors;
	gchar *website;

	gchar **dependencies;

	guint32 abi_version;
	gboolean internal;
	gboolean load_on_query;

	gboolean bind_global;
} GPluginPluginInfoPrivate;

/******************************************************************************
 * Enums
 *****************************************************************************/
enum {
	PROP_ZERO = 0,
	PROP_ID,
	PROP_PROVIDES,
	PROP_PRIORITY,
	PROP_ABI_VERSION,
	PROP_INTERNAL,
	PROP_LOQ,
	PROP_BIND_GLOBAL,
	PROP_NAME,
	PROP_VERSION,
	PROP_LICENSE_ID,
	PROP_LICENSE_TEXT,
	PROP_LICENSE_URL,
	PROP_ICON_NAME,
	PROP_SUMMARY,
	PROP_DESCRIPTION,
	PROP_CATEGORY,
	PROP_AUTHORS,
	PROP_WEBSITE,
	PROP_DEPENDENCIES,
	N_PROPERTIES,
};
static GParamSpec *properties[N_PROPERTIES] = {
	NULL,
};

G_DEFINE_TYPE_WITH_PRIVATE(
	GPluginPluginInfo,
	gplugin_plugin_info,
	G_TYPE_OBJECT)

/******************************************************************************
 * Private API
 *****************************************************************************/
static void
gplugin_plugin_info_set_id(GPluginPluginInfo *info, const gchar *id)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->id);
	priv->id = g_strdup(id);
}

static void
gplugin_plugin_info_set_provides(
	GPluginPluginInfo *info,
	const gchar *const *provides)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_strfreev(priv->provides);

	priv->provides = g_strdupv((gchar **)provides);

	g_object_notify_by_pspec(G_OBJECT(info), properties[PROP_PROVIDES]);
}

static void
gplugin_plugin_info_set_priority(GPluginPluginInfo *info, gint priority)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	if(priority != priv->priority) {
		priv->priority = priority;

		g_object_notify_by_pspec(G_OBJECT(info), properties[PROP_PRIORITY]);
	}
}

static void
gplugin_plugin_info_set_abi_version(
	GPluginPluginInfo *info,
	guint32 abi_version)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	priv->abi_version = abi_version;
}

static void
gplugin_plugin_info_set_internal(GPluginPluginInfo *info, gboolean internal)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	priv->internal = internal;
}

static void
gplugin_plugin_info_set_load_on_query(GPluginPluginInfo *info, gboolean loq)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	priv->load_on_query = loq;
}

static void
gplugin_plugin_info_set_bind_global(
	GPluginPluginInfo *info,
	gboolean bind_global)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	priv->bind_global = bind_global;
}

static void
gplugin_plugin_info_set_name(GPluginPluginInfo *info, const gchar *name)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->name);
	priv->name = g_strdup(name);
}

static void
gplugin_plugin_info_set_version(GPluginPluginInfo *info, const gchar *version)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->version);
	priv->version = g_strdup(version);
}

static void
gplugin_plugin_info_set_license_id(
	GPluginPluginInfo *info,
	const gchar *license_id)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->license_id);
	priv->license_id = g_strdup(license_id);
}

static void
gplugin_plugin_info_set_license_text(
	GPluginPluginInfo *info,
	const gchar *license_text)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->license_text);
	priv->license_text = g_strdup(license_text);
}

static void
gplugin_plugin_info_set_license_url(
	GPluginPluginInfo *info,
	const gchar *license_url)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->license_url);
	priv->license_url = g_strdup(license_url);
}

static void
gplugin_plugin_info_set_icon_name(
	GPluginPluginInfo *info,
	const gchar *icon_name)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->icon_name);
	priv->icon_name = g_strdup(icon_name);
}

static void
gplugin_plugin_info_set_summary(GPluginPluginInfo *info, const gchar *summary)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->summary);
	priv->summary = g_strdup(summary);
}

static void
gplugin_plugin_info_set_description(
	GPluginPluginInfo *info,
	const gchar *description)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->description);
	priv->description = g_strdup(description);
}

static void
gplugin_plugin_info_set_category(GPluginPluginInfo *info, const gchar *category)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->category);
	priv->category = g_strdup(category);
}

static void
gplugin_plugin_info_set_authors(
	GPluginPluginInfo *info,
	const gchar *const *authors)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_strfreev(priv->authors);

	priv->authors = g_strdupv((gchar **)authors);
}

static void
gplugin_plugin_info_set_website(GPluginPluginInfo *info, const gchar *website)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_free(priv->website);
	priv->website = g_strdup(website);
}

static void
gplugin_plugin_info_set_dependencies(
	GPluginPluginInfo *info,
	const gchar *const *dependencies)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(info);

	g_strfreev(priv->dependencies);

	priv->dependencies = g_strdupv((gchar **)dependencies);
}

/******************************************************************************
 * Object Stuff
 *****************************************************************************/
static void
gplugin_plugin_info_get_property(
	GObject *obj,
	guint param_id,
	GValue *value,
	GParamSpec *pspec)
{
	GPluginPluginInfo *info = GPLUGIN_PLUGIN_INFO(obj);

	switch(param_id) {
		case PROP_ID:
			g_value_set_string(value, gplugin_plugin_info_get_id(info));
			break;
		case PROP_PROVIDES:
			g_value_set_boxed(value, gplugin_plugin_info_get_provides(info));
			break;
		case PROP_PRIORITY:
			g_value_set_int(value, gplugin_plugin_info_get_priority(info));
			break;
		case PROP_ABI_VERSION:
			g_value_set_uint(value, gplugin_plugin_info_get_abi_version(info));
			break;
		case PROP_INTERNAL:
			g_value_set_boolean(value, gplugin_plugin_info_get_internal(info));
			break;
		case PROP_LOQ:
			g_value_set_boolean(
				value,
				gplugin_plugin_info_get_load_on_query(info));
			break;
		case PROP_BIND_GLOBAL:
			g_value_set_boolean(
				value,
				gplugin_plugin_info_get_bind_global(info));
			break;
		case PROP_NAME:
			g_value_set_string(value, gplugin_plugin_info_get_name(info));
			break;
		case PROP_VERSION:
			g_value_set_string(value, gplugin_plugin_info_get_version(info));
			break;
		case PROP_LICENSE_ID:
			g_value_set_string(value, gplugin_plugin_info_get_license_id(info));
			break;
		case PROP_LICENSE_TEXT:
			g_value_set_string(
				value,
				gplugin_plugin_info_get_license_text(info));
			break;
		case PROP_LICENSE_URL:
			g_value_set_string(
				value,
				gplugin_plugin_info_get_license_url(info));
			break;
		case PROP_ICON_NAME:
			g_value_set_string(value, gplugin_plugin_info_get_icon_name(info));
			break;
		case PROP_SUMMARY:
			g_value_set_string(value, gplugin_plugin_info_get_summary(info));
			break;
		case PROP_DESCRIPTION:
			g_value_set_string(
				value,
				gplugin_plugin_info_get_description(info));
			break;
		case PROP_CATEGORY:
			g_value_set_string(value, gplugin_plugin_info_get_category(info));
			break;
		case PROP_AUTHORS:
			g_value_set_boxed(value, gplugin_plugin_info_get_authors(info));
			break;
		case PROP_WEBSITE:
			g_value_set_string(value, gplugin_plugin_info_get_website(info));
			break;
		case PROP_DEPENDENCIES:
			g_value_set_boxed(
				value,
				gplugin_plugin_info_get_dependencies(info));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, param_id, pspec);
			break;
	}
}

static void
gplugin_plugin_info_set_property(
	GObject *obj,
	guint param_id,
	const GValue *value,
	GParamSpec *pspec)
{
	GPluginPluginInfo *info = GPLUGIN_PLUGIN_INFO(obj);

	switch(param_id) {
		case PROP_ID:
			gplugin_plugin_info_set_id(info, g_value_get_string(value));
			break;
		case PROP_PROVIDES:
			gplugin_plugin_info_set_provides(info, g_value_get_boxed(value));
			break;
		case PROP_PRIORITY:
			gplugin_plugin_info_set_priority(info, g_value_get_int(value));
			break;
		case PROP_ABI_VERSION:
			gplugin_plugin_info_set_abi_version(info, g_value_get_uint(value));
			break;
		case PROP_INTERNAL:
			gplugin_plugin_info_set_internal(info, g_value_get_boolean(value));
			break;
		case PROP_LOQ:
			gplugin_plugin_info_set_load_on_query(
				info,
				g_value_get_boolean(value));
			break;
		case PROP_BIND_GLOBAL:
			gplugin_plugin_info_set_bind_global(
				info,
				g_value_get_boolean(value));
			break;
		case PROP_NAME:
			gplugin_plugin_info_set_name(info, g_value_get_string(value));
			break;
		case PROP_VERSION:
			gplugin_plugin_info_set_version(info, g_value_get_string(value));
			break;
		case PROP_LICENSE_ID:
			gplugin_plugin_info_set_license_id(info, g_value_get_string(value));
			break;
		case PROP_LICENSE_TEXT:
			gplugin_plugin_info_set_license_text(
				info,
				g_value_get_string(value));
			break;
		case PROP_LICENSE_URL:
			gplugin_plugin_info_set_license_url(
				info,
				g_value_get_string(value));
			break;
		case PROP_ICON_NAME:
			gplugin_plugin_info_set_icon_name(info, g_value_get_string(value));
			break;
		case PROP_SUMMARY:
			gplugin_plugin_info_set_summary(info, g_value_get_string(value));
			break;
		case PROP_DESCRIPTION:
			gplugin_plugin_info_set_description(
				info,
				g_value_get_string(value));
			break;
		case PROP_CATEGORY:
			gplugin_plugin_info_set_category(info, g_value_get_string(value));
			break;
		case PROP_AUTHORS:
			gplugin_plugin_info_set_authors(info, g_value_get_boxed(value));
			break;
		case PROP_WEBSITE:
			gplugin_plugin_info_set_website(info, g_value_get_string(value));
			break;
		case PROP_DEPENDENCIES:
			gplugin_plugin_info_set_dependencies(
				info,
				g_value_get_boxed(value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, param_id, pspec);
			break;
	}
}

static void
gplugin_plugin_info_finalize(GObject *obj)
{
	GPluginPluginInfoPrivate *priv =
		gplugin_plugin_info_get_instance_private(GPLUGIN_PLUGIN_INFO(obj));

	g_clear_pointer(&priv->id, g_free);
	g_clear_pointer(&priv->provides, g_strfreev);
	g_clear_pointer(&priv->name, g_free);
	g_clear_pointer(&priv->version, g_free);
	g_clear_pointer(&priv->license_id, g_free);
	g_clear_pointer(&priv->license_text, g_free);
	g_clear_pointer(&priv->license_url, g_free);
	g_clear_pointer(&priv->icon_name, g_free);
	g_clear_pointer(&priv->summary, g_free);
	g_clear_pointer(&priv->description, g_free);
	g_clear_pointer(&priv->authors, g_strfreev);
	g_clear_pointer(&priv->website, g_free);
	g_clear_pointer(&priv->dependencies, g_strfreev);
	g_clear_pointer(&priv->category, g_free);

	G_OBJECT_CLASS(gplugin_plugin_info_parent_class)->finalize(obj);
}

static void
gplugin_plugin_info_init(G_GNUC_UNUSED GPluginPluginInfo *info)
{
}

static void
gplugin_plugin_info_class_init(GPluginPluginInfoClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	obj_class->get_property = gplugin_plugin_info_get_property;
	obj_class->set_property = gplugin_plugin_info_set_property;
	obj_class->finalize = gplugin_plugin_info_finalize;

	/* properties */
	/**
	 * GPluginPluginInfo:id:
	 *
	 * The id of the plugin.
	 *
	 * While not required, the recommended convention is to use the following
	 * format: &lt;application or library&gt;/&lt;name of the plugin&gt;.
	 *
	 * For example, the Python3 loader in GPlugin has an id of
	 * "gplugin/python3-loader".
	 */
	properties[PROP_ID] = g_param_spec_string(
		"id",
		"id",
		"The ID of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:provides:
	 *
	 * A list of additional plugin ids and versions that this plugin can
	 * provide.  This mechanism is used so that plugins can replace and extend
	 * the behavior of other plugins.
	 *
	 * The format fields should either be <literal>&lt;plugin-id&gt;</literal>
	 * or <literal>&lt;plugin-id&gt;=&lt;plugin-version&gt;</literal>.  The
	 * optional version is used to help resolve dependencies that are based
	 * on a specific version.
	 *
	 * Since: 0.32.0
	 */
	properties[PROP_PROVIDES] = g_param_spec_boxed(
		"provides",
		"provides",
		"The additional ids that this plugin provides.",
		G_TYPE_STRV,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:priority:
	 *
	 * The priority that this plugin should have when determining which plugin
	 * to use when multiple plugins have the same id or provides. Higher values
	 * take precedence over lower values.  If two plugins have the same id and
	 * priority, the first one found will be used.
	 *
	 * Since: 0.32.0
	 */
	properties[PROP_PRIORITY] = g_param_spec_int(
		"priority",
		"priority",
		"The priority of the plugin",
		G_MININT,
		G_MAXINT,
		0,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS);

	/**
	 * GPluginPluginInfo:abi-version:
	 *
	 * The GPlugin ABI version that the plugin was compiled against.
	 *
	 * GPlugin only uses the first byte (`0xff000000`) of this value.  The
	 * remaining 3 bytes are available for the application to use.
	 *
	 * Take the following example from an application:
	 *
	 * |[<!-- language="C" -->
	 *  #define ABI_VERSION (GPLUGIN_NATIVE_ABI_VERSION |
	 *                       (APPLICATION_MAJOR_VERSION << 8) |
	 *                       (APPLICATION_MINOR_VERSION))
	 * ]|
	 *
	 * The application here uses the thrid and fourth bytes, but could use
	 * the second as well.
	 */
	properties[PROP_ABI_VERSION] = g_param_spec_uint(
		"abi-version",
		"abi_version",
		"The ABI version of the plugin",
		0,
		G_MAXUINT32,
		0,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:internal:
	 *
	 * Whether or not the plugin is considered an "internal" plugin.
	 *
	 * Defaults to %FALSE.
	 */
	properties[PROP_INTERNAL] = g_param_spec_boolean(
		"internal",
		"internal",
		"Whether or not the plugin is an internal plugin",
		FALSE,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS);

	/**
	 * GPluginPluginInfo:load-on-query:
	 *
	 * Whether or not the plugin should be loaded when it's queried.
	 *
	 * This is used by the loaders and may be useful to your application as
	 * well.
	 *
	 * Defaults to %FALSE.
	 */
	properties[PROP_LOQ] = g_param_spec_boolean(
		"load-on-query",
		"load-on-query",
		"Whether or not the plugin should be loaded when queried",
		FALSE,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS);

	/**
	 * GPluginPluginInfo:bind-global:
	 *
	 * Determines whether the plugin should be have its symbols bound globally.
	 *
	 * Note: This should only be used by the native plugin loader.
	 */
	properties[PROP_BIND_GLOBAL] = g_param_spec_boolean(
		"bind-global",
		"bind-global",
		"Whether symbols should be bound globally",
		FALSE,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS);

	/**
	 * GPluginPluginInfo:name:
	 *
	 * The display name of the plugin.  This should be a translated string.
	 */
	properties[PROP_NAME] = g_param_spec_string(
		"name",
		"name",
		"The name of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:version:
	 *
	 * The version of the plugin.  Preferably a semantic version.
	 */
	properties[PROP_VERSION] = g_param_spec_string(
		"version",
		"version",
		"The version of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:license-id:
	 *
	 * The short name of the license.
	 *
	 * It is recommended to use the identifier of the license from
	 * https://spdx.org/licenses/ and should be "Other" for licenses that are
	 * not listed.
	 *
	 * If a plugin has multiple license, they should be separated by a pipe
	 * (|). In the odd case that you have multiple licenses that are used at
	 * the same time, they should be separated by an ampersand (&).
	 */
	properties[PROP_LICENSE_ID] = g_param_spec_string(
		"license-id",
		"license-id",
		"The license id of the plugin according to SPDX",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:license-text:
	 *
	 * The text of the license for this plugin.  This should only be used when
	 * the plugin is licensed under a license that is not listed at spdx.org.
	 */
	properties[PROP_LICENSE_TEXT] = g_param_spec_string(
		"license-text",
		"license text",
		"The text of the license for the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:license-url:
	 *
	 * The url to the text of the license.  This should primarily only be used
	 * for licenses not listed at spdx.org.
	 */
	properties[PROP_LICENSE_URL] = g_param_spec_string(
		"license-url",
		"license url",
		"The url to the license of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:icon-name:
	 *
	 * A XDG icon name for the plugin.  The actual use of this is determined by
	 * the application/library using GPlugin.
	 */
	properties[PROP_ICON_NAME] = g_param_spec_string(
		"icon-name",
		"icon-name",
		"The XDG icon name for the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:summary:
	 *
	 * A short description of the plugin that can be listed with the name in a
	 * user interface.
	 */
	properties[PROP_SUMMARY] = g_param_spec_string(
		"summary",
		"summary",
		"The summary of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:description:
	 *
	 * The full description of the plugin that will be used in a "more
	 * information" section in a user interface.
	 */
	properties[PROP_DESCRIPTION] = g_param_spec_string(
		"description",
		"description",
		"The description of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:category:
	 *
	 * The category of this plugin.
	 *
	 * This property is used to organize plugins into categories in a user
	 * interface.  It is recommended that an application has a well defined
	 * set of categories that plugin authors should use, and put all plugins
	 * that don't match this category into an "Other" category.
	 */
	properties[PROP_CATEGORY] = g_param_spec_string(
		"category",
		"category",
		"The category of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:authors:
	 *
	 * A list of the names and email addresses of the authors.
	 *
	 * It is recommended to use the RFC 822, 2822 format of:
	 * `"First Last <user@domain.com>"`.
	 */
	properties[PROP_AUTHORS] = g_param_spec_boxed(
		"authors",
		"authors",
		"The authors of the plugin",
		G_TYPE_STRV,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:website:
	 *
	 * The url of the plugin that can be represented in a user interface.
	 */
	properties[PROP_WEBSITE] = g_param_spec_string(
		"website",
		"website",
		"The website of the plugin",
		NULL,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	/**
	 * GPluginPluginInfo:dependencies:
	 *
	 * A comma separated list of plugin id's that this plugin depends on.
	 */
	properties[PROP_DEPENDENCIES] = g_param_spec_boxed(
		"dependencies",
		"dependencies",
		"The dependencies of the plugin",
		G_TYPE_STRV,
		G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_CONSTRUCT_ONLY);

	g_object_class_install_properties(obj_class, N_PROPERTIES, properties);
}

/******************************************************************************
 * GPluginPlugin API
 *****************************************************************************/

/**
 * gplugin_plugin_info_new: (skip)
 * @id: The id of the plugin.
 * @abi_version: The GPlugin ABI version that the plugin uses.
 * @...: name/value pairs of properties to set, followed by %NULL.
 *
 * Creates a new #GPluginPluginInfo instance.
 *
 * Returns: (transfer full): The new #GPluginPluginInfo instance.
 */

/**
 * gplugin_plugin_info_get_id:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the id that the plugin identifies itself as.
 *
 * Returns: The id from @info.
 */
const gchar *
gplugin_plugin_info_get_id(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->id;
}

/**
 * gplugin_info_get_id_normalized:
 * @info: The #GPluginPluginInfo instance.
 *
 * Gets the normalized version of the id from @info.  That is, a version where
 * only alpha-numeric and -'s are in the id.
 *
 * Returns: (transfer full): The normalized id of @info.
 */
gchar *
gplugin_info_get_id_normalized(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;
	gchar *copy = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	/* this only happens if an id wasn't passed, but that should be caught by
	 * loader and then the manager, but that doesn't stop someone from just
	 * creating a GPluginPluginInfo and doing dumb shit with it.
	 */
	if(priv->id == NULL) {
		return NULL;
	}

	copy = g_strdup(priv->id);

	return g_strcanon(copy, G_CSET_A_2_Z G_CSET_a_2_z G_CSET_DIGITS "-", '-');
}

/**
 * gplugin_plugin_info_get_provides:
 * @info: The #GPluginPluginInfo instance.
 *
 * Gets the provides of the plugin as specified in @info.
 *
 * Returns: (array zero-terminated=1) (transfer none): The list of
 *          dependencies from @info.
 *
 * Since: 0.32.0
 */
const gchar *const *
gplugin_plugin_info_get_provides(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return (const gchar *const *)priv->provides;
}

/**
 * gplugin_plugin_info_get_priority:
 * @info: The #GPluginPluginInfo instance.
 *
 * Gets the priority of the plugin as specified in @info.
 *
 * Returns: The priority from @info.
 *
 * Since: 0.32.0
 */
gint
gplugin_plugin_info_get_priority(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), 0);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->priority;
}

/**
 * gplugin_plugin_info_get_abi_version:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the ABI or Application Binary Interface version that the plugin
 * is supposed to work against.
 *
 * Returns: The abi_version from @info.
 */
guint32
gplugin_plugin_info_get_abi_version(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), 0);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->abi_version;
}

/**
 * gplugin_plugin_info_get_internal:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns where or not this plugin is is considered an internal plugin.  An
 * internal plugin would be something like a plugin loader or another plugin
 * that should not be shown to users.
 *
 * Returns: %TRUE if the plugin is internal, %FALSE otherwise.
 */
gboolean
gplugin_plugin_info_get_internal(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), FALSE);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->internal;
}

/**
 * gplugin_plugin_info_get_load_on_query:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns whether or not this plugin should be loaded when queried.  This is
 * useful for internal plugins that are adding functionality and should always
 * be turned on.  The plugin loaders use this to make sure all plugins can
 * always be loaded.
 *
 * Returns: %TRUE if the plugin should be loaded on query, %FALSE otherwise.
 */
gboolean
gplugin_plugin_info_get_load_on_query(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), FALSE);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->load_on_query;
}

/**
 * gplugin_plugin_info_get_name:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the name of the plugin as specified in @info.
 *
 * Returns: The name from @info.
 */
const gchar *
gplugin_plugin_info_get_name(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->name;
}

/**
 * gplugin_plugin_info_get_version:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the version of the plugin as specified in @info.
 *
 * Returns: The version from @info.
 */
const gchar *
gplugin_plugin_info_get_version(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->version;
}

/**
 * gplugin_plugin_info_get_license_id:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the liences id for the plugin as specified in @info.
 *
 * Returns: The license-id from @info.
 */
const gchar *
gplugin_plugin_info_get_license_id(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->license_id;
}

/**
 * gplugin_plugin_info_get_license_text:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the license text for the plugin as specified in @info.
 *
 * Returns: The text of the license from @info.
 */
const gchar *
gplugin_plugin_info_get_license_text(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->license_text;
}

/**
 * gplugin_plugin_info_get_license_url:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the url of the license for the plugin as specified in @info
 *
 * Returns: The url of the license from @info.
 */
const gchar *
gplugin_plugin_info_get_license_url(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->license_url;
}

/**
 * gplugin_plugin_info_get_icon_name:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the name of the icon for the plugin as specified in @info.
 *
 * Returns: The icon name from @info.
 */
const gchar *
gplugin_plugin_info_get_icon_name(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->icon_name;
}

/**
 * gplugin_plugin_info_get_summary:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the summery for the plugin as specified in @info.
 *
 * Returns: The summary from @info.
 */
const gchar *
gplugin_plugin_info_get_summary(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->summary;
}

/**
 * gplugin_plugin_info_get_description:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the description for the plugin as specified in @info.
 *
 * Returns: The description from @info.
 */
const gchar *
gplugin_plugin_info_get_description(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->description;
}

/**
 * gplugin_plugin_info_get_category:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the category of the plugin as specified in @info.
 *
 * Returns: The category from @info.
 */
const gchar *
gplugin_plugin_info_get_category(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->category;
}

/**
 * gplugin_plugin_info_get_authors:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the authors of the plugin as specified in @info.
 *
 * Returns: (array zero-terminated=1) (transfer none): The authors from @info.
 */
const gchar *const *
gplugin_plugin_info_get_authors(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return (const gchar *const *)priv->authors;
}

/**
 * gplugin_plugin_info_get_website:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the website for the plugin as specified in @info.
 *
 * Returns: The website from @info.
 */
const gchar *
gplugin_plugin_info_get_website(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->website;
}

/**
 * gplugin_plugin_info_get_dependencies:
 * @info: The #GPluginPluginInfo instance.
 *
 * Returns the dependencies of the plugins as specified in @info.
 *
 * Returns: (array zero-terminated=1) (transfer none): The list of
 *          dependencies from @info.
 */
const gchar *const *
gplugin_plugin_info_get_dependencies(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), NULL);

	priv = gplugin_plugin_info_get_instance_private(info);

	return (const gchar *const *)priv->dependencies;
}

/**
 * gplugin_plugin_info_get_bind_global:
 * @info: The #GPluginPluginInfo instance.
 *
 * This propoerty and therefore function is only used by the native plugin
 * loader.
 *
 * Returns: %TRUE if the plugin has requested to be loaded with its symbols
 *          bound global, %FALSE if they should be bound locally.
 */
gboolean
gplugin_plugin_info_get_bind_global(GPluginPluginInfo *info)
{
	GPluginPluginInfoPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PLUGIN_INFO(info), FALSE);

	priv = gplugin_plugin_info_get_instance_private(info);

	return priv->bind_global;
}
