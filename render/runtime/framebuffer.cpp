#include"framebuffer.h"


using krender::FrameBuffer;
using krender::math::ColorVec4;

FrameBuffer::FrameBuffer(int const& width, int const& height) : width_(width), height_(height) {
	framebuffer_.resize(width * height * 4);
}

void FrameBuffer::FrameBufferReSize(int const& width, int const& height) {
	framebuffer_.resize(width * height * 4);
}

void FrameBuffer::FrameBufferSetPixel(int x, int y, ColorVec4& color) {
	if (x < 0 || x >= width_ || y < 0 || y >= height_) {
		//Kaf.log("The parameter is out of range");
		return;
	}
	int index = (x + y * width_) * 4;
	framebuffer_[index] = color.x;
	framebuffer_[index + 1] = color.y;
	framebuffer_[index + 2] = color.z;
	framebuffer_[index + 3] =  color.w;
}

void FrameBuffer::FrameBufferClear() {
	//faster method
	std::fill(framebuffer_.begin(), framebuffer_.end(), 0);
}