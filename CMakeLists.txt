cmake_minimum_required(VERSION 3.10)
project(pixel-vim)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# 获取gcc版本路径
execute_process(
    COMMAND ls /usr/lib/gcc/x86_64-w64-mingw32/
    OUTPUT_VARIABLE GCC_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# MinGW头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    /usr/x86_64-w64-mingw32/include
    /usr/lib/gcc/x86_64-w64-mingw32/${GCC_VERSION}/include
    /usr/lib/gcc/x86_64-w64-mingw32/${GCC_VERSION}/include/c++
    /usr/lib/gcc/x86_64-w64-mingw32/${GCC_VERSION}/include/c++/x86_64-w64-mingw32
    /usr/share/mingw-w64/include
    /usr/share/mingw-w64/include/uiautomation
)

# 添加Windows编译定义
add_definitions(
    -DWIN32
    -D_WINDOWS
    -DWIN32_LEAN_AND_MEAN
    -D_WIN32_WINNT=0x0601
    -DWINVER=0x0601
    -DCOBJMACROS
    -DUNICODE
    -D_UNICODE
)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*/*.cpp"
)

# 创建可执行文件
add_executable(pixel-vim ${SOURCES})

# 链接库
target_link_libraries(pixel-vim
    -luser32
    -lgdi32
    -lole32
    -loleaut32
    -luuid
    -lcomdlg32
    -lcomctl32
    -ladvapi32
    -lshell32
    -lstdc++
    -luiautomationcore
    -lcomsupp
)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 