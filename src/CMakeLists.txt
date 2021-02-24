cmake_minimum_required(VERSION 3.10)

set(FILE_SOURCES
  "app.cpp"
)
set(FILE_HEADERS
)

# for window application, not console
add_link_options("/SUBSYSTEM:WINDOWS")

# using wxWidgets dynamic library
add_compile_options(-DWXUSINGDLL)

add_executable(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)