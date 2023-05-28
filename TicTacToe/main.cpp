#include <iostream>
#include "SDL.h"
#include "texture.h"
#include "glad/glad.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "vertex.h"
#include "ebo.h"
#include "transform.h"
#include "rectangle.h"
#include "cross.h"
#include <vector>
#include <array>
#include <cmath>
#include "circle.h"
#include "helper.h"
#include "globals.h"
#include "constants.h"
#include "enums.h"
#include "init.h"

extern globals_t globals;

/*
glm::vec2 ndcToScreen(glm::vec2 ndc) {
	glm::vec2 ndc_0_to_1 = (ndc + 1.0f) / 0.5f;
	return ndc_0_to_1 * glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
}

glm::vec2 screenToNdc(glm::vec2 screen) {
	screen = screen / glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	glm::vec2 ndc = (screen * 2.0f) - 1.0f;
	return glm::vec2(ndc.x, -ndc.y);
}

glm::vec2 ticTacToeBox(glm::vec2 ndc, float wallOffset) {
	glm::vec2 tt(-1, -1);
	if (ndc.x <= -wallOffset && ndc.x >= -0.75f) {
		tt.x = 0;
	}
	else if (ndc.x >= -wallOffset && ndc.x <= wallOffset) {
		tt.x = 1;
	}
	else if (ndc.x >= wallOffset && ndc.x <= 0.75f) {
		tt.x = 2;
	}

	if (ndc.y <= -wallOffset && ndc.y >= -0.75f) {
		tt.y = 2;
	}
	else if (ndc.y >= -wallOffset && ndc.y <= wallOffset) {
		tt.y = 1;
	}
	else if (ndc.y >= wallOffset && ndc.y <= 0.75f) {
		tt.y = 0;
	}

	return tt;
}

glm::vec3 getTicTacToeSquarePos(glm::vec2 tts) {
	glm::vec2 pos(0.f, 0.f);
	if (tts.x == 0) {
		pos.x = -0.5f;
	}
	else if (tts.x == 1) {
		pos.x = 0.f;
	}
	else {
		pos.x = 0.5f;
	}

	if (tts.y == 0) {
		pos.y = 0.5f;
	}
	else if (tts.y == 1) {
		pos.y = 0.f;
	}
	else {
		pos.y = -0.5f;
	}
	return glm::vec3(pos.x, pos.y, 0.f);
}
*/

/*
struct FinishLine {
	int winner;
	glm::vec2 startTT;
	glm::vec2 endTT;
};

FinishLine isGameOver(int state[3][3]) {
	FinishLine finishLine{};
	for (int row = 0; row < 3; row++) {
		if (state[row][0] == state[row][1] && state[row][1] == state[row][2]) {
			finishLine.winner = state[row][0];
			finishLine.startTT = glm::vec2(0, row);
			finishLine.endTT = glm::vec2(2, row);
			return finishLine;
		}
	}
	for (int col = 0; col < 3; col++) {
		if (state[0][col] == state[1][col] && state[0][col] == state[2][col]) {
			finishLine.winner = state[0][col];
			finishLine.startTT = glm::vec2(col, 0);
			finishLine.endTT = glm::vec2(col, 2);
			return finishLine;
		}
	}
	if (state[0][0] == state[1][1] && state[1][1] == state[2][2]) {
		finishLine.winner = state[0][0];
		finishLine.startTT = glm::vec2(0, 0);
		finishLine.endTT = glm::vec2(2, 2);
		return finishLine;
	}
	if (state[2][0] == state[1][1] && state[2][0] == state[0][2]) {
		finishLine.winner = state[2][0];
		finishLine.startTT = glm::vec2(2, 0);
		finishLine.endTT = glm::vec2(0, 2);
		return finishLine;
	}
	return finishLine;
}
*/

