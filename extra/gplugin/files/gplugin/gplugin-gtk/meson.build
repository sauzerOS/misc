if get_option('gtk3')

###############################################################################
# Build Info
###############################################################################
GTK3 = dependency('gtk+-3.0', version : '>=3.0.0')

GPLUGIN_GTK_LIBRARY_VERSION = '0.1.0'

GPLUGIN_GTK_SOURCES = [
	'gplugin-gtk-plugin-info.c',
	'gplugin-gtk-store.c',
	'gplugin-gtk-view.c',
]

GPLUGIN_GTK_HEADERS = [
	'gplugin-gtk-plugin-info.h',
	'gplugin-gtk-store.h',
	'gplugin-gtk-view.h',
]

GPLUGIN_GTK_PRIVATE_SOURCES = [
]

GPLUGIN_GTK_PRIVATE_HEADERS = [
]

GPLUGIN_GTK_PUBLIC_BUILT_SOURCES = [
]

GPLUGIN_GTK_PUBLIC_BUILT_HEADERS = [
]

GPLUGIN_GTK_GENERATED_TARGETS = [
]

###############################################################################
# Configure Files
###############################################################################
GPLUGIN_GTK_H_INCLUDES = ''
foreach header : GPLUGIN_GTK_HEADERS
	GPLUGIN_GTK_H_INCLUDES = '@0@\n#include <gplugin-gtk/@1@>'.format(
		GPLUGIN_GTK_H_INCLUDES,
		header)
endforeach

conf = configuration_data()
conf.set('GPLUGIN_GTK_H_INCLUDES', GPLUGIN_GTK_H_INCLUDES)
gplugin_gtk_h = configure_file(
	input : 'gplugin-gtk.h.in',
	output : 'gplugin-gtk.h',
	configuration : conf,
	install : true,
	install_dir : get_option('includedir') / 'gplugin-1.0')

gplugin_gtk_xml = configure_file(
	input : 'gplugin-gtk.xml.in',
	output: 'gplugin-gtk.xml',
	configuration : version_conf,
	install: true,
	install_dir : get_option('datadir') / 'glade' / 'catalogs',
)

###############################################################################
# Resource Target
###############################################################################
gplugin_gtk_resources = gnome.compile_resources(
	'gplugin-gtk-resources',
	'data/gplugin-gtk.gresource.xml',
	c_name: 'gplugin_gtk',
	source_dir: 'data')

###############################################################################
# Library Target
###############################################################################
gplugin_gtk = shared_library('gplugin-gtk',
	GPLUGIN_GTK_SOURCES,
	GPLUGIN_GTK_HEADERS,
	GPLUGIN_GTK_PRIVATE_SOURCES,
	GPLUGIN_GTK_PRIVATE_HEADERS,
	GPLUGIN_GTK_PUBLIC_BUILT_SOURCES,
	GPLUGIN_GTK_PUBLIC_BUILT_HEADERS,
	gplugin_gtk_resources,
	c_args : ['-DGPLUGIN_GTK_COMPILATION', '-DG_LOG_DOMAIN="GPluginGtk"'],
	include_directories : toplevel_inc,
	dependencies : [gplugin_dep, GTK3],
	version : GPLUGIN_GTK_LIBRARY_VERSION,
	install : true
)

gplugin_gtk_inc = include_directories('.')

pkgconfig.generate(
	gplugin_gtk,
	name : 'gplugin-gtk',
	description : 'Gtk widgets for GPlugin',
	filebase : 'gplugin-gtk',
	subdirs : 'gplugin-1.0',
	libraries : [gplugin],
	requires : [GLIB, GOBJECT, GMODULE],
	variables : [
		'plugindir=${libdir}',
	],
)

###############################################################################
# GObject Introspection
###############################################################################
if get_option('introspection')
	gplugin_gtk_gir = gnome.generate_gir(
		gplugin_gtk,
		sources : GPLUGIN_GTK_SOURCES + GPLUGIN_GTK_HEADERS +
		          GPLUGIN_GTK_PUBLIC_BUILT_SOURCES +
		          GPLUGIN_GTK_PUBLIC_BUILT_HEADERS,
		includes : [gplugin_gir[0], 'Gtk-3.0'],
		namespace : 'GPluginGtk',
		symbol_prefix : 'gplugin_gtk',
		nsversion : '1.0',
		install : true,
		export_packages: ['gplugin-gtk'],
		dependencies : [gplugin_dep],
		extra_args : ['--quiet', '-DGPLUGIN_GTK_COMPILATION'])
	GPLUGIN_GTK_GENERATED_TARGETS += gplugin_gtk_gir
endif

###############################################################################
# Library Dependency Object
###############################################################################
gplugin_gtk_dep = declare_dependency(
	include_directories: [toplevel_inc, gplugin_gtk_inc],
	link_with : [gplugin, gplugin_gtk],
	sources : GPLUGIN_GTK_PUBLIC_BUILT_HEADERS + GPLUGIN_GTK_GENERATED_TARGETS,
	dependencies : [GLIB, GOBJECT, GTK3],
)

if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('gplugin-gtk', gplugin_gtk_dep)
endif

###############################################################################
# Install Stuff
###############################################################################
# install the normal includes into the gplugin-gtk subdirectory
install_headers(
	GPLUGIN_GTK_HEADERS,
	subdir : 'gplugin-1.0/gplugin-gtk'
)

###############################################################################
# subdirectories
###############################################################################
subdir('reference')

endif  # gtk3
