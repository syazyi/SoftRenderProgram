#pragma once
#include "mat4x4.h"
#include "vertex.h"
#include "framebuffer.h"

namespace krender {
	class Shader {
	public:
		Shader();
		virtual void VertexShader(VertexDataSet& vertexlist) = 0;
		virtual math::ColorVec4 FragmentShader(VertexDataSet& vertexlist, VertexDataSet& viewvedrtex) = 0;
		virtual void SetModel(math::mat4 const& pmodel);
		virtual void SetView(math::mat4 const& pview);
		void Interpolation();

		virtual ~Shader();
	protected:
		math::mat4 model;
		math::mat4 view;
	};
}
