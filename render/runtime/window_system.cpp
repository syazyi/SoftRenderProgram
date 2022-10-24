#include "window_system.h"

namespace krender{

    window_system::window_system(){
        window = nullptr;
    }

    WINDOW_ERROR_CODE window_system::initWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        window = glfwCreateWindow(kWindowWidth, kWindowHeight, "opengl", nullptr, nullptr);
        if (window == nullptr){
            glfwTerminate();
            return WINDOW_ERROR_CODE::WINDOW_CREATE_ERROR;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            return WINDOW_ERROR_CODE::GLAD_ERROR;
        }
        return WINDOW_ERROR_CODE::NO_ERROR;
    }

    bool window_system::shouldClose(){
        return glfwWindowShouldClose(window);
    }

    void window_system::windowSwapBuffer(){
        glfwSwapBuffers(window);
    }

    void window_system::pollEvent(){
        glfwPollEvents();
    }

    double window_system::getCurrentTime(){
        return glfwGetTime();
    }
    window_system::~window_system(){
        glfwTerminate();
    }

    int window_system::getWindowHeight(){
        return kWindowHeight;
    }

    int window_system::getWindowWidth(){
        return kWindowWidth;
    }
}