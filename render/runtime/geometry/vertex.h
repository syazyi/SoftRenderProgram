#ifndef KRENDER_VERTEX_H
#define KRENDER_VERTEX_H
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
#endif