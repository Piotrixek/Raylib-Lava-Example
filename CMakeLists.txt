cmake_minimum_required(VERSION 3.10)
project(RaylibLavaExample LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RAYLIB_PATH "C:/libs/raylib-5.5_win64_msvc16")
set(IMGUI_PATH "C:/libs/imgui-docking")


include_directories(${RAYLIB_PATH}/include)
include_directories(${IMGUI_PATH})

link_directories(${RAYLIB_PATH}/lib)

add_executable(LavaGame 
    main.cpp 
    game.cpp 
    UIManager.cpp
    lava.cpp
    rlImGui.cpp
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
)

target_link_libraries(LavaGame PRIVATE raylib winmm)

# file(COPY assets/lava.fs assets/lava.vs DESTINATION ${CMAKE_BINARY_DIR}/assets)