cmake_minimum_required(VERSION 3.10)

project(open_caffe
        VERSION 0.1
        DESCRIPTION "OpenCaffe SDK"
        LANGUAGES CXX
)

option(GUI_QT5 "GUI based on QT5" ON)
option(HEADLESS "Headless version" OFF)

set(GENERATE_FILES_DIRECTORY ${PROJECT_BINARY_DIR}/generated)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/lib CACHE PATH "Output directory of libraries.")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/lib CACHE PATH "Output directory of all archived executables.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GENERATE_FILES_DIRECTORY}/bin CACHE PATH "Output directory of all executables.")

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the build type: Release, Debug, RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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