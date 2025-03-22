project('Y11', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

sfml = dependency('sfml')
opengl = dependency('opengl')

executable(
  'Y11_sfml',
  [
    'y11.cc',
    'src/backends/sfml/sfml_backend.cc',
    'src/backends/sfml/sfml_renderer.cc',
    'src/backends/sfml/sfml_widget_metadata.cc',
    'src/widgets/rectangle.cc',
    'src/widgets/root.cc',
    'src/widgets/widget.cc',
    'src/widgets/common.cc',
    'src/widgets/layout.cc',
    'src/widgets/column.cc',
    # 'src/widgets/row.cc'
  ],
  dependencies: [ sfml, opengl ]
)

