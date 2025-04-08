#include <lua.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Python.h"



// 定义一个 C++ 函数，供 Lua 脚本调用
int call_cpp_function(lua_State* L) {
    // 检查参数数量
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "call_cpp_function expects 2 arguments");
    }

    // 获取参数
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);

    // 执行 C++ 函数逻辑
    std::cout << "C++ function called with arguments: " << a << ", " << b << std::endl;
    int result = a * b;

    // 将结果压入 Lua 栈
    lua_pushinteger(L, result);

    // 返回结果数量
    return 1;
}

int call_py_function_test() {

    Py_Initialize();

    // 执行 Python 脚本
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("import script");
    PyRun_SimpleString("script.main()");

    // 关闭 Python 解释器
    Py_Finalize();
    return 0;

}

int main() {

    call_py_function_test();
    return 0;

    std::setlocale(LC_ALL, "zh_CN.UTF-8"); // 设置终端为 UTF-8

    // 初始化 Lua 环境
    lua_State* L = luaL_newstate();
    if (!L) {
        std::cerr << "Failed to create a new Lua state." << std::endl;
        return 1;
    }

    // 打开 Lua 标准库
    luaopen_base(L);
    luaL_openlibs(L);

    // 注册 C++ 函数到 Lua 环境
    lua_pushcfunction(L, call_cpp_function);
    lua_setglobal(L, "call_cpp_function");

    // 要执行的 Lua 脚本文件
    std::string luaScriptFile = "example.lua";

    // 打开 Lua 脚本文件
    std::ifstream luaFile(luaScriptFile);
    if (!luaFile.is_open()) {
        std::cerr << "Failed to open Lua script file: " << luaScriptFile << std::endl;
        lua_close(L);
        return 1;
    }

    // 读取整个 Lua 脚本内容
    std::string scriptContent((std::istreambuf_iterator<char>(luaFile)), std::istreambuf_iterator<char>());
    luaFile.close();

    // 执行 Lua 脚本
    if (luaL_dostring(L, scriptContent.c_str()) != 0) {
        std::cerr << "Error executing Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // 弹出错误信息
    }
    else {
        std::cout << "Lua script executed successfully." << std::endl;
    }

    // 关闭 Lua 环境
    lua_close(L);
    return 0;
}