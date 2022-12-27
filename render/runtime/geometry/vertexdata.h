#ifndef KRENDER_VERTEXDATA_H
#define KRENDER_VERTEXDATA_H
#include "vec4.h"
namespace krender{
    class VertexData{
    public:
        math::Vec4f position;
        math::ColorVec4 color;
    public:
        VertexData() = default;
        VertexData(math::Vec4f const& vertex_position, math::ColorVec4 const& vertex_color);

        void SetVertexPosition(math::Vec4f const& vertex_position);
        void SetVertexColor(math::ColorVec4 const& vertex_color);
        //To be done
        math::Vec4f& GetPosition();
        math::ColorVec4& GetColor();
        
    };
}
#endif