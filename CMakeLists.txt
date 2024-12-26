cmake_minimum_required(VERSION 3.15...3.31)

project(LBDSPTestBench  VERSION 1.0
                        DESCRIPTION "LBDSP Audio Test Bench"
                        LANGUAGES C CXX)

add_executable(a    src/main.cpp
                    libs/imgui/imgui_demo.cpp
                    libs/imgui/imgui_draw.cpp
                    libs/imgui/imgui_tables.cpp
                    libs/imgui/imgui_widgets.cpp
                    libs/imgui/imgui.cpp
                    libs/imgui/backends/imgui_impl_opengl3.cpp
                    libs/imgui/backends/imgui_impl_glfw.cpp)

target_include_directories(a PRIVATE    src 
                                        libs 
                                        libs/imgui 
                                        libs/imgui/backends)

target_link_directories(a PRIVATE ${CMAKE_SOURCE_DIR}/libs/GLFW/bin)

target_link_libraries(a PRIVATE glfw3 opengl32)