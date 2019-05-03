cmake_minimum_required(VERSION 2.8)
project(tower-viewer)

# compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE" )

# external modules
find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM3 REQUIRED gtkmm-3.0)
PKG_CHECK_MODULES(POPPLER REQUIRED poppler-cpp)

# GKT3
INCLUDE_DIRECTORIES(${GTKMM3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKMM3_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTKMM3_CFLAGS_OTHER})

# src
add_subdirectory(src/document)
TARGET_INCLUDE_DIRECTORIES(document PUBLIC ${POPPLER_INCLUDE_DIRS})

# resources
add_subdirectory(resources)
set_source_files_properties(resources/resources.c PROPERTIES GENERATED TRUE)

# generate executable
add_executable(tower-viewer src/main.cpp resources/resources.c)
add_dependencies(tower-viewer generate_resources)
TARGET_LINK_LIBRARIES(tower-viewer ${GTKMM3_LIBRARIES} document)
