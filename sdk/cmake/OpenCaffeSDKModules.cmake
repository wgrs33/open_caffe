# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
# on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and limitations under the License.

# Create package

# Init variables
set(OpenCaffeSDK_CMAKE_OUTPUT_DIR "${GENERATE_FILES_DIRECTORY}/share/cmake/OpenCaffeSDKCMakePackagesFilesDir")
set(OpenCaffeSDK_CMAKE_FILES_INSTALL_PATH_RELATIVE share/cmake/OpenCaffeSDK)
set(OpenCaffeSDK_MODULES_CMAKE_CONFIG_SUBDIR Modules)
set(OpenCaffeSDK_COMPONENTS_CONFIG_INSTALL_PATH_RELATIVE
    ${OpenCaffeSDK_CMAKE_FILES_INSTALL_PATH_RELATIVE}/${OpenCaffeSDK_MODULES_CMAKE_CONFIG_SUBDIR})

###################################################
# Create a version file
# REMARK : if need version file during compilation, it will be best to create a tmp file and copy it only if different,
# to avoid re-compilation
set(VERSION_BARE_FILE version.h)
set(VERSION_FILE_INSTALLATION_PATH_RELATIVE include/opencaffe/sdk)
set(VERSION_FILE_OUTPUT_PATH ${GENERATE_FILES_DIRECTORY}/${VERSION_FILE_INSTALLATION_PATH_RELATIVE}/${VERSION_BARE_FILE})
add_library_version_header(generate_opencaffe_sdk_version_header
                           ${VERSION_FILE_OUTPUT_PATH}
                           opencaffe_sdk
)

###################################################
# Create Configuration file for the cmake package OpenCaffeSDK, that handles the components
include(CMakePackageConfigHelpers)

set(VERSION_FILE_INSTALLATION_PATH_RELATIVE include/opencaffe/sdk)
set(OpenCaffeSDK_config_file_to_install "${OpenCaffeSDK_CMAKE_OUTPUT_DIR}/OpenCaffeSDKConfig.cmake")
configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/OpenCaffeSDKConfig.cmake.in"
    "${OpenCaffeSDK_config_file_to_install}"
    INSTALL_DESTINATION ${OpenCaffeSDK_CMAKE_FILES_INSTALL_PATH_RELATIVE}
)
set(OpenCaffeSDK_config_version_file_to_install "${OpenCaffeSDK_CMAKE_OUTPUT_DIR}/OpenCaffeSDKConfigVersion.cmake")
write_basic_package_version_file(
    "${OpenCaffeSDK_config_version_file_to_install}"
    COMPATIBILITY ExactVersion
)

install (FILES ${VERSION_FILE_OUTPUT_PATH}
         DESTINATION ${VERSION_FILE_INSTALLATION_PATH_RELATIVE}
         COMPONENT opencaffe-sdk-base-dev
         )

install(FILES "${OpenCaffeSDK_config_file_to_install}"
        DESTINATION ${OpenCaffeSDK_CMAKE_FILES_INSTALL_PATH_RELATIVE}
        COMPONENT opencaffe-sdk-base-dev
)

install(FILES "${OpenCaffeSDK_config_version_file_to_install}"
        DESTINATION ${OpenCaffeSDK_CMAKE_FILES_INSTALL_PATH_RELATIVE}
        COMPONENT opencaffe-sdk-base-dev
)

