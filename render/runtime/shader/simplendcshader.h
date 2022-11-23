#pragma once
#include "kmath.h"
#include "shader.h"

namespace krender{
    class SimpleNDCShader : public Shader{
    public:
        SimpleNDCShader() = default;
        //SimpleNDCShader(FragmentStrategy* pstrategy);
        virtual void VertexShader(VertexDataSet& vertexlist) override;
        virtual math::ColorVec4 FragmentShader(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex) override;
        
    };
}