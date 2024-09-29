
rtld_sources += files(
	'generic/sysdeps.cpp',
)

libc_sources += files(
	'generic/entry.cpp',
	'generic/sysdeps.cpp',
)

if not no_headers
	install_headers(
		'include/abi-bits/errno.h',
		'include/abi-bits/fcntl.h',
		'include/abi-bits/blkcnt_t.h',
		'include/abi-bits/blksize_t.h',
		'include/abi-bits/dev_t.h',
		'include/abi-bits/gid_t.h',
		'include/abi-bits/ino_t.h',
		'include/abi-bits/mode_t.h',
		'include/abi-bits/nlink_t.h',
		'include/abi-bits/pid_t.h',
		'include/abi-bits/uid_t.h',
		'include/abi-bits/limits.h',
		'include/abi-bits/fsfilcnt_t.h',
		'include/abi-bits/fsblkcnt_t.h',
                'include/abi-bits/time_t.h',
                'include/abi-bits/stat.h',
		subdir: 'abi-bits',
		follow_symlinks: true
	)
	install_headers(
		'include/vintix/syscall.h',
		subdir: 'vintix'
	)
endif

if not headers_only
	crt = custom_target('crt0',
		build_by_default: true,
		command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
		input: 'x86/crt-src/crt0.S',
		output: 'crt0.o',
		install: true,
		install_dir: get_option('libdir')
	)
endif

