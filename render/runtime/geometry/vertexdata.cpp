#include "vertexdata.h"

krender::VertexData::VertexData(math::Vec4f const& vertex_position, math::ColorVec4 const& vertex_color) : position(vertex_position), color(vertex_color) {
}

void krender::VertexData::SetVertexPosition(math::Vec4f const& vertex_position) {
    position = vertex_position;
}
void krender::VertexData::SetVertexColor(math::ColorVec4 const& vertex_color) {
    color = vertex_color;
}

krender::math::Vec4f& krender::VertexData::GetPosition(){
    return position;
}

krender::math::ColorVec4& krender::VertexData::GetColor(){
    return color;
}