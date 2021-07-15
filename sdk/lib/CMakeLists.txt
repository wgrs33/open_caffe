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

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        ${EXTRA_LINK_LIBS}
        nlohmann_json::nlohmann_json
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