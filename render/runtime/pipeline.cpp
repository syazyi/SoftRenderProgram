#include "pipeline.h"
#include "window_system.h"
 krender::Pipeline::Pipeline(FrameBuffer* pframebuffer, VertexDataSet* vertexdata, Shader* pshader, RasterizeStrategy* rastertemp) : 
     framebuffer(pframebuffer), vertexlist(vertexdata), shader(pshader), rasterize(rastertemp) {}

void krender::Pipeline::Rendering() {
    //对每个三角形操作，粒度不够细，还需要完成画线操作，如果我只是想画线，两个顶点之间连一条线，而未链接的顶点不划线。似乎可以使用链表维护三角形顶点。
    //obj文件中是哪几个顶点组成一个三角形。将顶点全部列出，通过三角中的索引（三角形中存索引？）访问顶点，再那这些顶点计算，这样就是使用现成的数据了。
    //使用顶点数组而不是三角形，使用顶点索引访问三角形。不同对顶点索引的解释方式可以设置不同的图形，比如三角形，四边形，以及线等。
    VertexDataSet* tempvertex = new VertexDataSet(*vertexlist);

    //由于矩阵的乘法结合律，可以先将总体矩阵计算出来再计算最终顶点位置。这一个阶段可以叫做几何阶段。
    shader->VertexShader(*tempvertex);
    VertexDataSet view_pos = *tempvertex;
    Project(*tempvertex, EProjectType::Perspective);
    Clip(*tempvertex);
    ScreenMapping(*tempvertex);
    //对三角形进行画边（或画点）而不是画三角形，需要修改顶点着色器的实现，当然可以使用不同的实现去画线，这里可能要用到策略模式。该函数接口可能因为这个原因需要变化。
    
    rasterize->Draw(*tempvertex, view_pos, framebuffer, shader);
    // shader->FragmentShader(*tempvertex, view_pos, framebuffer);
    delete tempvertex;
}
void krender::Pipeline::Project(VertexDataSet& pvertexlist, EProjectType type) {
    math::mat4 projectionmat;
    if (type == EProjectType::Orthogonal) {
        float r = 1.f * ((float)framebuffer->width_ / (float)framebuffer->height_);
        float l = -r;
        float t = 1.f;
        float b = -t;
        float n = -1.f;
        float f = 1.f;
        projectionmat = math::mat4(
            2.f / (r - l), 0, 0, (r + l) / (l - r),
            0, 2 / (t - b), 0, (t + b) / (b - t),
            0, 0, 2 / (n - f), (f + n) / (n - f),
            0, 0, 0, 1
        );
    }
    else if (type == EProjectType::Perspective){
        float fovy = math::Radians(45.0f);
        float aspect = float(framebuffer->width_) / float(framebuffer->height_);
        float n = 0.1f;
        float f = 100.f;
        float tanHalfFovy = tan(fovy / 2.0f);
        projectionmat = math::mat4{
            1.0f / (aspect * tanHalfFovy), 0, 0, 0,
            0, 1.0f / (tanHalfFovy), 0, 0, 
            0, 0, -(f + n) / (f - n), -2.f * f * n / (f - n), 
            0, 0, -1, 0
        };
    }
    

    for (auto& a : pvertexlist.vertex) {
        a.position *= projectionmat;
    }
    //Put it in the vertex shader first
}

void krender::Pipeline::Clip(VertexDataSet& pvertexlist) {
    //if x, y <0 && >1, clip.
    for(auto& a : pvertexlist.vertex){
        a.position /= a.position.w;
    }
}

void krender::Pipeline::ScreenMapping(VertexDataSet& pvertexlist) {
    for (auto& temp_vertexdata : pvertexlist.vertex) {
        //  temp_vertexdata.position[0] *= framebuffer->width_;
        //  temp_vertexdata.position[1] *= framebuffer->height_;
        krender::math::mat4 viewport(framebuffer->width_ / 2, 0, 0, framebuffer->width_ / 2,
                                     0, framebuffer->height_ / 2, 0, framebuffer->height_ / 2,
                                     0, 0, 1, 0,
                                     0, 0, 0, 1);
        temp_vertexdata.position *= viewport;
    }
}


void krender::Pipeline::setFramebuffer(FrameBuffer* pframebuffer) {
    framebuffer = pframebuffer;
}


void krender::Pipeline::PipelineClear(){
    framebuffer->FrameBufferClear();
}

krender::Pipeline::~Pipeline() {
}