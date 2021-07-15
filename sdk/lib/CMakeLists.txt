add_library(${CMAKE_PROJECT_NAME}_core SHARED)
add_library(OpenCaffeSDK::Core ALIAS ${CMAKE_PROJECT_NAME}_core)
set_target_properties(${CMAKE_PROJECT_NAME}_core
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        EXPORT_NAME OpenCaffeSDK::Core
)

set(opencaffecore_inc_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        $<BUILD_INTERFACE:${opencaffecore_inc_dirs}>
        # <prefix>/include; check if in install directory there are headers
        $<INSTALL_INTERFACE:include>  
)

target_link_libraries(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        ${EXTRA_LINK_LIBS}
)

install(TARGETS ${CMAKE_PROJECT_NAME}_core
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${opencaffecore_inc_dirs}/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*"
)

# install(EXPORT OpenCaffeSDK DESTINATION ${GENERATE_FILES_DIRECTORY}/lib
#         NAMESPACE OpenCaffeSDK::
        # INCLUDES DESTINATION ${GENERATE_FILES_DIRECTORY}/include
# )

add_subdirectory(src)