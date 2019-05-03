cmake_minimum_required(VERSION 2.8)
project(tower-viewer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE" )

add_subdirectory(resources)

find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM3 REQUIRED gtkmm-3.0)
PKG_CHECK_MODULES(POPPLER REQUIRED poppler-cpp)

INCLUDE_DIRECTORIES(${GTKMM3_INCLUDE_DIRS} ${POPPLER_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKMM3_LIBRARY_DIRS} ${POPPLER_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTKMM3_CFLAGS_OTHER} ${POPPLER_CFLAGS_OTHER})

add_executable(tower-viewer src/main.cpp resources/resources.c src/document/document.h src/document/document.cpp)
set_source_files_properties(resources/resources.c PROPERTIES GENERATED TRUE)
add_dependencies(tower-viewer generate_resources)

TARGET_LINK_LIBRARIES(tower-viewer ${GTKMM3_LIBRARIES} ${POPPLER_LIBRARIES})
