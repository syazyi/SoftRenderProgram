#ifndef KRENDER_FRAMEBUFFER_H
#define KRENDER_FRAMEBUFFER_H
#include<vector>
#include"vec4.h"
namespace krender {

	class FrameBuffer {
	public:
		std::vector<float> z_buffer;
		std::vector<unsigned char> framebuffer_;
		int width_;
		int height_;

	public:
		FrameBuffer(int const& width, int const& height);
		void FrameBufferReSize(int const& width, int const& height);
		void FrameBufferSetZBuffer(int x, int y, float z);
		void FrameBufferSetPixel(int x, int y, math::ColorVec4& color);
		bool FrameBufferCompareZBuffer(int x, int y, float z);
		void FrameBufferClear();
	};
}
#endif