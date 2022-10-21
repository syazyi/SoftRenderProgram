#pragma once
#include <vector>
#include "vertexdata.h"
//Abolition case
namespace krender{
    class VertexDataSet{
    public:
        std::vector<VertexData> vertex;
        std::vector<uint32_t> vertex_index;
        int triangleNums;
    public:
        VertexDataSet() = default;
        void AddVertex(VertexData& vertexdata);
        void AddIndex(uint32_t pindex);
        void setTriangleNums();
    };
}