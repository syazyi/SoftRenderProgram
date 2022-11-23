#pragma once
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
        
        std::pair<float, float> Interpolation(VertexDataSet& vertexlist, math::Vec3f& const point);
    };
} // namespace krender
