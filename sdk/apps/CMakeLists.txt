add_subdirectory(pid_controller_test)

if(HEADLESS)
    add_subdirectory(headless)
endif(HEADLESS)

if(GUI_QT5)
    add_subdirectory(gui_qt5)
endif(GUI_QT5)