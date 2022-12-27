#ifndef KRENDER_SHADER_H
#define KRENDER_SHADER_H
#include "mat4x4.h"
#include "vertex.h"
#include "framebuffer.h"
//优化思路：设置类似Shader中的全局上下文的格式，使用结构体设置。这样一些矩阵使用上下文去设置即可。
namespace krender {
	class Shader {
	public:
		Shader();
		virtual void VertexShader(VertexDataSet& vertexlist) = 0;
		virtual math::ColorVec4 FragmentShader(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex, const math::ColorVec4& pointSelfColor) = 0;
		virtual void SetModel(math::mat4 const& pmodel);
		virtual void SetView(math::mat4 const& pview);

		virtual ~Shader();
	protected:
		math::mat4 model;
		math::mat4 view;
	};
}
#endif