target_sources(opencaffe_sdk_base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inputdevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/outputdevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/analogdevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterdevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/motordevice.cpp
)