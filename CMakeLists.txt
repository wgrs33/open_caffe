cmake_minimum_required(VERSION 3.14)

project(open_caffe
        VERSION 0.1
        DESCRIPTION "OpenCaffe Application"
        LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# find_package(Doxygen)
#     if(Doxygen_FOUND)
#     add_subdirectory(docs)
# else()
#     message(STATUS "Doxygen not found, not building docs")
# endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Threads REQUIRED)

# include_directories(${CMAKE_SOURCE_DIR}/api/inc)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${CMAKE_PROJECT_NAME}
                      ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${CMAKE_PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${CMAKE_PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_INC_DIRS})
target_compile_definitions(${CMAKE_PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${CMAKE_PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Quick
          Qt${QT_VERSION_MAJOR}::SerialPort
          Threads::Threads
)

add_subdirectory(api)