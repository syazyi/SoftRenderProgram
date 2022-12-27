#ifndef KRENDER_RASTERIZESTRATEGY_H
#define KRENDER_RASTERIZESTRATEGY_H
#include <utility>
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "shader.h"
namespace krender
{
    class RasterizeStrategy{
    public:
        virtual void Draw(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex, FrameBuffer* pframebuffer, Shader* shader) = 0;
        virtual ~RasterizeStrategy(){}
    };
} // namespace krender
#endif