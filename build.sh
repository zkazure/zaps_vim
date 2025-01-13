rm -rf build
mkdir build
cd build

cmake DCMAKE_TOOLCHAIN_FILE=../mingw-toolchain.cmake ..

# 构建项目
cmake --build .