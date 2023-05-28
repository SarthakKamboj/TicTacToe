#include "vao.h"

/*
VAO::VAO() {
	glGenVertexArrays(1, &id);
}

void VAO::bind() {
	glBindVertexArray(id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::enableAttribute(VBO& vbo, int attrId, int numValues, int dType, int normalized, int stride, int offset) {
	bind();
	vbo.bind();
	glVertexAttribPointer(attrId, numValues, dType, normalized, stride, (void*)offset);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attrId);
}
*/

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
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attrId);
}
