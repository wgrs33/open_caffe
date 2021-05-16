target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
                           ${CMAKE_CURRENT_LIST_DIR}/inc
)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
               ${CMAKE_CURRENT_LIST_DIR}/src/ttext.cpp
               ${CMAKE_CURRENT_LIST_DIR}/inc/ttext.h
)
      