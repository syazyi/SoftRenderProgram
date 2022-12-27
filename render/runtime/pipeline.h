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
        explicit Pipeline(std::shared_ptr<FrameBuffer>& pframebuffer, VertexDataSet* vertexdata, Shader* pshader, RasterizeStrategy* rastertemp);
        Pipeline(Pipeline const&) = delete;

        void Rendering();
        void Project(VertexDataSet& pvertexlist);
        void Clip(VertexDataSet& pvertexlist);
        void ScreenMapping(VertexDataSet& pvertexlist);
        void setFramebuffer(std::shared_ptr<FrameBuffer>& pframebuffer);
        void PipelineClear();
        ~Pipeline();
    private:
        std::shared_ptr<FrameBuffer> framebuffer;
        VertexDataSet* vertexlist;
        Shader* shader;
        RasterizeStrategy* rasterize;
    };
}
#endif