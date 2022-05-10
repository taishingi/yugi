cmake_minimum_required(VERSION 3.21)
project(yugi C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -ansi -pedantic)
macro(add_lib name)
  add_library(${name} sources/${name}.c headers/${name}.h)
  install(FILES headers/${name}.h DESTINATION include)
  install(TARGETS ${name} DESTINATION lib)
endmacro()

add_lib(colors)
add_lib(unit)
add_lib(installer)

install(PROGRAMS oh DESTINATION bin)

