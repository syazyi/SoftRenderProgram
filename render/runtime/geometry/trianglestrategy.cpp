#include "trianglestrategy.h"

auto krender::TriangleStrategy::interpolation(float x, float y, const std::array<VertexData, 3>& triangle)
{
    math::Vec3f a = triangle[0].position.ToVec3();
    math::Vec3f b = triangle[1].position.ToVec3();
    math::Vec3f c = triangle[2].position.ToVec3();

    float alpha = (-(x - b.x) * (c.y - b.y) + (y - b.y) * (c.x - b.x)) / (-(a.x - b.x) * (c.y - b.y) + (a.y - b.y) * (c.x - b.x));
    float beta = (-(x - c.x) * (a.y - c.y) + (y - c.y) * (a.x - c.x)) / (-(b.x - c.x) * (a.y - c.y) + (b.y - c.y) * (a.x - c.x));
    float gamma = 1 - alpha - beta;

    return std::make_tuple(alpha, beta, gamma);
}

void krender::TriangleStrategy::Draw(VertexDataSet& vertexlist, VertexDataSet& viewvertex, FrameBuffer* pframebuffer, Shader* shader){
    
    for (int k = 0; k < vertexlist.triangleNums * 3; k += 3) {
        math::Vec4f vertex1 = vertexlist.vertex[vertexlist.vertex_index[k] - 1].position;
        math::Vec4f vertex2 = vertexlist.vertex[vertexlist.vertex_index[k + 1] - 1].position;
        math::Vec4f vertex3 = vertexlist.vertex[vertexlist.vertex_index[k + 2] - 1].position;

        auto verView1 = vertexlist.vertex[vertexlist.vertex_index[k] - 1];
        auto verView2 = vertexlist.vertex[vertexlist.vertex_index[k + 1] - 1];
        auto verView3 = vertexlist.vertex[vertexlist.vertex_index[k + 2] - 1];

        int upper = std::max(vertex1.y, std::max(vertex2.y, vertex3.y));
        int bottom = std::min(vertex1.y, std::min(vertex2.y, vertex3.y));
        int right = std::max(vertex1.x, std::max(vertex2.x, vertex3.x));
        int left = std::min(vertex1.x, std::min(vertex2.x, vertex3.x));
        for (int i = bottom; i <= upper; i++) {
            for (int j = left; j <= right; j++) {
                    float x = j + 0.5;
                    float y = i + 0.5;
                   
                    std::array<math::Vec4f, 3> triangle = {vertex1, vertex2, vertex3};
                    std::array<VertexData, 3> triangleView = {verView1, verView2, verView3};
                if (InsideTriangle(x, y, triangle)) {
                    auto [alpha, beta, gamma] = interpolation(x, y, triangleView);
                    float zValue = InterpolationZBuffer(alpha, beta, gamma, triangleView);
                    
                    if (pframebuffer->FrameBufferCompareZBuffer(x, y, zValue)) {
                        //Pass the z-test
                        pframebuffer->FrameBufferSetZBuffer(x, y, zValue);
                        math::ColorVec4 color = shader->FragmentShader(vertexlist, viewvertex, InterpolationColor(alpha, beta, gamma, triangleView));
                        pframebuffer->FrameBufferSetPixel(x, y, color);
                    }
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
    auto adz = Cross(a, d).z;
    auto bez = Cross(b, e).z;
    auto cfz = Cross(c, f).z;
    return (( adz < 0 && bez < 0 && cfz < 0) || ( adz > 0 && bez > 0 && cfz > 0));
}

krender::math::ColorVec4 krender::TriangleStrategy::InterpolationColor(float x, float y, const std::array<VertexData, 3>& triangle){
    auto [alpha, beta, gamma] = krender::TriangleStrategy::interpolation(x, y, triangle);

    auto colorX = clampColor(alpha * triangle[0].color.x + beta * triangle[1].color.x + gamma * triangle[2].color.x);
    auto colorY = clampColor(alpha * triangle[0].color.y + beta * triangle[1].color.y + gamma * triangle[2].color.y);
    auto colorZ = clampColor(alpha * triangle[0].color.z + beta * triangle[1].color.z + gamma * triangle[2].color.z);
    auto colorA = clampColor(alpha * triangle[0].color.w + beta * triangle[1].color.w + gamma * triangle[2].color.w);

 
    return math::ColorVec4((unsigned char)colorX, (unsigned char)colorY, (unsigned char)colorZ, (unsigned char)colorA);
    //math::Vec3f a;
    
}

krender::math::ColorVec4 krender::TriangleStrategy::InterpolationColor(float alpha, float beta, float gamma, const std::array<VertexData, 3>& triangle)
{
    auto colorX = clampColor(alpha * triangle[0].color.x + beta * triangle[1].color.x + gamma * triangle[2].color.x);
    auto colorY = clampColor(alpha * triangle[0].color.y + beta * triangle[1].color.y + gamma * triangle[2].color.y);
    auto colorZ = clampColor(alpha * triangle[0].color.z + beta * triangle[1].color.z + gamma * triangle[2].color.z);
    auto colorA = clampColor(alpha * triangle[0].color.w + beta * triangle[1].color.w + gamma * triangle[2].color.w);


    return math::ColorVec4((unsigned char)colorX, (unsigned char)colorY, (unsigned char)colorZ, (unsigned char)colorA);
}

float krender::TriangleStrategy::InterpolationZBuffer(float x, float y, const std::array<VertexData, 3>& triangle)
{
    auto [alpha, beta, gamma] = interpolation(x, y, triangle);

    float zBufferValue = alpha * triangle[0].position.z + beta * triangle[1].position.z + gamma * triangle[2].position.z;

    return zBufferValue;
}

float krender::TriangleStrategy::InterpolationZBuffer(float alpha, float beta, float gamma, const std::array<VertexData, 3>& triangle)
{
    float zBufferValue = alpha * triangle[0].position.z + beta * triangle[1].position.z + gamma * triangle[2].position.z;

    return zBufferValue;
}


