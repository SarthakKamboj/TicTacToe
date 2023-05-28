#include "ebo.h"
#include <vector>
#include <iostream>
#include "helper.h"
#include "globals.h"

// extern Globals globals;
/*
EBO::EBO(unsigned int* indicies, int sizeOfBuffer) {
	numIndicies = sizeOfBuffer / sizeof(indicies[0]);
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfBuffer, indicies, GL_STATIC_DRAW);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	addEBO(*this);
}

EBO::EBO() {
	id = 0;
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::array<int, 6> EBO::getVertices() {
	std::array<int, 6> readData;
	std::array<unsigned int, 6> tempData;
	if (numIndicies == 6) {
		// unsigned int readData[6]{};
		bind();
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndicies * sizeof(unsigned int), tempData.data());
		for (int i = 0; i < 6; i++) {
			readData[i] = (int)tempData[i];
		}
		unbind();
	}
	else {
		for (int i = 0; i < 6; i++) {
			readData[i] = -1;
		}
	}
	return readData;
}
*/

ebo_t create_ebo(const unsigned int* indicies, const int size_of_buffer) {
	ebo_t ebo;
	ebo.numIndicies = size_of_buffer / sizeof(indicies[0]);
	glGenBuffers(1, &ebo.id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_buffer, indicies, GL_STATIC_DRAW);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ebo;
}

void bind_ebo(const ebo_t& ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.id);
}

void unbind_ebo() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
