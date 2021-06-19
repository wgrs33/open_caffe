set(APP_NAME ${CMAKE_PROJECT_NAME}_headless)

set(apps_inc_dirs "")
set(apps_link_libs "")

find_package(Threads REQUIRED)

set(apps_link_libs
    ${apps_link_libs}
    Threads::Threads
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_AUTOMOC ON)

set(apps_inc_dirs
        ${apps_inc_dirs}
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(apps_link_libs
        ${apps_link_libs}
)

add_executable(${APP_NAME}
    terminal_control.cpp
    # soft/whatever_is_here_and_in_subdirs.cpp
)

target_link_libraries(${APP_NAME} PRIVATE
    ${apps_link_libs}
    # OpenCaffeSDK::core
)

target_include_directories(${APP_NAME} PRIVATE 
    ${apps_inc_dirs}
)

# if(USE_XXX)
#     target_compile_definitions(${APP_NAME} PRIVATE USE_XXX)
# endif(USE_XXX)

install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION bin
)