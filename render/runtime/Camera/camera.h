#ifndef CAMERA_H_
#define CAMERA_H_

#include "kmath.h"
namespace krender
{
    using namespace math;
    class Camera{
    public:
        Camera(const Vec3f& pos, const Vec3f& front, const Vec3f& up) : m_cameraPos(pos), m_cameraFront(front), m_cameraUp(up){}
        void setPos(const Vec3f& Pos);
        void setFront(const Vec3f& Front);
        void setUp(const Vec3f& Up);
        void setSpeed(float speed);
        mat4 GetLookAt();
    public:
        Vec3f m_cameraPos{};
        Vec3f m_cameraFront{};
        Vec3f m_cameraUp{};
        float m_speed{ 1.0f };
    };
} // namespace krender


#endif