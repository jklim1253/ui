cmake_minimum_required(VERSION 3.10)
project(control VERSION 0.1)

set(FILE_SOURCES
  "colorbutton.cpp"
)
set(FILE_HEADERS
  "colorbutton.hpp"
)

add_compile_options(-DCONTROL_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)
target_link_libraries(${PROJECT_NAME} util)