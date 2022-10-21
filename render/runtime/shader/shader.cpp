#include "shader.h"

krender::Shader::Shader() : model(1.f), view(1.f){}

void krender::Shader::SetModel(math::mat4 const& pmodel) {
	model = pmodel;
}

void krender::Shader::SetView(math::mat4 const& pview) {
	view = pview;
}

krender::Shader::~Shader(){
}
