#ifndef KRENDER_TRIANGLELIST_H
#define KRENDER_TRIANGLELIST_H
#include<vector>
#include "triangle.h"

namespace krender {
    class TriangleList {
    public:
        std::vector<Triangle*> trianglelist;
    public:
        TriangleList();
        void AddTriangle(Triangle* triangle);
    };
}
#endif