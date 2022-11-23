#pragma once
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "shader.h"
namespace krender
{
    class RasterizeStrategy{
    public:
        virtual void Draw(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex, FrameBuffer* pframebuffer, Shader* shader) = 0;
        virtual std::pair<float, float> Interpolation(const VertexDataSet& vertexlist, const math::Vec3f& point) = 0;
        virtual ~RasterizeStrategy(){}
    };
} // namespace krender
