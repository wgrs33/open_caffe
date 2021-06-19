set(APP_NAME ${CMAKE_PROJECT_NAME}_gui_qt5)

set(apps_inc_dirs "")
set(apps_link_libs "")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/sdk/core/include)

set(apps_inc_dirs
        ${apps_inc_dirs}
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(apps_link_libs
      ${apps_link_libs}
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Quick
      Qt${QT_VERSION_MAJOR}::SerialPort
      Threads::Threads
)

set(apps_src_files
        sdk_gui/ttext.cpp
        # sdk_gui/ttext.h
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${APP_NAME}
                      ${apps_src_files}
    )
else()
    add_executable(${APP_NAME}
                   ${apps_src_files}
    )
endif()

target_link_libraries(${APP_NAME} PRIVATE
    ${apps_link_libs}
    # OpenCaffeSDK::core
)

target_include_directories(${APP_NAME} PRIVATE 
    ${apps_inc_dirs}
    # ${PROJECT_INC_DIRS}
)

target_compile_definitions(${APP_NAME} PRIVATE 
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

# if(USE_XXX)
#     target_compile_definitions(${APP_NAME} PRIVATE USE_XXX)
# endif(USE_XXX)

install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION bin
)