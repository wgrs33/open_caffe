set(APP_NAME ${CMAKE_PROJECT_NAME}_headless)

set(apps_inc_dirs "")
set(apps_link_libs "")

set(CMAKE_PREFIX_PATH 
        ${CMAKE_PREFIX_PATH}
        ${GENERATE_FILES_DIRECTORY}/lib
)

find_package(Threads REQUIRED)
find_library(OpenCaffeCore open_caffe_core)

set(apps_link_libs
    ${apps_link_libs}
    Threads::Threads
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

set(apps_inc_dirs
        ${apps_inc_dirs}
        ${GENERATE_FILES_DIRECTORY}/include
)

set(apps_link_libs
        ${apps_link_libs}
)

add_executable(${APP_NAME}
    headless.cpp
    # soft/whatever_is_here_and_in_subdirs.cpp
)

target_link_libraries(${APP_NAME} PRIVATE
    ${apps_link_libs}
    "${OpenCaffeCore}"
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