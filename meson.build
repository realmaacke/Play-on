project('Play-on-client', 'cpp',
  version : '0.1.0',
  default_options : [
    'cpp_std=c++20',
    'warning_level=2',
    'buildtype=debugoptimized'
  ]
)

rapidjson_dep = dependency('RapidJSON', fallback : ['rapidjson', 'rapidjson_dep'])
gtkmm_dep = dependency('gtkmm-4.0')
mpv_dep   = dependency('mpv')
curl_dep  = dependency('libcurl', fallback : ['curl', 'curl_dep'])

sources = run_command('find', 'src', '-name', '*.cpp', check: true).stdout().strip().split('\n')
inc = include_directories('includes')

executable('playon',
  sources,
  include_directories : inc,
  dependencies : [gtkmm_dep, mpv_dep, curl_dep, rapidjson_dep],
  install : true
)