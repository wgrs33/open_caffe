include(CMakeParseArguments)

# Function to add gtest executable to ctest
#
# Parameters
#   TEST                       - Name of the test to add
#   TARGET                     - Target to associate with the test
#
# Usage:
#   add_gtest(TEST base-unit-tests TARGET gtest_base)
function(add_gtest)
    cmake_parse_arguments(PARSED_ARGS "" "TEST;TARGET" "" ${ARGN})

    # Check validity of input args
    foreach(mandatory_arg TEST TARGET)
        if(NOT PARSED_ARGS_${mandatory_arg})
            message(SEND_ERROR "Error when calling function register_gtest : missing mandatory argument ${mandatory_arg} : ${PARSED_ARGS_${mandatory_arg}}")
            return()
        endif(NOT PARSED_ARGS_${mandatory_arg})
    endforeach(mandatory_arg)

    add_test(
        NAME ${PARSED_ARGS_TEST}
        COMMAND $<TARGET_FILE:${PARSED_ARGS_TARGET}> --gtest_color=yes --gtest_output=xml:${GTEST_XML_OUTPUT_DIRECTORY}/${PARSED_ARGS_TEST}.xml
    )
endfunction(add_gtest)
