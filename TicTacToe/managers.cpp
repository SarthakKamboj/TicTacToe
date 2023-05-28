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

/*
int EBOManager::addEbo(const EBO& ebo) {
	for (int i = 0; i < ebos.size(); i++) {
		const EBO& curEBo = ebos[i];
		if (ebo.id == curEBo.id) {
			return i;
		}
	}
	ebos.push_back(ebo);
	return ebos.size() - 1;
}

int EBOManager::removeEbo(const EBO& ebo) {
	int idx = -1;
	for (int i = 0; i < ebos.size(); i++) {
		const EBO& curEbo = ebos[i];
		if (ebo.id == curEbo.id) {
			idx = i;
			break;
		}
	}
	
	if (idx != -1) {
		ebos.erase(ebos.begin() + idx, ebos.begin() + idx + 1);
		return ebo.id;
	}
	return -1;
}

int ShaderManager::addShader(const Shader& shader) {
	for (int i = 0; i < shaders.size(); i++) {
		const Shader& curShader = shaders[i];
		if (shader.id == curShader.id) {
			return i;
		}
	}
	shaders.push_back(shader);
	return shaders.size() - 1;
}

int ShaderManager::removeShader(const Shader& shader) {
	int idx = -1;
	for (int i = 0; i < shaders.size(); i++) {
		const Shader& curShader = shaders[i];
		if (curShader.id == shader.id) {
			idx = i;
			break;
		}
	}
	
	if (idx != -1) {
		shaders.erase(shaders.begin() + idx, shaders.begin() + idx + 1);
		return shader.id;
	}
	return -1;
}
*/