#####################################################################
#
# Creates OpenCaffe SDK module library, installs it and adds a cmake component for package OpenCaffeSDK
#
#
# usage :
#     OpenCaffeSDK_add_module(<module-name>
#          [INTERFACE | SOURCES srcs...]
#          [[REQUIRED_OPENCAFFE_SDK_MODULES
#               <PRIVATE|PUBLIC|INTERFACE> <components>...
#               [<PRIVATE|PUBLIC|INTERFACE> <components>...]
#          ]]
#          [EXTRA_REQUIRED_PACKAGE packages...]
#      )
#
#
#  Creates and installs a library named opencaffe_sdk_<module-name> . This library's public headers need to be in a
#  folder "include" at sdk/modules/<module-name>. This function handles the right cpack components (i.e.
#  opencaffe-sdk-<module-name> for runtime and opencaffe-sdk-<module-name>-dev for development). Moreover, it creates
#  (and installs) the files needed to create a <module-name> module of the OpenCaffeSDK package. Finally, an alias
#  library OpenCaffeSDK::<module-name> will also be created
#
#  REMARK : given the above description, note that folder sdk/modules/<module-name>/include has to exist
#
#  The INTERFACE is to be used if the library opencaffe_sdk_<module-name> is to be a INTERFACE library. It will be
#  a SHARED one otherwise. In this second case, you may use the option SOURCES to specify the library sources. However,
#  this is not mandatory, as sources may be specified with target_sources() after the call to this function.
#
#  The export set where the library opencaffe_sdk_<module-name> is exported will be named
#  opencaffe_sdk_<module-name>Targets. This means that if you want to add other targets to the set, you'll have to use
#  this name, as it is the one installed in this function.
#
#  The REQUIRED_OPENCAFFE_SDK_MODULES defines a list of other OpenCaffeSDK components on which the current one
#  depends on. If this option is provided :
#     -> a call to target_link_libraries(opencaffe_sdk_<module-name> <PRIVATE|PUBLIC|INTERFACE> ..) will be done
#        (note that if opencaffe_sdk_<module-name> is an interface library, only the INTERFACE keyword is allowed)
#     -> for INTERFACE and PUBLIC, an additional file OpenCaffeSDK_<module-name>Depends.cmake will be created. This
#        file is used by the OpenCaffeSDK find package to determine inter-dependencies between the different cmake
#        components
#
#  The EXTRA_REQUIRED_PACKAGE defines a list of other packages the module depends on. If you need only some components
#  of these packages, you need to provide them as a full string. For example "Boost COMPONENTS filesystem" if the
#  module only needs the filesystem component of Boost. The list provided with this option is used to create the
#  configuration file OpenCaffeSDK_<module-name>Config.cmake, used when looking for package OpenCaffeSDK.
#  REMARK : please note that when using this option, you'll still need to call
#                     target_link_libraries(opencaffe_sdk_<module-name> ...)
#           with the target the package defines.
#
#
#  Example :
#
#  OpenCaffeSDK_add_module(ui
#      REQUIRED_OPENCAFFE_SDK_MODULES
#          PUBLIC core
#          PRIVATE base
#      EXTRA_REQUIRED_PACKAGE "Boost COMPONENTS system filesystem"
#      EXTRA_REQUIRED_PACKAGE OpenCV
#  )
#
include(CMakeParseArguments)
function(OpenCaffeSDK_add_module module_name)
    set(multiValueArgs SOURCES EXTRA_REQUIRED_PACKAGE REQUIRED_OPENCAFFE_SDK_MODULES VARIABLE_TO_SET)
    cmake_parse_arguments(PARSED_ARGS "INTERFACE_LIBRARY" "" "${multiValueArgs}" ${ARGN})

    # Check validity of input args
    if(PARSED_ARGS_SOURCES AND PARSED_ARGS_INTERFACE_LIBRARY)
        message(SEND_ERROR
        "Error when calling function OpenCaffeSDK_add_module : incompatible input arguments INTERFACE_LIBRARY and SOURCES")
        return()
    endif(PARSED_ARGS_SOURCES AND PARSED_ARGS_INTERFACE_LIBRARY)

    set (module_include_folder_path ${PROJECT_SOURCE_DIR}/sdk/modules/${module_name}/include)
    if (NOT IS_DIRECTORY "${module_include_folder_path}")
        set (module_include_folder_path ${PROJECT_SOURCE_DIR}/sdk/modules/${module_name}/cpp/include)
        if( NOT IS_DIRECTORY "${module_include_folder_path}")
            message(SEND_ERROR
                    "Error in OpenCaffeSDK_add_module : folder ${module_include_folder_path} does not exist")
            return()
        endif  (NOT IS_DIRECTORY "${module_include_folder_path}")
    endif (NOT IS_DIRECTORY "${module_include_folder_path}")


    # Create library:
    set(public_keywork_to_use PUBLIC)
    if(PARSED_ARGS_INTERFACE_LIBRARY)
        add_library(opencaffe_sdk_${module_name} INTERFACE)
        set(public_keywork_to_use INTERFACE)
    else()
        add_library(opencaffe_sdk_${module_name} SHARED ${PARSED_ARGS_SOURCES})
        set_target_properties(opencaffe_sdk_${module_name}
            PROPERTIES
                VERSION ${PROJECT_VERSION_FULL}
                SOVERSION ${PROJECT_VERSION_MAJOR}
        )
    endif(PARSED_ARGS_INTERFACE_LIBRARY)

    # Create library alias:
    add_library(OpenCaffeSDK::${module_name} ALIAS opencaffe_sdk_${module_name})

    # Set export name of the built target, so that we can refer to it with OpenCaffeSDK::${module_name}, thanks
    # to the fact that we export the target set with the NAMESPACE OpenCaffeSDK:: (see below when installing export)
    set_target_properties(opencaffe_sdk_${module_name} PROPERTIES EXPORT_NAME ${module_name})

    target_include_directories(opencaffe_sdk_${module_name}
        ${public_keywork_to_use}
            $<BUILD_INTERFACE:${module_include_folder_path}>
            $<INSTALL_INTERFACE:include>
    )

    set(internal_include_dir "${PROJECT_SOURCE_DIR}/sdk/modules/${module_name}/cpp/src/include")
    if(NOT PARSED_ARGS_INTERFACE_LIBRARY)
        if(IS_DIRECTORY "${internal_include_dir}")
            target_include_directories(opencaffe_sdk_${module_name}
                PRIVATE
                    $<BUILD_INTERFACE:${internal_include_dir}>
            )
        endif(IS_DIRECTORY "${internal_include_dir}")
    endif(NOT PARSED_ARGS_INTERFACE_LIBRARY)

    set(needed_opencaffe_sdk_cmake_components)
    if (PARSED_ARGS_REQUIRED_OPENCAFFE_SDK_MODULES)
        cmake_parse_arguments(SDK_NEEDED_MODULES "" "" "PUBLIC;INTERFACE;PRIVATE" ${PARSED_ARGS_REQUIRED_OPENCAFFE_SDK_MODULES})
        foreach(mod IN LISTS SDK_NEEDED_MODULES_PUBLIC)
            target_link_libraries(opencaffe_sdk_${module_name}
                PUBLIC OpenCaffeSDK::${mod}
            )
            list(APPEND needed_opencaffe_sdk_cmake_components ${mod})
        endforeach(mod)

        foreach(mod IN LISTS SDK_NEEDED_MODULES_INTERFACE)
            target_link_libraries(opencaffe_sdk_${module_name}
                INTERFACE OpenCaffeSDK::${mod}
            )
            list(APPEND needed_opencaffe_sdk_cmake_components ${mod})
        endforeach(mod)

        foreach(mod IN LISTS SDK_NEEDED_MODULES_PRIVATE)
            target_link_libraries(opencaffe_sdk_${module_name}
                PRIVATE OpenCaffeSDK::${mod}
            )
        endforeach(mod)
    endif (PARSED_ARGS_REQUIRED_OPENCAFFE_SDK_MODULES)


    # Install target :
    set(COMPONENT_NAME_PREFIX "opencaffe-sdk-${module_name}")
    string(REPLACE "_" "-" COMPONENT_NAME_PREFIX "${COMPONENT_NAME_PREFIX}")
    if(PARSED_ARGS_INTERFACE_LIBRARY)
        install(TARGETS opencaffe_sdk_${module_name}
                EXPORT opencaffe_sdk_${module_name}Targets
        )
    else()
        install(TARGETS opencaffe_sdk_${module_name}
            EXPORT opencaffe_sdk_${module_name}Targets
            RUNTIME
                DESTINATION ${RUNTIME_INSTALL_DEST}
                COMPONENT ${COMPONENT_NAME_PREFIX}-lib
            ARCHIVE
                DESTINATION ${ARCHIVE_INSTALL_DEST}
                COMPONENT ${COMPONENT_NAME_PREFIX}-lib
            LIBRARY
                DESTINATION ${LIBRARY_INSTALL_DEST}
                COMPONENT ${COMPONENT_NAME_PREFIX}-lib
                NAMELINK_SKIP
            )

        install(TARGETS opencaffe_sdk_${module_name}
                EXPORT opencaffe_sdk_${module_name}Targets
                LIBRARY
                    DESTINATION ${LIBRARY_INSTALL_DEST}
                    COMPONENT ${COMPONENT_NAME_PREFIX}-dev
                    NAMELINK_ONLY
            )
    endif(PARSED_ARGS_INTERFACE_LIBRARY)

    # Install public headers
    install(DIRECTORY ${module_include_folder_path}/
            DESTINATION ${HEADER_INSTALL_DEST}
            COMPONENT ${COMPONENT_NAME_PREFIX}-dev
            )

    # Create the configuration file
    set(config_file_text "")
    set(config_file_text "${config_file_text}if (ANDROID)\n")
    set(config_file_text "${config_file_text}    include(\${CMAKE_CURRENT_LIST_DIR}/../../android/env.cmake)\n")
    set(config_file_text "${config_file_text}endif (ANDROID)\n\n")

    foreach(variable_to_set ${PARSED_ARGS_VARIABLE_TO_SET})
        set(config_file_text "${config_file_text}set(${variable_to_set})\n")
    endforeach(variable_to_set)

    foreach(extra_package ${PARSED_ARGS_EXTRA_REQUIRED_PACKAGE})
        set(config_file_text "${config_file_text}find_package(${extra_package} REQUIRED QUIET)\n")
    endforeach(extra_package)

    set(config_file_text "${config_file_text}\nif(NOT TARGET OpenCaffeSDK::${module_name})")
    set(config_file_text
        "${config_file_text}\n    include(\"\${CMAKE_CURRENT_LIST_DIR}/OpenCaffeSDK_${module_name}Targets.cmake\")")
    set(config_file_text "${config_file_text}\nendif(NOT TARGET OpenCaffeSDK::${module_name})")

    # Write the config file
    set(input_conf_path "${OpenCaffeSDK_CMAKE_OUTPUT_DIR}/OpenCaffeSDK_${module_name}Config.cmake.in")
    file(WRITE ${input_conf_path} "${config_file_text}")


    # Get installation path
    set(MVPackageModule_CMAKE_FILES_INSTALLATION_PATH_RELATIVE
        "${OpenCaffeSDK_COMPONENTS_CONFIG_INSTALL_PATH_RELATIVE}/${module_name}")
    set(MVPackageModule_CMAKE_PACKAGE_OUTPUT_FILES_DIR
        "${OpenCaffeSDK_CMAKE_OUTPUT_DIR}/${OpenCaffeSDK_MODULES_CMAKE_CONFIG_SUBDIR}/${module_name}")
    include(CMakePackageConfigHelpers)

    set(files_to_install "")
    set(output_config_file_path
        "${MVPackageModule_CMAKE_PACKAGE_OUTPUT_FILES_DIR}/OpenCaffeSDK_${module_name}Config.cmake")
    configure_package_config_file(
       "${input_conf_path}"
        "${output_config_file_path}"
        INSTALL_DESTINATION ${MVPackageModule_CMAKE_FILES_INSTALLATION_PATH_RELATIVE}
    )
    list(APPEND files_to_install "${output_config_file_path}")

    set(output_config_version_file_path
        "${MVPackageModule_CMAKE_PACKAGE_OUTPUT_FILES_DIR}/OpenCaffeSDK_${module_name}ConfigVersion.cmake")
    write_basic_package_version_file(
        "${output_config_version_file_path}"
        COMPATIBILITY ExactVersion
    )
    list(APPEND files_to_install "${output_config_version_file_path}")

    if(needed_opencaffe_sdk_cmake_components)
        # Create a depends file
        set(output_depends_file_path
            "${MVPackageModule_CMAKE_PACKAGE_OUTPUT_FILES_DIR}/OpenCaffeSDK_${module_name}Depends.cmake")
        file(WRITE ${output_depends_file_path}
            "set(OpenCaffeSDK_${module_name}_NEEDED_COMPONENTS ${needed_opencaffe_sdk_cmake_components})")
        list(APPEND files_to_install "${output_depends_file_path}")
    endif()

    export(EXPORT opencaffe_sdk_${module_name}Targets
           FILE "${OpenCaffeSDK_CMAKE_OUTPUT_DIR}/${OpenCaffeSDK_MODULES_CMAKE_CONFIG_SUBDIR}/${module_name}/OpenCaffeSDK_${module_name}Targets.cmake"
           NAMESPACE OpenCaffeSDK::
    )

    install(EXPORT opencaffe_sdk_${module_name}Targets
            FILE OpenCaffeSDK_${module_name}Targets.cmake
            NAMESPACE OpenCaffeSDK::
            DESTINATION ${MVPackageModule_CMAKE_FILES_INSTALLATION_PATH_RELATIVE}
            COMPONENT ${COMPONENT_NAME_PREFIX}-dev
    )


    install(FILES ${files_to_install}
            DESTINATION ${MVPackageModule_CMAKE_FILES_INSTALLATION_PATH_RELATIVE}
            COMPONENT ${COMPONENT_NAME_PREFIX}-dev
    )

endfunction(OpenCaffeSDK_add_module)
