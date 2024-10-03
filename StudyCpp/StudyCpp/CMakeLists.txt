set(STUDYCPP_SRC_DIR ${CMAKE_SOURCE_DIR}/StudyCpp/src)
set(STUDYCPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/StudyCpp/include)
set(STUDYCPP_LIB_DIR ${CMAKE_SOURCE_DIR}/StudyCpp/lib)
set(STUDYCPP_UI_DIR ${CMAKE_SOURCE_DIR}/StudyCpp/ui)
set(STUDYCPP_QRC_DIR ${CMAKE_SOURCE_DIR}/StudyCpp/source)


# set(Qt6_DIR "D:/qt/6.8.0/msvc2022_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "D:/qt/6.8.0/msvc2022")
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)


# Qt特有的编译器需要打开，默认是关闭的
set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

set(CMAKE_AUTOUIC_SEARCH_PATHS "${STUDYCPP_UI_DIR}")

# 头文件目录
# include_directories(${STUDYCPP_INCLUDE_DIR} ${STUDYCPP_INCLUDE_DIR}/function)

# 添加源文件    #qt 的文件也要夹进来防止无法找到moc文件
file(GLOB_RECURSE STUDYCPP_SRC_FILES
    "${STUDYCPP_SRC_DIR}/*.cpp"
    "${STUDYCPP_SRC_DIR}/function/*.cpp"
    "${STUDYCPP_INCLUDE_DIR}/*.h"           
    "${STUDYCPP_INCLUDE_DIR}/function/*.h"
)
# message( "Compile ****  ${STUDYCPP_SRC_FILES}")

#只能指定单个目录建议只用上面
# aux_source_directory(./src ./ SRC_LIST)


set(CMAKE_INCLUDE_CURRENT_DIR ON)


#适合ui文件
file(GLOB UI_FILES "${STUDYCPP_UI_DIR}/StudyC.ui")
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# # 集成源码以及资源并打包是,适合qml
# qt6_add_resources(QML_QRC  "${STUDYCPP_UI_DIR}/*.qrc")
# # #Qt 6 中用于将 QML 模块添加到 CMake 项目中的一个命令。它简化了 QML 文件的集成，
# # #使得 QML 文件可以像 C++ 文件一样被管理和构建。
# qt_add_qml_module(${PROJECT_NAME} 
#     URI CMakeQml
#     VERSION 1.0
#     QML_FILES
#         ${STUDYCPP_QRC_DIR}/Main.qml
# )

# 将 Qt 资源文件添加进构建
file(GLOB QRC_FILES "${STUDYCPP_QRC_DIR}/StudyC.qrc")
qt6_add_resources(QRC_SOURCES ${QRC_FILES})

## ********** 添加第三方库 ，也可以使用 这里主要是动态库
set(LIBRARIES
jsoncpp     "${STUDYCPP_LIB_DIR}/jsoncpp"
# reflectcpp  "${STUDYCPP_LIB_DIR}/reflectcpp/lib"
)

message("using extren library")
# 库名称和路径列表
list(LENGTH  LIBRARIES LIBRARY_COUNT)
set(INDEX 0)


# 开始循环，按每次两步获取库名和路径
while(${INDEX} LESS ${LIBRARY_COUNT})
    # 获取当前的库名和库路径
    list(GET LIBRARIES ${INDEX} LIB_NAME)
    math(EXPR NEXT_INDEX "${INDEX} + 1")  # 计算下一个索引
    list(GET LIBRARIES ${NEXT_INDEX} LIB_PATH)
    # 打印信息（可选）
    
    # 添加动态库
    add_library(${LIB_NAME} SHARED IMPORTED)
    # 设置动态库和导入库路径
    set_target_properties(${LIB_NAME} PROPERTIES
        IMPORTED_LOCATION "${LIB_PATH}/${LIB_NAME}.dll"   # 动态库 (.dll)
        IMPORTED_IMPLIB "${LIB_PATH}/${LIB_NAME}.lib"     # 导入库 (.lib)
    )
    message(STATUS "Library: ${LIB_PATH}/${LIB_NAME}.lib")
    # 将库添加到链接列表
    list(APPEND LINK_LIBS ${LIB_NAME})

    # 增加索引，步进2（库名和库路径各占一个索引）
    math(EXPR INDEX "${INDEX} + 2")
endwhile()


#库的搜索路径
link_directories(
${STUDYCPP_LIB_DIR}/reflectcpp/lib
)

add_executable(${PROJECT_NAME} main.cpp  ${STUDYCPP_SRC_FILES} ${UI_HEADERS} ${QRC_SOURCES})


message( "${STUDYCPP_SRC_FILES}\n ${UI_HEADERS}\n ${QRC_SOURCES}")

message("${STUDYCPP_LIB_DIR}/reflectcpp/lib")
# 链接Qt库和依赖库  ****可以在这边把库路径加进来，然后直接target_link_libraries 使用
target_include_directories(${PROJECT_NAME}  PRIVATE
${STUDYCPP_INCLUDE_DIR}
${STUDYCPP_INCLUDE_DIR}/function
${STUDYCPP_LIB_DIR}/jsoncpp/include 
${STUDYCPP_LIB_DIR}/magic_enum/include
${STUDYCPP_LIB_DIR}/reflectcpp/include
${STUDYCPP_LIB_DIR}/nlohmann/include/include
)

message("**********${LINK_LIBS}************")
# 链接Qt库和依赖库
target_link_libraries(${PROJECT_NAME} PRIVATE 
Qt6::Core 
Qt6::Widgets 
Qt6::Gui 
reflectcpp
${LINK_LIBS})
