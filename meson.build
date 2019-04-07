project('vcvm', 'c', 'cpp',
  default_options : ['c_std=c11', 'cpp_std=c++14', 'buildtype=release'],
  meson_version : '>=0.49.0'
)

message('Using build type: ' + get_option('buildtype'))

force_velo_toolchain = get_option('force_velo_toolchain')

if force_velo_toolchain
  cc = meson.get_compiler('c')
  cc_version = run_command(cc.cmd_array() + ['--version'], check : true).stdout()
  if not cc_version.contains('(velo)')
    error('force_velo_toolchain is set and you arn\'t using the velo toolchain.')
  endif
  cpp = meson.get_compiler('cpp')
  cpp_version = run_command(cpp.cmd_array() + ['--version'], check : true).stdout()
  if not cpp_version.contains('(velo)')
    error('force_velo_toolchain is set and you arn\'t using the velo toolchain.')
  endif
else
  warning('Not using the blessed velo gcc toolchain. Here be dragons.')
endif

add_project_arguments('-Wall', '-Werror', '-Wextra', language : 'c')
add_project_arguments('-Wall', '-Werror', '-Wextra', language : 'cpp')

src = run_command('find', './src', '-name', '*.c', '-or', '-name', '*.h', check : true).stdout().strip().split('\n')
test_src = run_command('find', './test', '-name', '*.cpp', '-or', '-name', '*.h', check : true).stdout().strip().split('\n')

# testing is currently only used on native x86 builds. Creating a disabler will disable the test exe and test target.
if meson.is_cross_build()
  minunit = disabler()
else
  minunit = dependency('minunit', main : true, required : true)
endif

vpr = dependency(
  'vpr',
  required : true,
  fallback : ['vpr', 'vpr_dep']
)

vcvm_include = include_directories('include')

vcvm_lib = static_library('vcvm', src,
  include_directories : vcvm_include,
  dependencies : [vpr]
)

vcvm_dep = declare_dependency(
  link_with : vcvm_lib,
  include_directories : vcvm_include
)

vcvm_test = executable(
  'testvcvm',
  test_src,
  include_directories : vcvm_include,
  link_with : vcvm_lib,
  dependencies : [minunit, vpr]
)

test('testvcvm', vcvm_test)

# vim: ts=2 sw=2 et colorcolumn=120
