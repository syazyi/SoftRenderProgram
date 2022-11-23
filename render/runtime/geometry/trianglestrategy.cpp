#include "trianglestrategy.h"

void krender::TriangleStrategy::Draw(VertexDataSet& vertexlist, VertexDataSet& viewvertex, FrameBuffer* pframebuffer, Shader* shader){
    //这里仅仅只绘制了一个三角形，因此还要考虑多三角形的情况。
    for (int k = 0; k < vertexlist.triangleNums * 2; k += 3) {
        math::Vec4f vertex1 = vertexlist.vertex[vertexlist.vertex_index[k] - 1].position;
        math::Vec4f vertex2 = vertexlist.vertex[vertexlist.vertex_index[k + 1] - 1].position;
        math::Vec4f vertex3 = vertexlist.vertex[vertexlist.vertex_index[k + 2] - 1].position;

        int upper = std::max(vertex1.y, std::max(vertex2.y, vertex3.y));
        int bottom = std::min(vertex1.y, std::min(vertex2.y, vertex3.y));
        int right = std::max(vertex1.x, std::max(vertex2.x, vertex3.x));
        int left = std::min(vertex1.x, std::min(vertex2.x, vertex3.x));
        for (int i = bottom; i <= upper; i++) {
            for (int j = left; j <= right; j++) {
                   float x = j + 0.5;
                   float y = i + 0.5;
                   
                   std::array<math::Vec4f, 3> triangle = {vertex1, vertex2, vertex3};
                   if (InsideTriangle(x, y, triangle)) {
                       math::ColorVec4 color = shader->FragmentShader(vertexlist, viewvertex);
                       pframebuffer->FrameBufferSetPixel(x, y, color);
                   }
                /*math::ColorVec4 color;
                std::array<math::Vec4f, 3> triangle = { vertex1, vertex2, vertex3 };
                float msaaWeight[2] = { 0.25, 0.75 };
                for (int m = 0; m < 2; m++) {
                    for (int n = 0; n < 2; n++) {
                        if (InsideTriangle(j + msaaWeight[m], i + msaaWeight[n], triangle)) {
                            color += shader->FragmentShader(vertexlist, viewvertex);
                        }
                    }
                }
                color /= 4;
                pframebuffer->FrameBufferSetPixel(x, y, color);*/
            }
        }
    }
}

bool krender::TriangleStrategy::InsideTriangle(float x, float y, std::array<math::Vec4f, 3> triangle){
    //Assuming that the vertex indexes have been arranged in clockwise(non-counterclockwise) order
	math::Vec3f a = (triangle[1] - triangle[0]).ToVec3();
    math::Vec3f b = (triangle[2] - triangle[1]).ToVec3();
    math::Vec3f c = (triangle[0] - triangle[2]).ToVec3();
    math::Vec3f d = (math::Vec4f(x, y, 0) - triangle[0]).ToVec3();
    math::Vec3f e = (math::Vec4f(x, y, 0) - triangle[1]).ToVec3();
    math::Vec3f f = (math::Vec4f(x, y, 0) - triangle[2]).ToVec3();
    return (Cross(a, d).z < 0 && Cross(b, e).z < 0 && Cross(c, f).z < 0);
}

std::pair<float, float> krender::TriangleStrategy::Interpolation(VertexDataSet& const vertexlist, math::Vec3f& const point){
    float alpha = 0;
    float beta = 1;
    math::Vec3f a;
    return std::pair<float, float>(alpha, beta);
}