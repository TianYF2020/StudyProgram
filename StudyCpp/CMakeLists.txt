
cmake_minimum_required(VERSION 3.20)

project(StudyCpp VERSION 1.0 LANGUAGES C CXX DESCRIPTION "This is c++ study code")

# if(MSVC)
#     add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
#     message("using MSVC ****************************")
# elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
# endif()

# 有些项目会动态生成头文件，项目中需要引入它，因此需要将output目录也include进来
# 等同于INCLUDE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#强制使用c++ 17以上的标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)  # 64位
    set(ARCH_DIR "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)  # 32位
    set(ARCH_DIR "x86")
else()
    message(FATAL_ERROR "Unsupported architecture.")
endif()
message(" Use ${ARCH_DIR} exe.")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/outlib)

add_subdirectory(StudyCpp)