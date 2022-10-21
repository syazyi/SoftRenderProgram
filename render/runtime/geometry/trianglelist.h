#pragma once
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