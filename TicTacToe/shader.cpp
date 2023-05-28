#include "shader.h"
#include <string>
#include <iostream>
#include "globals.h"
#include "helper.h"

extern globals_t globals;

/*
Shader::Shader() {
	id = 0;
}

Shader::Shader(const char* vertPath, const char* fragPath) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	std::string vertStr = getFileContents(vertPath);
	const char* vertexShaderSource = vertStr.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	std::string fragStr = getFileContents(fragPath);
	const char* fragmentShaderSource = fragStr.c_str();
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glUseProgram(id);
}

void Shader::bind() {
	glUseProgram(id);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setMat4(const char* varName, const glm::mat4& mat) {
	glUseProgram(id);
	unsigned int loc = glGetUniformLocation(id, varName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setInt(const char* varName, const int val) {
	glUseProgram(id);
	unsigned int loc = glGetUniformLocation(id, varName);
	glUniform1i(loc, val);
}

void Shader::setVec3(const char* varName, const glm::vec3 v) {
	glUseProgram(id);
	unsigned int loc = glGetUniformLocation(id, varName);
	glUniform3fv(loc, 1, glm::value_ptr(v));
}

std::string Shader::getFileContents(const char* path) {
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int size = file.tellg();
	file.seekg(0, file.beg);
	std::ios_base::iostate state = file.rdstate();
	if (state != std::ios_base::goodbit) {
		std::cout << "error opening file" << std::endl;

	}
	while (!file.eof()) {
		char* data = new char[(int)size + 1];
		memset(data, 0, size + 1);
		file.read(data, size);
		std::string fileStr(data);
		delete[] data;
		file.close();
		return fileStr;
	}
	return std::string();
}

glm::vec3 Shader::getVec3(const char* varName) {
	glm::vec3 v;
	unsigned int loc = glGetUniformLocation(id, varName);
	glGetUniformfv(id, loc, &v[0]);
	return v;
}
*/

shader_t create_shader(const char* vert_path, const char* frag_path) {
	shader_t shader;

	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char info_log[512];

	std::string vert_code_str = helper::get_file_contents(vert_path);
	const char* vert_shader_source = vert_code_str.c_str();
	glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
	glCompileShader(vert_shader);
	glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vert_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	std::string frag_code_str = helper::get_file_contents(frag_path);
	const char* frag_shader_source = frag_code_str.c_str();
	glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
	glCompileShader(frag_shader);
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	shader.id = glCreateProgram();
	glAttachShader(shader.id, vert_shader);
	glAttachShader(shader.id, frag_shader);
	glLinkProgram(shader.id);
	glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader.id, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	return shader;
}

void bind_shader(const shader_t& shader) {
	glUseProgram(shader.id);
}

void unbind_shader() {
	glUseProgram(0);
}

void shader_set_mat4(shader_t& shader, const char* var_name, const glm::mat4& mat) {
	glUseProgram(shader.id);
	unsigned int loc = glGetUniformLocation(shader.id, var_name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader_set_int(shader_t& shader, const char* var_name, const int val) {
	glUseProgram(shader.id);
	unsigned int loc = glGetUniformLocation(shader.id, var_name);
	glUniform1i(loc, val);
}

void shader_set_vec3(shader_t& shader, const char* var_name, const glm::vec3& v) {
	glUseProgram(shader.id);
	unsigned int loc = glGetUniformLocation(shader.id, var_name);
	glUniform3fv(loc, 1, glm::value_ptr(v));
}

glm::vec3 shader_get_vec3(const shader_t& shader, const char* var_name) {
	glm::vec3 v;
	unsigned int loc = glGetUniformLocation(shader.id, var_name);
	glGetUniformfv(shader.id, loc, &v[0]);
	return v;
}
