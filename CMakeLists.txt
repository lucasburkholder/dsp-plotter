# cmake_minimum_required(VERSION 3.15...3.31)

# project(DSPPlotter  VERSION 1.0
#                         DESCRIPTION "DSP Plotter"
#                         LANGUAGES C CXX)

include(CMakePrintHelpers)

add_compile_definitions(DSPPLOTTER_BASE_DIR="${CMAKE_CURRENT_LIST_DIR}")

add_library(dsp-plotter STATIC  src/main.cpp
                                src/app.cpp
                                libs/tinywav/tinywav.c
                                libs/implot/implot.cpp
                                libs/implot/implot_items.cpp
                                libs/imgui/imgui_demo.cpp
                                libs/imgui/imgui_draw.cpp
                                libs/imgui/imgui_tables.cpp
                                libs/imgui/imgui_widgets.cpp
                                libs/imgui/imgui.cpp
                                libs/imgui/backends/imgui_impl_opengl3.cpp
                                libs/imgui/backends/imgui_impl_glfw.cpp)

target_include_directories(dsp-plotter  PRIVATE src 
                                                libs
                                                libs/tinywav
                                                libs/implot
                                                libs/imgui 
                                                libs/json
                                                libs/imgui/backends)
target_include_directories(dsp-plotter  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)                                                

target_compile_options(dsp-plotter PRIVATE -g)
target_link_libraries(dsp-plotter PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/glfw/bin/libglfw3.a opengl32)