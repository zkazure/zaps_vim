cmake_minimum_required(VERSION 3.10)
project(pixel-vim)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 检查操作系统
if(WIN32)
    # Windows特定设置
    if(DEFINED ENV{WindowsSdkDir})
        set(WINDOWS_SDK_PATH $ENV{WindowsSdkDir})
    else()
        set(WINDOWS_SDK_PATH "C:/Program Files (x86)/Windows Kits/10")
    endif()
    
    # 查找最新的SDK版本
    file(GLOB SDK_VERSIONS LIST_DIRECTORIES true "${WINDOWS_SDK_PATH}/Include/*")
    list(SORT SDK_VERSIONS ORDER DESCENDING)
    list(GET SDK_VERSIONS 0 LATEST_SDK_VERSION)
    
    message(STATUS "Using Windows SDK at: ${LATEST_SDK_VERSION}")
    
    include_directories(
        ${LATEST_SDK_VERSION}/um
        ${LATEST_SDK_VERSION}/shared
        ${LATEST_SDK_VERSION}/ucrt
    )

    # 添加Windows编译定义
    add_definitions(-DWIN32_LEAN_AND_MEAN -DWIN32 -D_WINDOWS)
else()
    # 非Windows系统，使用Wine开发头文件
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(WINE REQUIRED wine)
    include_directories(${WINE_INCLUDE_DIRS})
    
    # 添加Wine相关定义
    add_definitions(-D_WINE)
endif()

# 添加include目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*/*.cpp"
)

# 创建可执行文件
add_executable(pixel-vim ${SOURCES})

# 平台特定链接
if(WIN32)
    target_link_libraries(pixel-vim
        user32
        gdi32
        ole32
        oleaut32
        uuid
        UIAutomationCore
    )
else()
    target_link_libraries(pixel-vim
        ${WINE_LIBRARIES}
    )
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 