/*
float getDotProduct(glm::vec3 v1, glm::vec3 v2) {
	v1 = glm::normalize(v1);
	v2 = glm::normalize(v2);
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

void printCrosses(std::vector<Cross>& placedCrosses) {
	for (Cross& cross : placedCrosses)
	{
		std::cout << "left diag ebo id: " << cross.leftDiag.ebo.id << "   right diag ebo id: " << cross.rightDiag.ebo.id << std::endl;
	}
	std::cout << "-------------------------" << std::endl;
}

void printOutlineCircles(std::vector<OutlineCircle>& placedCircles) {
	for (OutlineCircle& circle : placedCircles)
	{
		std::cout << "circle ebo id: " << circle.ebo.id << std::endl;
	}
	std::cout << "-------------------------" << std::endl;
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}
*/


int main(int argc, char** argv) {
	

	// int winWidth = 600;
	// int winHeight = 600;

	int state[3][3]{};		
	/*
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	glDebugMessageCallback(MessageCallback, 0);
	*/

	init();

	std::vector<rectangle_t> rectangles;
	setup_board_objects(rectangles);

	Texture texture("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\smiley_face.jpg");
	/*
	float offset = 0.25f;
	float shorterScale = 0.035f;
	glm::vec3 wallColor = glm::vec3(13, 161, 146) / 255.f;
	Rectangle leftWall(glm::vec3(-offset, 0.0f, 0.0f), glm::vec3(shorterScale, 1.5f, 0.0f), 0.0f, wallColor);
	Rectangle rightWall(glm::vec3(offset, 0.0f, 0.0f), glm::vec3(shorterScale, 1.5f, 0.0f), 0.0f, wallColor);
	Rectangle topWall(glm::vec3(0.f, offset, 0.0f), glm::vec3(shorterScale, 1.5f, 0.0f), 90.0f, wallColor);
	Rectangle bottomWall(glm::vec3(0.0f, -offset, 0.0f), glm::vec3(shorterScale, 1.5f, 0.0f), 90.0f, wallColor);
	*/

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Cross tempCross;
	// OutlineCircle tempCircle(64, 0.18f, 0.2f, glm::vec3(1.f, 0.f, 0.f));

	// tempCross.setColor(glm::vec3(1.f, 0.f, 0.f));

	// FilledCircle o(64, 0.2f, glm::vec3(0.9f, 0.9f, 0.9f));

	/*
	std::vector<Cross> placedCrosses;
	std::vector<OutlineCircle> placedCircles;
	*/

	PLAYER player = PLAYER::ONE;

	bool running = true;
	bool mouse_button_up = false;
	bool game_over = false;
	bool space = false;
	bool pPressed = false;

	cross_t temp_cross = create_cross(glm::vec3(0), glm::vec3(1.f), glm::vec3(1, 0, 0));
	ouline_circle_t temp_circle = create_outline_circle(glm::vec3(0), glm::vec3(1.f), 0.f, glm::vec3(1, 0, 0));

	std::vector<cross_t> placed_crosses;
	std::vector<ouline_circle_t> placed_circles;

	// Rectangle finishline;
	rectangle_t finish_line;

	// Shader shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	// shader.setVec3("color", glm::vec3(1, 1, 0));

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (running) {
		mouse_button_up = false;
		pPressed = false;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(globals.window)) {
				running = false;
			}
			switch (event.type) {
			case SDL_QUIT: {
				running = false;
			}
						 break;
			case SDL_MOUSEBUTTONUP: {
				mouse_button_up = true;
			}
								  break;
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_SPACE: {
					space = true;
					break;
				}
				case SDLK_p: {
					pPressed = true;
					break;
				}
				default:
					break;
				}
			}
							break;
			}
		}

		glm::vec3 bck_color = glm::vec3(20, 189, 172) / 255.f;
		glClearColor(bck_color.x, bck_color.y, bck_color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.bind();

		for (const rectangle_t& rectangle : rectangles) {
			draw_rectangle(rectangle);
		}

		/*
		leftWall.draw();
		rightWall.draw();
		topWall.draw();
		bottomWall.draw();

		if (player == ONE) {
			tempCross.draw();
		}
		else {
			tempCircle.draw();
		}

		for (OutlineCircle& circle : placedCircles)
		{
			circle.draw();
		}

		for (Cross& cross : placedCrosses)
		{
			// cross.draw();
			// shader.setMat4("model", cross.leftDiag.transform.getModelMatrix());
			// cross.leftDiag.vao.bind();

			tempCross.leftDiag.vao.bind();
			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempCross.leftDiag.ebo.id);
			// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			// glDrawElements(GL_TRIANGLES, cross.leftDiag.ebo.numIndicies, GL_UNSIGNED_INT, 0);

			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			// const auto& indiciesL = cross.leftDiag.ebo.getVertices();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			tempCross.leftDiag.vao.unbind();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// shader.setMat4("model", cross.rightDiag.transform.getModelMatrix());
			// cross.rightDiag.vao.bind();
			tempCross.rightDiag.vao.bind();
			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempCross.rightDiag.ebo.id);
			// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			// glDrawElements(GL_TRIANGLES, cross.rightDiag.ebo.numIndicies, GL_UNSIGNED_INT, 0);

			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			// const auto& indiciesR = cross.rightDiag.ebo.getVertices();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			tempCross.rightDiag.vao.unbind();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		}

		if (gameOver) {
			placedCrosses[0].draw();
			placedCrosses[1].draw();
			placedCrosses[2].draw();
		}
		*/

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		glm::vec2 ndc = helper::screen_to_ndc(glm::vec2(mouseX, mouseY));
		float offset = 0.25f;
		glm::vec2 mouse_over_idx = helper::get_ttt_box_idx_from_ndc(ndc, offset);

		if (player == PLAYER::ONE) {
			temp_cross.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
			draw_cross(temp_cross);
		}
		else {
			temp_circle.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
			draw_outline_circle(temp_circle);
		}

		if (mouse_button_up) {
			if (player == ONE) {
				placed_crosses.push_back(temp_cross);
				cross_t& new_cross = placed_crosses[placed_crosses.size() - 1];
				new_cross.color = glm::vec3(0.37f);
				player = TWO;
				state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = ONE;
			}
			else {
				placed_circles.push_back(temp_circle);
				ouline_circle_t& new_circle = placed_circles[placed_circles.size() - 1];
				new_circle.color = glm::vec3(1, 1, 1);
				player = ONE;
				state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = TWO;
			}
		}

		for (const cross_t& cross : placed_crosses) {
			draw_cross(cross);
		}

		for (const ouline_circle_t& circle : placed_circles) {
			draw_outline_circle(circle);
		}

		finish_state_t finish_state = helper::is_game_over(state);
		if (!game_over && finish_state.winner != 0) {
			glm::vec3 start_pos = helper::get_ttt_box_ndc_from_idx(finish_state.start_ttt_idx);
			glm::vec3 end_pos = helper::get_ttt_box_ndc_from_idx(finish_state.end_ttt_idx);
			float distance = glm::length(end_pos - start_pos);

			glm::vec3 pos = (start_pos + end_pos) / 2.0f;
			glm::vec3 scale(distance * 1.15f, 0.025f, 1.f);
			glm::vec3 relPos = end_pos - start_pos;
			float dX = helper::dot_product(relPos, glm::vec3(1.0f, 0.f, 0.f));
			float dY = helper::dot_product(relPos, glm::vec3(0.0f, 1.f, 0.f));
			float rotation = (dY >= 0.f ? 1.f : -1.f) * glm::degrees(acosf(dX));
			finish_line = create_rectangle(pos, scale, rotation, glm::vec3(0.8f));
			game_over = true;
		}

		if (game_over) {
			draw_rectangle(finish_line);
		}

		SDL_GL_SwapWindow(globals.window);
	}

	return -1;
}