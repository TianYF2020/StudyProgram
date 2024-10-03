
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was reflectcpp-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(REFLECTCPP_BSON OFF)
set(REFLECTCPP_FLEXBUFFERS OFF)
set(REFLECTCPP_TOML OFF)
set(REFLECTCPP_XML OFF)
set(REFLECTCPP_YAML OFF)
set(REFLECTCPP_USE_BUNDLED_DEPENDENCIES ON)

if(REFLECTCPP_BSON OR REFLECTCPP_FLEXBUFFERS OR REFLECTCPP_XML OR REFLECTCPP_YAML OR NOT REFLECTCPP_USE_BUNDLED_DEPENDENCIES)
  include(CMakeFindDependencyMacro)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/reflectcpp-exports.cmake)

if (NOT REFLECTCPP_USE_BUNDLED_DEPENDENCIES)
  find_dependency(ctre)
  find_dependency(yyjson)  
endif()

if (REFLECTCPP_BSON)  
  find_dependency(bson-1.0)
endif ()

if (REFLECTCPP_FLEXBUFFERS)
  find_dependency(flatbuffers)
endif ()

if (REFLECTCPP_TOML)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(tomlplusplus REQUIRED IMPORTED_TARGET tomlplusplus)
endif()

if (REFLECTCPP_XML)
  find_dependency(pugixml)
endif ()

if (REFLECTCPP_YAML)
  find_dependency(yaml-cpp)
endif ()

check_required_components(reflectcpp)
