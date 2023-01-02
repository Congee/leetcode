project(
  'leetcode',
  'c',
  'cpp',
  version: '0.1.0',
  license: 'MIT',
  meson_version: '>=0.57.1',
  default_options: [
    'cpp_std=c++20',
    'c_std=c11',
    'warning_level=3',
    'werror=false',
    'cpp_args=-Og -g',
    'cpp_debugstl=true',
  ],
)

compiler = meson.get_compiler('cpp')
cpp_args = []
link_args = []
coverage_args = ['-fprofile-instr-generate', '-fcoverage-mapping']

if compiler.get_id() == 'clang'
  add_global_arguments(['-fcolor-diagnostics', '-D__LOCAL__'], language : 'cpp')  # ninja color output
  # meson defaults to libstdc++: https://github.com/mesonbuild/meson/issues/8592
  add_global_link_arguments(['-stdlib=libc++'], language : 'cpp')
  if get_option('b_coverage')
    add_global_arguments(coverage_args, language : 'cpp')  # ninja color output
    add_global_link_arguments(coverage_args, language : 'cpp')
  endif
endif


cxxabi = host_machine.system() == 'darwin' ? compiler.find_library('c++abi') : []  # required on darwin

inc = [include_directories('include')]
deps = [cxxabi]

src = files(
  'src/main.cpp',
  'src/1206.design-skiplist.cpp',
)

executable(
  'main',
  src,
  include_directories: inc,
  dependencies: deps,
)
