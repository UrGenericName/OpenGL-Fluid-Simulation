#pragma once

#include "Lines.h"

Lines::Lines() {
	LineSetup();
}

Lines::~Lines() {}

void Lines::LineSetup() {

	// VAO (vertex array object) stores the configuration settings for vertex attributes (what each value might mean, how long a vertex is etc.)
	VAO.Bind();

	// VBO (vertex buffer object) allocates bytes for the vertex data in VRAM
	VBOptr = new VBO_line(vertices);

	// EBO (element buffer object) allocates bytes for the indices in VRAM (tells OpenGL which vertices need to be connected together to form a triangle)
	EBOptr = new EBO(indices);

	//			POS		  COLOR		NORMAL      UV
	// VAO : [x, y, z,   r, g, b,   x, y, z,   u, v,]
	VAO.LinkAttribute(*VBOptr, 0, 3, GL_FLOAT, sizeof(LineVertex), (void*)0);	// defines the position (x, y, z, 0.0f); 4 floats with an offset of 0
	VAO.LinkAttribute(*VBOptr, 1, 3, GL_FLOAT, sizeof(LineVertex), (void*)(4 * sizeof(float)));	// defines the color (r, g, b, 0.0f); 4 floats with an offset of 4 floats

	// Unbind them, since the constructor binds them automatically
	VAO.Unbind();
	(*VBOptr).Unbind();
	(*EBOptr).Unbind();

}

void Lines::Draw(Shader& shader) {

	shader.Activate();
	VAO.Bind();

	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

	VAO.Unbind();
}

void Lines::updateBuffers() {

	VBOptr->Update(vertices); // updates the vertices stored in the VBO
	EBOptr->Update(indices); // updates the indices stored in the EBO

}