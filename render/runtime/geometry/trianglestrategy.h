#ifndef KRENDER_TRIANGLESTRATEGY_H
#define KRENDER_TRIANGLESTRATEGY_H
#include <array>

#include "rasterizestrategy.h"
#include "vec3.h"
#include "shader.h"

namespace krender
{
    class TriangleStrategy : public RasterizeStrategy{
    public:
        virtual void Draw(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex, FrameBuffer* pframebuffer, Shader* shader) override;
        bool InsideTriangle(float x, float y, std::array<math::Vec4f, 3> triangle);
        
        math::ColorVec4 InterpolationColor(float x, float y, const std::array<VertexData, 3>& triangle);
        float clampColor(float a){
            if(a > 255.f){
                return 255.f;
            }
            if(a < 0.f){
                return 0.f;
            }
            return a;
        }
    };
} // namespace krender
#endif