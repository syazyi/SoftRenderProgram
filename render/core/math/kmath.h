#ifndef KRENDER_KMATH_H
#define KRENDER_KMATH_H
#include <cmath>
#include "mat4x4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

namespace krender
{
    namespace math
    {
        //Angle of rotation of vector P around unit axis A theta
        static mat4 GetRotationMatrix(const Vec3f& vecToR, const Vec3f& aixs_unit, float radian){
            float c = cos(radian);
            float s = sin(radian);
            mat4 rotation_mat (
                c + (1 - c) * aixs_unit.x * aixs_unit.x, (1 - c) * aixs_unit.x * aixs_unit.y - s * aixs_unit.z, (1 - c) * aixs_unit.x * aixs_unit.z + s * aixs_unit.y, 0,
                (1 - c) * aixs_unit.x * aixs_unit.y + s * aixs_unit.z, c + (1 - c) * aixs_unit.y * aixs_unit.y,  (1 - c) * aixs_unit.z * aixs_unit.y - s * aixs_unit.x, 0, 
                (1 - c) * aixs_unit.z * aixs_unit.x - s * aixs_unit.y, (1 - c) * aixs_unit.z * aixs_unit.y + s * aixs_unit.x, c + (1 - c) * aixs_unit.z * aixs_unit.z, 0,
                 0, 0, 0, 1
            );
            return rotation_mat;
        }

        static float Radians(float degrees) {
            return degrees * static_cast<float>(0.01745329251994329576923690768489);
        }

    } // namespace math
    
} // namespace krender

#endif