fmt = dependency('fmt', version: '10.1.0', required: false)
if not fmt.found()
  fmt_sub = cmake.subproject('fmt', options: build_type_opts, required: true)
  message('fmt targets:\n - ' + '\n - '.join(fmt_sub.target_list()))

  fmt = fmt_sub.dependency('fmt')
endif

executable(
  'dire',
  'main.cpp',
  dependencies: [
    dire,
    fmt,
  ]
)
