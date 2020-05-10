libswd_version = meson.project_version()

swd_lib = library(
  'swd',
  [
    'libswd_bin.c',
    'libswd_bitgen.c',
    'libswd_bus.c',
    'libswd_cli.c',
    'libswd_cmd.c',
    'libswd_cmdq.c',
    'libswd_core.c',
    'libswd_dap.c',
    'libswd_debug.c',
    'libswd_drv.c',
    'libswd_error.c',
    'libswd_externs.c',
    'libswd_log.c',
    'libswd_memap.c',
  ],
  c_args: [
    '-Wno-missing-field-initializers',
  ],
  version: libswd_version,
  install: true,
)

libswd_dep = declare_dependency(
  include_directories: '.',
  link_with: swd_lib,
)

install_headers(['libswd.h'], subdir: 'swd')
pkg = import('pkgconfig')
pkg.generate(
  swd_lib,
  description: 'CeDeROM\'s Serial Wire Debug Open Library',
  version: libswd_version,
)

if get_option('application').enabled()
  readline_dep = dependency('readline', required: true)
  ftdi_dep = dependency('libftdi1', required: true)
  usb_dep = dependency('libusb-1.0', required: true)

  executable(
    'libswd_app',
    sources: [
      'libswd_app.c',
    ],
    dependencies: [
      readline_dep,
      ftdi_dep,
      usb_dep,
      libswd_dep,
    ],
  )
endif
