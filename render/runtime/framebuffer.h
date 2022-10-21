#pragma once
#include<vector>
#include"vec4.h"
namespace krender {

	class FrameBuffer {
	public:
		std::vector<unsigned char> framebuffer_;
		int width_;
		int height_;

	public:
		FrameBuffer(int const& width, int const& height);
		void FrameBufferReSize(int const& width, int const& height);
		void FrameBufferSetPixel(int x, int y, math::ColorVec4& color);
		void FrameBufferClear();
	};
}
