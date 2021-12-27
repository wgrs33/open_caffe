# Override built-in add_library so that we can call it without sources, and add sources with method target_sources()
if(${CMAKE_VERSION} VERSION_LESS "3.11.0")

    set(dummy_header "${GENERATE_FILES_DIRECTORY}/dummy_header.h")
    file(WRITE "${dummy_header}" "")

    function(add_library)
        cmake_parse_arguments(LIB_ARGS "IMPORTED;ALIAS;INTERFACE" "" "" ${ARGN})
        if(LIB_ARGS_IMPORTED OR LIB_ARGS_ALIAS OR LIB_ARGS_INTERFACE)
            # No need to add sources : just redirect call to built-in add_library method
            _add_library(${ARGN})
        else()
            # In this case, if the sources are not provided we need to add them. To make the
            # code clearer to read, we add the dummy header in any case (even if it's needed
            # only when the call to add_library is done without any source file) : it doesn't hurt
            # and if you forget to add sources to the library (via target_sources), you'll be warned
            # by cmake, which will throw the following error :
            #
            #    CMake Error: CMake can not determine linker language for target: LIBNAME
            #
            _add_library(${ARGN} ${dummy_header})
        endif(LIB_ARGS_IMPORTED OR LIB_ARGS_ALIAS OR LIB_ARGS_INTERFACE)
    endfunction(add_library)

endif(${CMAKE_VERSION} VERSION_LESS "3.11.0")