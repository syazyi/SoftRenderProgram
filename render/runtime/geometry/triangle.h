#pragma once
#include <array>
#include "vertexdata.h"
namespace krender
{
    class Triangle{
    public:
        std::array<VertexData, 3> vertexdata;
    public:
        Triangle() = default;
        Triangle(VertexData const& a, VertexData const& b, VertexData const& c);
    };
} // namespace krender
