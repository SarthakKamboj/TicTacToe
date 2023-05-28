#pragma once

#include <vector>
#include "ebo.h"
#include "shader.h"
#include "vao.h"

/*
class EBOManager {
public:
	EBOManager() = default;
	std::vector<EBO> ebos;
	int addEbo(const EBO& ebo);
	int removeEbo(const EBO& ebo);
};
*/

struct ebo_manager_t {
	std::vector<ebo_t> ebos;
};
int add_ebo(ebo_manager_t& manager, ebo_t& ebo);

struct shader_manager_t {
	std::vector<shader_t> shaders;
};
int add_shader(shader_manager_t& manager, shader_t& shader);

struct vao_manager_t {
	std::vector<vao_t> vaos;
};
int add_vao(vao_manager_t& manager, vao_t& vao);

/*
class ShaderManager {
public:
	ShaderManager() = default;
	std::vector<Shader> shaders;
	int addShader(const Shader& ebo);
	int removeShader(const Shader& ebo);
};
*/

/*
struct ImportantValues {
	int rectangleEBOIdx = -1;
	int outlineCirlceEboIdx = -1;
};
*/
