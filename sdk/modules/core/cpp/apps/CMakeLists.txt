option(GUI_QT5 "GUI based sample on QT5" OFF)

add_subdirectory(opencaffe_pid_controller_sample)
add_subdirectory(opencaffe_headless_core_sample)

if(GUI_QT5)
    add_subdirectory(opencaffe_gui_qt5_core_sample)
endif(GUI_QT5)