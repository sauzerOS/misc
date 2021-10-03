###############################################################################
# Project Info
###############################################################################
project('gplugin', 'c',
	license : 'LGPL-2.0-or-later',
	version : '0.34.1',
	meson_version : '>=0.56.0',
	default_options : ['c_std=c99'])

parts = meson.project_version().split('-')
if parts.length() > 1
	extra = parts[1]
else
	extra = ''
endif

parts = parts[0].split('.')
GPLUGIN_MAJOR_VERSION = parts[0]

version_conf = configuration_data()
version_conf.set('GPLUGIN_MAJOR_VERSION', GPLUGIN_MAJOR_VERSION)
version_conf.set('GPLUGIN_MINOR_VERSION', parts[1])
version_conf.set('GPLUGIN_MICRO_VERSION', parts[2])
version_conf.set('GPLUGIN_EXTRA_VERSION', extra)
version_conf.set('GPLUGIN_VERSION', meson.project_version())

###############################################################################
# Dependencies
###############################################################################
gnome = import('gnome')
pkgconfig = import('pkgconfig')

if get_option('help2man')
	help2man = find_program('help2man')
endif

GLIB = dependency('glib-2.0', version : '>=2.40.0')
GOBJECT = dependency('gobject-2.0')

# we separate gmodule out so our test aren't linked to it
GMODULE = dependency('gmodule-2.0')

###############################################################################
# NLS
###############################################################################
GETTEXT_PACKAGE = 'gplugin'
LOCALE_DIR = get_option('prefix') / get_option('localedir')

add_project_arguments('-DLOCALEDIR="@0@"'.format(LOCALE_DIR), language : 'c')
add_project_arguments('-DGETTEXT_PACKAGE="@0@"'.format(GETTEXT_PACKAGE),
	language : 'c')

if get_option('nls')
	i18n = import('i18n')
endif

###############################################################################
# Build Info
###############################################################################
compiler = meson.get_compiler('c')

add_project_arguments(
	'-DPREFIX="@0@"'.format(get_option('prefix')),
	'-DLIBDIR="@0@"'.format(get_option('libdir')),
	'-DGPLUGIN_WEBSITE="https://keep.imfreedom.org/gplugin/gplugin"',
	language : 'c'
)

if compiler.has_argument('-Wformat')
	add_project_arguments('-Wformat', language : 'c')
	if compiler.has_multi_arguments(['-Wformat', '-Werror=format-security'])
		add_project_arguments('-Werror=format-security', language : 'c')
	endif
endif

toplevel_inc = include_directories('.')

###############################################################################
# gtk-doc
###############################################################################
if get_option('doc') and not get_option('introspection')
	error('Documentation requires GObject Introspection.')
endif

gidocgen_dep = dependency(
	'gi-docgen', version: '>= 2021.1',
	fallback: ['gi-docgen', 'dummy_dep'],
	required: get_option('doc')
)

gidocgen = find_program('gi-docgen', required : get_option('doc'))
docs_dir = get_option('prefix') / get_option('datadir') / 'doc'

###############################################################################
# Subdirectories
###############################################################################
subdir('gplugin')
subdir('gplugin-gtk')
subdir('gplugin-gtk-viewer')
subdir('gplugin-query')
subdir('packaging')
subdir('po')

subdir('lua')
subdir('perl5')
subdir('python3')
subdir('rust')
subdir('tcc')
subdir('vala')

if get_option('doc')
	doc_targets = [gplugin_doc]
	if get_option('gtk3')
		doc_targets += gplugin_gtk_doc
	endif

	alias_target('doc', doc_targets)
endif

###############################################################################
# Install stuff
###############################################################################
# documentation
install_data('ChangeLog', 'INSTALL.md', 'README.md', 'HACKING.md',
	install_dir : get_option('datadir') / 'doc' / 'gplugin')

summary({
	'api reference' : get_option('doc'),
	'gtk3 widgets' : get_option('gtk3'),
	'man pages' : get_option('help2man'),
}, bool_yn : true, section : 'Miscellaneous')

summary({
	'introspection' : get_option('introspection'),
	'vapi' : get_option('vapi'),
}, bool_yn : true, section : 'Bindings')
