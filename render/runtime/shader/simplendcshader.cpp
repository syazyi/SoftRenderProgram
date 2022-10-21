#include "simplendcshader.h"

// krender::SimpleNDCShader::SimpleNDCShader(FragmentStrategy* pstrategy){
//     strategy = pstrategy;
// }

void krender::SimpleNDCShader::VertexShader(VertexDataSet& vertexlist){
    math::mat4 vm = view * model;
    for(auto& a : vertexlist.vertex){
        a.position *= vm;
    }
}
krender::math::ColorVec4 krender::SimpleNDCShader::FragmentShader(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex){
    return krender::math::ColorVec4(255, 0, 0, 255);
}

