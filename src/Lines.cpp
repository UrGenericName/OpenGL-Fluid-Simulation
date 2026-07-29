#pragma once

#include "Lines.h"

#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Lines::Lines() {
	LineSetup();
}

Lines::Lines(Mesh& mesh) {

	LineSetup();
	generateFromBoundingBox(mesh);

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

	GLuint tintLoc = glGetUniformLocation(shader.ID, "u_tint");
	glUniform3f(tintLoc, tint.x, tint.y, tint.z);

	GLuint modelMatrixLoc = glGetUniformLocation(shader.ID, "u_modelMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));

	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

	VAO.Unbind();
}

void Lines::generateFromBoundingBox(Mesh& mesh) {

	vec3 minBounds{ INFINITY };
	vec3 maxBounds{ -INFINITY };

	// FETCH BOUNDS
	for (Vertex& vertex : mesh.vertices) {

		if (vertex.position.x < minBounds.x) minBounds.x = vertex.position.x;
		if (vertex.position.y < minBounds.y) minBounds.y = vertex.position.y;
		if (vertex.position.z < minBounds.z) minBounds.z = vertex.position.z;

		if (vertex.position.x > maxBounds.x) maxBounds.x = vertex.position.x;
		if (vertex.position.y > maxBounds.y) maxBounds.y = vertex.position.y;
		if (vertex.position.z > maxBounds.z) maxBounds.z = vertex.position.z;

	}

	// SET LINE VERTICES
	vertices = {
		LineVertex{ vec4(maxBounds.x, minBounds.y, minBounds.z, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minBounds.x, minBounds.y, minBounds.z, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxBounds.x, maxBounds.y, minBounds.z, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minBounds.x, maxBounds.y, minBounds.z, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxBounds.x, minBounds.y, maxBounds.z, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minBounds.x, minBounds.y, maxBounds.z, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxBounds.x, maxBounds.y, maxBounds.z, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minBounds.x, maxBounds.y, maxBounds.z, 0.0f),		vec4(1.0f) }
	};

	indices = {
		0, 1,
		2, 3,
		4, 5,
		6, 7,
		0, 2,
		0, 4,
		1, 3,
		1, 5,
		2, 6,
		3, 7,
		4, 6,
		5, 7
	};

	position = mesh.position;
	rotation = mesh.rotation;
	scale = mesh.scale;

}

void Lines::updateBuffers() {

	VBOptr->Update(vertices); // updates the vertices stored in the VBO
	EBOptr->Update(indices); // updates the indices stored in the EBO

}

mat4 Lines::getModelMatrix() {

	return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

mat4 Lines::getTranslationMatrix() {

	mat4 translationMatrix{
		1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,
		position.x,	position.y,	position.z,	1.0f
	};

	return translationMatrix;
}

mat4 Lines::getRotationMatrix() {

	float cosTheta, sinTheta;

	cosTheta = cos(rotation.x);
	sinTheta = sin(rotation.x);
	mat4 rotationX{
		1.0f,	0.0f,		0.0f,		0.0f,
		0.0f,	cosTheta,	sinTheta,	0.0f,
		0.0f,	-sinTheta,	cosTheta,	0.0f,
		0.0f,	0.0f,		0.0f,		1.0f
	};

	cosTheta = cos(rotation.y);
	sinTheta = sin(rotation.y);
	mat4 rotationY{
		cosTheta,	0.0f,	-sinTheta,	0.0f,
		0.0f,		1.0f,	0.0f,		0.0f,
		sinTheta,	0.0f,	cosTheta,	0.0f,
		0.0f,		0.0f,	0.0f,		1.0f,
	};

	cosTheta = cos(rotation.z);
	sinTheta = sin(rotation.z);
	mat4 rotationZ{
		cosTheta,	sinTheta,	0.0f,	0.0f,
		-sinTheta,	cosTheta,	0.0f,	0.0f,
		0.0f,		0.0f,		1.0f,	0.0f,
		0.0f,		0.0f,		0.0f,	1.0f
	};

	mat4 rotationMatrix{ rotationZ * rotationY * rotationX };

	return rotationMatrix;
}

mat4 Lines::getScaleMatrix() {

	mat4 scaleMatrix{
		scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		scale.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
	};

	return scaleMatrix;

}