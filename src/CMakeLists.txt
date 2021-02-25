cmake_minimum_required(VERSION 3.10)

set(FILE_SOURCES
  "app.cpp"
)
set(FILE_HEADERS
)
set(FILE_RESOURCES
  "app.rc"
)

# for window application, not console
add_link_options("/SUBSYSTEM:WINDOWS")

# using wxWidgets dynamic library
add_compile_options(-DWXUSINGDLL)

add_subdirectory(util)
add_subdirectory(control)

add_executable(${CMAKE_PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
  ${FILE_RESOURCES}
)
target_link_libraries(${CMAKE_PROJECT_NAME} util)
target_link_libraries(${CMAKE_PROJECT_NAME} control)