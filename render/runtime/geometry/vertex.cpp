#include"vertex.h"
#include<assert.h>

void krender::VertexDataSet::AddVertex(VertexData& vertexdata) {
    vertex.push_back(vertexdata);
}
void krender::VertexDataSet::AddIndex(uint32_t pindex){
    vertex_index.push_back(pindex);
}

void krender::VertexDataSet::setTriangleNums()
{
    assert(vertex_index.size() % 3 == 0);
    triangleNums = vertex_index.size() / 3;
}
