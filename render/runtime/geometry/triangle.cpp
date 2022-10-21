#include "triangle.h"

krender::Triangle::Triangle(VertexData const& a, VertexData const& b, VertexData const& c) {
    vertexdata[0] = a;
    vertexdata[1] = b;
    vertexdata[2] = c;
}