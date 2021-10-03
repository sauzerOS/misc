if get_option('doc')
	gplugin_gtk_toml = configure_file(
		input : 'gplugin-gtk.toml.in',
		output : 'gplugin-gtk.toml',
		configuration : version_conf,
		install : true,
		install_dir : docs_dir / 'gplugin-gtk',
	)

	gplugin_gtk_doc = custom_target('gplugin-gtk-doc',
		input : [ gplugin_gtk_toml, gplugin_gtk_gir[0] ],
		output : 'gplugin-gtk',
		command : [
			gidocgen,
			'generate',
			'--quiet',
			'--fatal-warnings',
			'--add-include-path=@0@'.format(meson.project_build_root() / 'gplugin'),
			'--config=@INPUT0@',
			'--output-dir=@OUTPUT@',
			'--no-namespace-dir',
			'--content-dir=@0@'.format(meson.current_source_dir()),
			'@INPUT1@'
		],
		depends : [ gplugin_gir[0] ],
		build_by_default : true,
		install : true,
		install_dir : docs_dir,
	)
endif

