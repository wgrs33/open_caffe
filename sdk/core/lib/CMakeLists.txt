add_library(${CMAKE_PROJECT_NAME}_core SHARED)
set_target_properties(${CMAKE_PROJECT_NAME}_core
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        EXPORT_NAME Core
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include
    DESTINATION ${GENERATE_FILES_DIRECTORY}/include
)

target_include_directories(${CMAKE_PROJECT_NAME}_core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        # $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
)

target_link_libraries(${CMAKE_PROJECT_NAME}_core
    PUBLIC
        ${EXTRA_LINK_LIBS}
)

install(TARGETS ${CMAKE_PROJECT_NAME}_core
    LIBRARY DESTINATION lib
)