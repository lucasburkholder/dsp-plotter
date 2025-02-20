#ifndef DSP_PLOTTER_CPP
#define DSP_PLOTTER_CPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <string>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "implot.h"
#include "app.h"
#include "dsp-plotter.h"
#include "tinywav/tinywav.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


#ifndef DSPPLOTTER_BASE_DIR
    #error "DSP Plotter base directory not set at compile-time. Don't know where to find fonts, etc."
#endif

GLFWwindow* window;
ImVec4 clear_color;
DSPPlotter::App app;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

extern "C" int DspPlotter_init( char *wavFilePath, 
                                uint32_t frameSize,
                                startupFunc_t startupFunc, 
                                processFunc_t processFunc,
                                shutdownFunc_t shutdownFunc) {

    // Try opening wav file just to make sure it works
    TinyWav tw;
    int err = tinywav_open_read(&tw, wavFilePath, TW_SPLIT);
    if (err != 0) {
        fprintf(stderr, "ERROR: Could not open wav file\n");
        return DspPlotterErr_CouldNotOpenWavFile;
    }
    tinywav_close_read(&tw);

    // Paths
    const char * baseDir = DSPPLOTTER_BASE_DIR;
    uint32_t baseDirLen = strlen(baseDir);
    uint32_t resDirLen = baseDirLen + 4; // .../res
    uint32_t fontPathLen = resDirLen + 11; // .../res/Tahoma.ttf
    char resDir[resDirLen];
    strcpy(resDir, baseDir);
    strcat(resDir, "/res");

    char fontPath[fontPathLen];
    strcpy(fontPath, resDir);
    strcat(fontPath, "/Tahoma.ttf");

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return DspPlotterErr_Error;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create window with graphics context
    std::string prefix( "DSP Plotter: ");
    char windowTitle[prefix.size() + strlen(wavFilePath)];
    strcpy(windowTitle, prefix.c_str());
    strcat(windowTitle, wavFilePath);
    
    window = glfwCreateWindow(1280, 720, windowTitle, nullptr, nullptr);
    if (window == nullptr)
        return DspPlotterErr_Error;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable docking
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    printf("Font path: %s\n", fontPath);

    ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath, 18.f);
    IM_ASSERT(font != nullptr);

    // Our state
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    app.init(wavFilePath, frameSize, startupFunc, processFunc, shutdownFunc);

    return DspPlotterErr_NoError;
}

// Main code
extern "C" int DspPlotter_show()
{
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();
        app.onFrame();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return DspPlotterErr_NoError;
}


#endif /* DSP_PLOTTER_CPP */
