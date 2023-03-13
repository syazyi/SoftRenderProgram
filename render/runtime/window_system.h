#ifndef KRENDER_WINDOWS_SYSTEM_H
#define KRENDER_WINDOWS_SYSTEM_H
#include"glad/glad.h"
#include"glfw/glfw3.h"


namespace krender
{
    class Camera;   
    enum class WINDOW_ERROR_CODE{
        WINDOW_CREATE_ERROR,
        GLAD_ERROR,
        NO_ERROR
    };
    class window_system
    {
    private:
        static constexpr int kWindowWidth = 800;
        static constexpr int kWindowHeight = 600;
    public:
        GLFWwindow* window;
    public:
        window_system();
        ~window_system();
        WINDOW_ERROR_CODE initWindow();
        bool shouldClose();
        double getCurrentTime();
        void windowSwapBuffer();
        void ProcessInput(Camera& camera);
        void pollEvent();
        
        static int getWindowWidth();
        static int getWindowHeight();
    };

} // namespace krender
#endif