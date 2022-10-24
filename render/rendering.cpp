#include<vector>
#include<memory>

#include "kmath.h"

#include "window_system.h"
#include "triangle.h"
#include "trianglelist.h"
#include "vertexdata.h"
#include "pipeline.h"
#include"framebuffer.h"
#include "trianglestrategy.h"

using namespace krender::math;

int main(){
	
	std::shared_ptr<krender::window_system> window = std::make_shared<krender::window_system>();
	if(window->initWindow() != krender::WINDOW_ERROR_CODE::NO_ERROR){
		return -1;
	}
	//Test
	std::shared_ptr<krender::FrameBuffer> colorbuffer = std::make_shared<krender::FrameBuffer>(krender::window_system::getWindowWidth(), krender::window_system::getWindowHeight());
	//std::shared_ptr<krender::FrameBuffer> colorbufferSecond = std::make_shared<krender::FrameBuffer>(kWindowWeight, kWindowHeight);
	
	
	Vec3f a(0.0f, 0.1f, 0);
	Vec3f b(0.1f, 0.0f, 0);
	Vec3f c(-0.1f, 0.0f, 0);

	Vec3f a1(0.0f, -0.1f, 0);

	ColorVec4 a_color(255, 0, 0);
	ColorVec4 b_color(0, 255, 0);
	ColorVec4 c_color(0, 0, 255);

	krender::VertexData a_vertex(Vec4f(a), a_color);
	krender::VertexData b_vertex(Vec4f(b), b_color);
	krender::VertexData c_vertex(Vec4f(c), c_color);

	krender::VertexData a1_vertex(Vec4f(a1), a_color);

	//krender::Triangle* triangle_test = new krender::Triangle(a_vertex, b_vertex, c_vertex);
	krender::VertexDataSet* vertexdata_set = new krender::VertexDataSet();
	vertexdata_set->AddVertex(a_vertex);
	vertexdata_set->AddVertex(b_vertex);
	vertexdata_set->AddVertex(c_vertex);
	vertexdata_set->AddVertex(a1_vertex);

	vertexdata_set->AddIndex(1);
	vertexdata_set->AddIndex(2);
	vertexdata_set->AddIndex(3);

	vertexdata_set->AddIndex(2);
	vertexdata_set->AddIndex(4);
	vertexdata_set->AddIndex(3);

	vertexdata_set->setTriangleNums();

	//krender::TriangleList* triangle_list = new krender::TriangleList();
	//triangle_list->AddTriangle(triangle_test);
	krender::RasterizeStrategy* raster = new krender::TriangleStrategy;
	krender::Shader* simpleshader = new krender::SimpleNDCShader;


	krender::Pipeline* pipeline = new krender::Pipeline(colorbuffer, simpleshader, vertexdata_set, raster);
	
	//Test

	while (!window->shouldClose()) {
		float time = window->getCurrentTime();
		float angle = time *  3.14159f / 180.f * 10.f;
		krender::math::mat4 roatoa_model(cos(angle), -sin(angle), 0, 0,
								  sin(angle),  cos(angle), 0, 0,
								           0, 		    0, 1, 0,
								           0,           0, 0, 1);
		krender::math::mat4 move_model(1, 0, 0, 0.0f,
									   0, 1, 0, 0.0f,
									   0, 0, 1, 0,
									   0, 0, 0, 1);
		krender::math::mat4 move_back_model(1, 0, 0, 0.0f,
									   0, 1, 0, 0.0f,
									   0, 0, 1, 0,
									   0, 0, 0, 1);
		simpleshader->SetModel(move_back_model*=roatoa_model*=move_model);
		krender::math::Vec3f lookat(0, 0, -1);
		krender::math::Vec3f up(0, 1, 0);
		krender::math::Vec3f lux = Cross(lookat, up);
		krender::math::mat4 viewmat4(lux.x, lux.y, lux.z, 0, 
									 up.x, up.y, up.z, 0, 
									 -lookat.x, -lookat.y, -lookat.z, 0,
									 0, 0, 0, 1);
		simpleshader->SetView(viewmat4);
		pipeline->PipelineClear();

		pipeline->Rendering();
		glDrawPixels(krender::window_system::getWindowWidth(), krender::window_system::getWindowHeight(), GL_RGBA, GL_UNSIGNED_BYTE, colorbuffer->framebuffer_.data());

		window->windowSwapBuffer();
		window->pollEvent();
	}
	//这里渲染结果被拉长是因为长和宽的比例不是一比一所以被拉长。可能需要设置摄像机或窗口使他比例协调。
	pipeline->PipelineClear();
	delete raster;
	delete vertexdata_set;
	delete pipeline;
	delete simpleshader;
	return 0;
}
