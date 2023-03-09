#ifndef KRENDER_PIPELINE_H
#define KRENDER_PIPELINE_H
#include<memory>
#include "framebuffer.h"
#include "triangle.h"
#include "trianglelist.h"
#include "kmath.h"
#include "simplendcshader.h"
#include "rasterizestrategy.h"

namespace krender{
    class Pipeline{
    public:
        explicit Pipeline(FrameBuffer* pframebuffer, VertexDataSet* vertexdata, Shader* pshader, RasterizeStrategy* rastertemp);
        Pipeline(Pipeline const&) = delete;

        void Rendering();
        void Project(VertexDataSet& pvertexlist);
        void Clip(VertexDataSet& pvertexlist);
        void ScreenMapping(VertexDataSet& pvertexlist);
        void setFramebuffer(FrameBuffer* pframebuffer);
        void PipelineClear();
        ~Pipeline();
    private:
        FrameBuffer* framebuffer;
        VertexDataSet* vertexlist;
        Shader* shader;
        RasterizeStrategy* rasterize;
    };
}
#endif