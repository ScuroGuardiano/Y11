project('Y11', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

sfml = dependency('sfml')
opengl = dependency('opengl')

y11_sources = [
  'y11.cc',
  'src/widgets/rectangle.cc',
  'src/widgets/root.cc',
  'src/widgets/widget.cc',
  'src/widgets/common.cc',
  'src/widgets/layout.cc',
  'src/widgets/column.cc',
  'src/widgets/row.cc',
  'src/widgets/composite.cc',
  'src/widgets/circle.cc',
  'src/widgets/ellipse.cc',
  'src/widgets/text.cc',
  'src/animations/keyframe.cc',
  'src/animations/animation.cc',
  'src/events/cursor.cc',
  'src/widgets/button.cc',
]

executable(
  'Y11_sfml',
  y11_sources + [
    'src/backends/sfml/sfml_backend.cc',
    'src/backends/sfml/sfml_renderer.cc',
    'src/backends/sfml/sfml_widget_metadata.cc',
  ],
  dependencies: [ sfml, opengl ],
  cpp_args: '-DY11_BACKEND_USE_SFML'
)

# executable(
#   'Y11_blank',
#   y11_sources,
#   cpp_args: '-DY11_BACKEND_USE_BLANK'
# )
