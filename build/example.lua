-- 这是一个较长的 Lua 脚本示例
-- Lua 脚本文件

-- 定义一个 Lua 函数
function add(a, b)
    print("Lua function add called with arguments: " .. a .. ", " .. b)
    return a + b
end

-- 调用 C++ 注册的函数
print("Calling C++ function from Lua...")
local result = call_cpp_function(10, 20)
print("Result from C++ function: " .. result)
-- 打印欢迎信息
print("Welcome to the Lua script!")

-- 定义一个函数
function add(a, b)
    return a + b
end

-- 调用函数并打印结果
local result = add(5, 3)
print("The result of add(5, 3) is: " .. result)

-- 创建一个表
local my_table = {
    name = "Kimi",
    age = 25,
    hobbies = {"reading", "coding", "traveling"}
}

-- 遍历表并打印内容
print("My table contains:")
for key, value in pairs(my_table) do
    print(key .. ": " .. tostring(value))
end

-- 定义一个匿名函数
local anonymous_function = function(x)
    return x * x
end

-- 调用匿名函数并打印结果
local squared = anonymous_function(4)
print("The square of 4 is: " .. squared)

-- 使用 Lua 的 I/O 库读取文件
local file = io.open("example.txt", "r")
if file then
    local content = file:read("*all")
    print("Content of example.txt:")
    print(content)
    file:close()
else
    print("example.txt not found.")
end

-- 使用 Lua 的 math 库
local pi = math.pi
print("The value of pi is: " .. pi)

-- 使用 Lua 的 string 库
local str = "Hello, Lua!"
local upper_str = string.upper(str)
print("Uppercase string: " .. upper_str)

-- 使用 Lua 的 table 库
local array = {1, 2, 3, 4, 5}
table.sort(array)
print("Sorted array:")
for i, v in ipairs(array) do
    print(v)
end

-- 使用 Lua 的 coroutine 库
local function co_function()
    for i = 1, 5 do
        coroutine.yield(i)
    end
end

local co = coroutine.create(co_function)
print("Coroutine output:")
while coroutine.status(co) ~= "dead" do
    print(coroutine.resume(co))
end

-- 使用 Lua 的 os 库
local current_time = os.time()
print("Current time: " .. os.date("%c", current_time))

-- 使用 Lua 的 debug 库
local function debug_function()
    debug.debug()
end

-- 调试函数
print("Enter debug mode:")
debug_function()