project('SolveCad', ['cpp', 'c'],
  version: '1.3.0',
  meson_version: '>=1.3.0',
  default_options: ['cpp_std=c++20', 'warning_level=1'],
)

cxx = meson.get_compiler('cpp')
is_windows = target_machine.system() == 'windows'



gtk4 = dependency('gtk4', version: '>=4.10')
pthread = cxx.find_library('pthread')
gtkmm = dependency('gtkmm-4.0', version: '>=4.10')
epoxy = dependency('epoxy')
eigen = dependency('eigen3')
glm = dependency('glm')
harfbuzz = dependency('harfbuzz')
freetype = dependency('freetype2')
png = dependency('libpng')
libpython = dependency('python3', required: false, disabler:true)
pybind11 = dependency('pybind11', required: false, disabler:true)

spnav = dependency('spnav', required: false)
if not spnav.found()
    spnav = cxx.find_library('spnav', required: false)
endif

src_common = files(
  'util/msd_animator.cpp',
  'util/msd.cpp',
  'util/picture_data.cpp',
  'util/uuid.cpp',
 

)

src_gui = files(
  'main.cpp',
  'canvas/canvas.cpp',
  'canvas/appearance.cpp',
  'canvas/chunk.cpp',
  'canvas/gl_util.cpp',
  'canvas/base_renderer.cpp',
  'canvas/background_renderer.cpp',
  'canvas/face_renderer.cpp',
  'canvas/line_renderer.cpp',
  'canvas/glyph_renderer.cpp',
  'canvas/glyph_3d_renderer.cpp',
  'canvas/box_selection.cpp',
  'canvas/bitmap_font_util.cpp',
  'canvas/bitmap_font/bitmap_font_desc.c',
  'canvas/bitmap_font/bitmap_font_img.c',
  'canvas/icon_renderer.cpp',
  'canvas/picture_renderer.cpp',
  'canvas/selection_texture_renderer.cpp',
  'canvas/selectable_ref.cpp',
  'logger/log_dispatcher.cpp',
  'logger/logger.cpp',
  'canvas/icon_texture_map.cpp',
)


fs = import('fs')
has_git_dir = fs.is_dir('.git')
version_deps = ['version.py']
if has_git_dir
    message('including git commit')
    version_deps += ['.git/HEAD', '.git/index']
endif

prog_python = find_program('python3')


gnome = import('gnome')
resources = gnome.compile_resources(
  'resources',
  'resource.xml',
  c_name: 'SolveCad_resources',
  source_dir: '/'
)

cpp_args = ['-DLIBRARY', '-DUSINGZ', '-D_USE_MATH_DEFINES', '-DGLM_ENABLE_EXPERIMENTAL']

if spnav.found()
    cpp_args += '-DHAVE_SPNAV'
endif

stdlibs = []
is_libstdcpp = cxx.get_define('__GLIBCXX__', prefix: '#include <vector>') != ''
if is_libstdcpp
    message('using libstdc++')
else
    message('not using libstdc++')
endif
if is_libstdcpp
    stdlibs += cxx.find_library('stdc++')
    stdlibs += cxx.find_library('stdc++fs', required:false)
endif

build_dependencies = [gtk4, gtkmm, epoxy, eigen, glm, stdlibs, spnav, harfbuzz, freetype, png, pthread]
if not is_windows
	uuid = dependency('uuid')
	build_dependencies += uuid
else
	build_dependencies += [cxx.find_library('rpcrt4')]
	src_common += 'src/util/uuid_win32.cpp'
	cpp_args += '-DWIN32_UUID'
endif



build_dependencies_py = build_dependencies + [libpython, pybind11]

include_directories = [
  include_directories('canvas'),
  include_directories('util'),
  include_directories('logger'),
]


has_wayland = cxx.has_define('GDK_WINDOWING_WAYLAND', dependencies:[gtk4], prefix:'#include <gdk/gdk.h>')

extra_libraries = []

if has_wayland
  subdir('3rd_party/wayland-proxy')
  extra_libraries += wayland_proxy
  cpp_args += '-DHAVE_WAYLAND_PROXY'
endif


datadir = get_option('datadir')
install_data('org.SolveCad.SolveCad.desktop', install_dir:datadir / 'applications')
install_data('org.SolveCad.SolveCad.metainfo.xml', install_dir:datadir / 'metainfo')
icondir = datadir / 'icons/hicolor'

install_data('icons/scalable/apps/dune3d.svg', install_dir: icondir /  'scalable/apps', rename: 'org.dune3d.dune3d.svg')


dune3d = executable('dune3d',
    [src_common, src_gui],
    dependencies: [build_dependencies],
    link_with: [] + extra_libraries,
    cpp_args: cpp_args,
    include_directories: include_directories,
    win_subsystem: 'windows',
    install: true
)
