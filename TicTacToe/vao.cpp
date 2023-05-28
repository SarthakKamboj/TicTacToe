#include "vao.h"

vao_t create_vao() {
	vao_t vao;
	glGenVertexArrays(1, &vao.id);
	return vao;
}

void bind_vao(const vao_t& vao) {
	glBindVertexArray(vao.id);
}

void unbind_vao() {
	glBindVertexArray(0);
}

void vao_enable_attribute(vao_t& vao, const vbo_t& vbo, const int attrId, const int numValues, const int dType, const int normalized, const int stride, const int offset) {
	bind_vao(vao);
	bind_vbo(vbo);
	glVertexAttribPointer(attrId, numValues, dType, normalized, stride, (void*)offset);
	glEnableVertexAttribArray(attrId);
}

void delete_vao(const vao_t& vao) {
	glDeleteVertexArrays(1, &vao.id);
}
