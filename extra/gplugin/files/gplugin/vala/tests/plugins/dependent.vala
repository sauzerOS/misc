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
using GPlugin;

public class DependentPluginInfo : GPlugin.PluginInfo {
	public DependentPluginInfo() {
		string[] dependencies = {"dependency1", "dependency2"};

		Object(
			id: "gplugin/vala-dependent-plugin",
			dependencies: dependencies
		);
	}
}

public GPlugin.PluginInfo gplugin_query(out Error error) {
	error = null;

	return new DependentPluginInfo();
}

public bool gplugin_load(GPlugin.Plugin plugin, out Error error) {
	error = null;

	return true;
}

public bool gplugin_unload(GPlugin.Plugin plugin, out Error error) {
	error = null;

	return false;
}
