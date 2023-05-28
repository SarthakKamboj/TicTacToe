#pragma once

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <string>

/*
class Shader {
public:
	Shader(const char* vertPath, const char* fragPath);
	Shader();
	void bind();
	void unbind();

	void setMat4(const char* varName, const glm::mat4& mat);
	void setInt(const char* varName, const int val);
	void setVec3(const char* varName, const glm::vec3 v);
	glm::vec3 getVec3(const char* varName);
	GLuint id;

private:
	std::string getFileContents(const char* path);
};
*/

struct shader_t {
	GLuint id = 0;
};

shader_t create_shader(const char* vert_path, const char* frag_path);
void bind_shader(const shader_t& shader);
void unbind_shader();
void shader_set_mat4(shader_t& shader, const char* var_name, const glm::mat4& mat);
void shader_set_int(shader_t& shader, const char* var_name, const int val);
void shader_set_vec3(shader_t& shader, const char* var_name, const glm::vec3& v);
glm::vec3 shader_get_vec3(const shader_t& shader, const char* var_name);
