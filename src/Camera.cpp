#pragma once

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(unsigned int i_width, unsigned int i_height, glm::vec3 i_position) : width(i_width), height(i_height), Position(i_position) {};

Camera& Camera::operator=(Camera other) {

	Position = other.Position;
	Orientation = other.Orientation;

	width = other.width;
	height = other.height;

	FOVdeg = other.FOVdeg;
	nearPlane = other.nearPlane;
	farPlane = other.farPlane;

	speed = other.speed;
	sensitivity = other.sensitivity;

	cameraMatrix = other.cameraMatrix;

	return *this;

}

void Camera::updateMatrix(Shader& shader) {

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	cameraMatrix = projection * view;

	shader.Activate();
	GLuint u_camMatrixLoc = glGetUniformLocation(shader.ID, "u_camMatrix");
	glUniformMatrix4fv(u_camMatrixLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	GLuint u_nearPlaneLoc = glGetUniformLocation(shader.ID, "u_nearPlane");
	glUniform1f(u_nearPlaneLoc, nearPlane);

	GLuint u_farPlaneLoc = glGetUniformLocation(shader.ID, "u_farPlane");
	glUniform1f(u_farPlaneLoc, farPlane);

}

glm::mat4 Camera::getMatrix() {
	return cameraMatrix;
}