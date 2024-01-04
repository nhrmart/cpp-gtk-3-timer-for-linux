cmake_minimum_required(VERSION 3.16)

project(Timer VERSION 1.0.0)

set(CMAKE_CXX_COMPILER g++-12)
set(CMAKE_CXX_STANDARD 23)

set(SOURCES
  includes/globals.cpp
  includes/utils.cpp
  includes/timer-funcs.cpp
  includes/event-listeners.cpp
  includes/activate.cpp
  includes/create-app.cpp
  main.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}
  /usr/include/gtk-3.0
  /usr/include/gtk-3.0/gdk
  /usr/include/glib-2.0
  /usr/lib/x86_64-linux-gnu/glib-2.0/include
  /usr/include/pango-1.0
  /usr/include/harfbuzz
  /usr/include/cairo
  /usr/include/atk-1.0
  /usr/include/gdk-pixbuf-2.0
  /usr/include/graphene-1.0
  /usr/lib/x86_64-linux-gnu/graphene-1.0/include
)

add_executable(timer ${SOURCES})

add_custom_target(
  compile_schemas
  COMMAND glib-compile-schemas ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_dependencies(timer compile_schemas)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
target_link_libraries(timer ${GTK_LIBRARIES})

install(TARGETS timer DESTINATION /usr/local/bin)

install(FILES org.nhrdev.timer.gschema.xml DESTINATION /usr/share/glib-2.0/schemas/)

install(FILES assets/images/icon.png DESTINATION /usr/share/icons/hicolor/48x48/apps/)