#include "helper.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "constants.h"

namespace helper {
	std::string get_file_contents(const char* path) {
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

	glm::vec2 ndc_to_screen(const glm::vec2 ndc) {
		glm::vec2 ndc_0_to_1 = (ndc + 1.0f) / 0.5f;
		return ndc_0_to_1 * glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	glm::vec2 screen_to_ndc(const glm::vec2 screen) {
		glm::vec2 normalized_screen = screen / glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
		glm::vec2 ndc = (normalized_screen * 2.0f) - 1.0f;
		return glm::vec2(ndc.x, -ndc.y);
	}

	glm::vec2 get_ttt_box_idx_from_ndc(glm::vec2 ndc, float wall_offset) {
		glm::vec2 tt(-1, -1);
		if (ndc.x <= -wall_offset && ndc.x >= -0.75f) {
			tt.x = 0;
		}
		else if (ndc.x >= -wall_offset && ndc.x <= wall_offset) {
			tt.x = 1;
		}
		else if (ndc.x >= wall_offset && ndc.x <= 0.75f) {
			tt.x = 2;
		}

		if (ndc.y <= -wall_offset && ndc.y >= -0.75f) {
			tt.y = 2;
		}
		else if (ndc.y >= -wall_offset && ndc.y <= wall_offset) {
			tt.y = 1;
		}
		else if (ndc.y >= wall_offset && ndc.y <= 0.75f) {
			tt.y = 0;
		}

		return tt;
	}

	glm::vec3 get_ttt_box_ndc_from_idx(glm::vec2 idx) {
		glm::vec2 pos(0.f, 0.f);
		if (idx.x == 0) {
			pos.x = -0.5f;
		}
		else if (idx.x == 1) {
			pos.x = 0.f;
		}
		else {
			pos.x = 0.5f;
		}

		if (idx.y == 0) {
			pos.y = 0.5f;
		}
		else if (idx.y == 1) {
			pos.y = 0.f;
		}
		else {
			pos.y = -0.5f;
		}
		return glm::vec3(pos.x, pos.y, 0.f);
	}

	finish_state_t is_game_over(int state[3][3]) {
		finish_state_t finish_state{};
		for (int row = 0; row < 3; row++) {
			if (state[row][0] == state[row][1] && state[row][1] == state[row][2]) {
				finish_state.winner = state[row][0];
				finish_state.start_ttt_idx = glm::vec2(0, row);
				finish_state.end_ttt_idx = glm::vec2(2, row);
				return finish_state;
			}
		}
		for (int col = 0; col < 3; col++) {
			if (state[0][col] == state[1][col] && state[0][col] == state[2][col]) {
				finish_state.winner = state[0][col];
				finish_state.start_ttt_idx = glm::vec2(col, 0);
				finish_state.end_ttt_idx = glm::vec2(col, 2);
				return finish_state;
			}
		}
		if (state[0][0] == state[1][1] && state[1][1] == state[2][2]) {
			finish_state.winner = state[0][0];
			finish_state.start_ttt_idx = glm::vec2(0, 0);
			finish_state.end_ttt_idx = glm::vec2(2, 2);
			return finish_state;
		}
		if (state[2][0] == state[1][1] && state[2][0] == state[0][2]) {
			finish_state.winner = state[2][0];
			finish_state.start_ttt_idx = glm::vec2(2, 0);
			finish_state.end_ttt_idx = glm::vec2(0, 2);
			return finish_state;
		}
		return finish_state;
	}

	float dot_product(glm::vec3 v1, glm::vec3 v2) {
		v1 = glm::normalize(v1);
		v2 = glm::normalize(v2);
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}
}

/*
std::string vec3Str(glm::vec3 v) {
	return std::to_string(v.x) + " " + std::to_string(v.y) + " " + std::to_string(v.z);
}

static std::vector<EBO> storedEbos;

void addEBO(EBO& ebo) {
	storedEbos.push_back(ebo);
}

void getAllEBOVerts() {
	for (EBO& ebo : storedEbos) {
		std::array<int, 6> vertsIdxs = ebo.getVertices();
		std::cout << "EBO " << ebo.id << ": ";
		for (int i = 0; i < 6; i++) {
			std::cout << vertsIdxs[i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n--------------------------------" << std::endl;
}
*/
