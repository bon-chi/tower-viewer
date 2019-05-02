cmake_minimum_required(VERSION 2.8)
project(tower-viewer)

find_program(GLIB_COMPILE_RESOURCES
        NAMES glib-compile-resources)
add_custom_command(
        OUTPUT resources.c
        COMMAND ${GLIB_COMPILE_RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/tower-viewer.gresource.xml --target=resources.c --sourcedir=${CMAKE_CURRENT_SOURCE_DIR} --generate-source
)

add_custom_target( generate_resources DEPENDS resources.c)
