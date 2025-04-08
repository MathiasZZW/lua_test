cmake_minimum_required(VERSION 3.10)
# Start of Selection
project(lua_test LANGUAGES CXX)
add_compile_options("/utf-8")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/external/packages")

set(LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/packages/lua_x64-windows/include")
set(LUA_LIBRARIES "${CMAKE_SOURCE_DIR}/external/packages/lua_x64-windows/lib/lua.lib")

find_package(Python3 COMPONENTS Development REQUIRED)
# 收集所有源文件
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# 收集所有头文件
file(GLOB_RECURSE HEADER_FILES 
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

# 添加可执行文件，包含所有源文件
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# 添加头文件搜索路径
target_include_directories(${CMAKE_PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
message(PYTHON_LIBRARIES ${PYTHON_LIBRARIES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LUA_LIBRARIES} Python3::Python)# 添加可执行文件
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/external/packages/lua_x64-windows/bin/lua.dll"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
)