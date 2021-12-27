cmake_minimum_required(VERSION 3.10)

project(open_caffe
        VERSION 0.1.0
        DESCRIPTION "OpenCaffe"
        LANGUAGES CXX
)

set(PROJECT_VERSION_SUFFIX "dev")

if(PROJECT_VERSION_SUFFIX STREQUAL "")
    set(PROJECT_VERSION_FULL "${PROJECT_VERSION}")
else(PROJECT_VERSION_SUFFIX STREQUAL "")
    set(PROJECT_VERSION_FULL "${PROJECT_VERSION}-${PROJECT_VERSION_SUFFIX}")
endif(PROJECT_VERSION_SUFFIX STREQUAL "")

# Set output directory for generated files
set(GENERATE_FILES_DIRECTORY ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATE_FILES_DIRECTORY})
set(HEADER_INSTALL_DEST "include")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/custom_functions)
include(add_library_version_header)
include(list_subdirs)
include(overriden)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/lib CACHE PATH "Output directory of libraries.")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/lib CACHE PATH "Output directory of all archived executables.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/bin CACHE PATH "Output directory of all executables.")

set(LIBRARY_INSTALL_DEST "lib")
set(ARCHIVE_INSTALL_DEST "lib")
set(RUNTIME_INSTALL_DEST "bin")

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the build type: Release, Debug, RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Boost
set (boost_components_to_find program_options filesystem timer chrono thread)
find_package(Boost COMPONENTS ${boost_components_to_find} REQUIRED)

find_package(Doxygen)
    if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(sdk)