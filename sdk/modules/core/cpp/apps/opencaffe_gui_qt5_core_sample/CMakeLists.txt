set(app opencaffe_gui_qt5_core_sample)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick SerialPort REQUIRED)
find_package(Threads REQUIRED)

set(common_libraries
    OpenCaffeSDK::core
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
    qt_add_executable(${app}
                      ${apps_src_files}
    )
else()
    add_executable(${app}
                   ${apps_src_files}
    )
endif()

target_link_libraries(${app} PRIVATE ${common_libraries})

target_compile_definitions(${app} PRIVATE 
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

install(
    TARGETS ${app}
    RUNTIME DESTINATION bin
    COMPONENT opencaffe-sdk-core-bin
)