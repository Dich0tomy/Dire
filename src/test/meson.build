catch2 = dependency('Catch2', version: '3.4.0', required: false)
if not catch2.found()
  catch2_sub = cmake.subproject('catch2', options: build_type_opts, required: true)
  message('catch2 targets:\n - ' + '\n - '.join(catch2_sub.target_list()))

  catch2 = catch2_sub.dependency('Catch2')
endif

local_deps = [
  catch2
]

# NOTE: Look in test_main.cpp - I define the global test environment there
# Each test can change it's environment variables as it pleases too

os = build_machine.system()

test_files = []

if(os in [ 'linux', 'cygwin' ])
  test_files = [
    'xdg_user_dirs.cpp',
    'linux/base_dirs.cpp',
    'linux/user_dirs.cpp',
    'linux/project_dirs.cpp',
  ]
elif(os == 'windows')
  test_files += [
    'windows/project_dirs.cpp',
    'windows/user_dirs.cpp',
  ]
elif(os == 'darwin')
  test_files += [
    'mac/base_dirs.cpp',
    'mac/project_dirs.cpp',
    'mac/user_dirs.cpp',
  ]
endif

executable(
  'dire_test',
  test_files + [ 'test_main.cpp' ],
  include_directories: include_directories('.'),
  dependencies: [ _dire_test_internal, local_deps ]
)
