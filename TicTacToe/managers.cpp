#include "managers.h"
#include "globals.h"

extern globals_t globals;

int add_ebo(ebo_manager_t& manager, ebo_t& ebo) {
	std::vector<ebo_t>& ebos = manager.ebos;
	for (int i = 0; i < ebos.size(); i++) {
		const ebo_t& cur_ebo = ebos[i];
		if (ebo.id == cur_ebo.id) {
			return i;
		}
	}
	ebos.push_back(ebo);
	return ebos.size() - 1;
}

int add_shader(shader_manager_t& manager, shader_t& shader) {
	std::vector<shader_t>& shaders = manager.shaders;
	for (int i = 0; i < shaders.size(); i++) {
		const shader_t& cur_shader = shaders[i];
		if (shader.id == cur_shader.id) {
			return i;
		}
	}
	shaders.push_back(shader);
	return shaders.size() - 1;
}

int add_vao(vao_manager_t& manager, vao_t& vao) {
	std::vector<vao_t>& vaos = manager.vaos;
	for (int i = 0; i < vaos.size(); i++) {
		const vao_t& cur_vao = vaos[i];
		if (vao.id == cur_vao.id) {
			return i;
		}
	}
	vaos.push_back(vao);
	return vaos.size() - 1;
}

int add_vbo(vbo_manager_t& manager, vbo_t& vbo) {
	std::vector<vbo_t>& vbos = manager.vbos;
	for (int i = 0; i < vbos.size(); i++) {
		const vbo_t& cur_vbo = vbos[i];
		if (vbo.id == cur_vbo.id) {
			return i;
		}
	}
	vbos.push_back(vbo);
	return vbos.size() - 1;
}
