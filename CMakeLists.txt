cmake_minimum_required(VERSION 3.10)
project(RaylibLavaExample LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RAYLIB_PATH "C:/libs/raylib-5.5_win64_msvc16")

include_directories(${RAYLIB_PATH}/include)

link_directories(${RAYLIB_PATH}/lib)

add_executable(LavaGame main.cpp game.cpp lava.cpp)


target_link_libraries(LavaGame PRIVATE raylib winmm)


file(COPY assets/lava.fs assets/lava.vs DESTINATION ${CMAKE_BINARY_DIR}/assets)
