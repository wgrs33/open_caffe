add_library(${CMAKE_PROJECT_NAME}_core SHARED)
set_target_properties(${CMAKE_PROJECT_NAME}_core
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        EXPORT_NAME Core
)

target_include_directories(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>  # <prefix>/include
)

target_link_libraries(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        ${EXTRA_LINK_LIBS}
)

install(TARGETS ${CMAKE_PROJECT_NAME}_core
    LIBRARY DESTINATION lib
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_core 
    POST_BUILD
        COMMAND cp -r 
            ${CMAKE_CURRENT_SOURCE_DIR}/include 
            ${GENERATE_FILES_DIRECTORY}/include
)

# install(EXPORT OpenCaffeSDK DESTINATION ${GENERATE_FILES_DIRECTORY}/lib
#         NAMESPACE OpenCaffeSDK::
        # INCLUDES DESTINATION ${GENERATE_FILES_DIRECTORY}/include
# )

add_subdirectory(src)