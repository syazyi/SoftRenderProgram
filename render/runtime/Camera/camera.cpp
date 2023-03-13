#include "camera.h"

namespace krender
{
    void Camera::setPos(const Vec3f &Pos)
    {
        m_cameraPos = Pos;
    }

    void Camera::setFront(const Vec3f &Front)
    {
        m_cameraFront = Front;
    }

    void Camera::setUp(const Vec3f &Up)
    {
        m_cameraUp = Up;
    }

    void Camera::setSpeed(float speed)
    {
        m_speed = speed;
    }

    mat4 Camera::GetLookAt()
    {
        Vec3f atPos = m_cameraPos + m_cameraFront;
        Vec3f zCamera = (atPos - m_cameraPos).Normalize();
        
        Vec3f xCamera = Cross(zCamera, m_cameraUp).Normalize();
        Vec3f yCamera = Cross(xCamera, zCamera).Normalize();

        mat4 View = mat4(
            xCamera.x, xCamera.y, xCamera.z, -(m_cameraPos * xCamera),
            yCamera.x, yCamera.y, yCamera.z, -(m_cameraPos * yCamera),
            -zCamera.x, -zCamera.y, -zCamera.z, m_cameraPos * zCamera,
            0, 0, 0, 1
        );
        return View;
    }
} // namespace krender

