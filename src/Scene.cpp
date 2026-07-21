#pragma once

#include "Scene.h"

#include <iostream>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <format>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace std;
using namespace std::chrono;

Scene::Scene(Camera& i_camera) : camera(i_camera) {}

Scene::~Scene() {}

void Scene::Draw(GLFWwindow* window) {

	auto start = high_resolution_clock::now();

	Inputs(window);

	if (!debugSettings.pause) {

		// CLEAR BACKGROUND
		glViewport(0, 0, camera.width, camera.height);
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shaderPipelineComponent.Draw(liquidSimComponent, camera);

	}

	auto end = high_resolution_clock::now();
	auto raw_duration = end - start;
	duration<double, milli> ms_double = raw_duration;
	frameTime = ms_double.count();

	// WINDOW NAME
	setWindowTitle(window, frameTime);

}

void Scene::setWindowTitle(GLFWwindow* window, double frameTime) {

	string windowName = "Liquid Simulation   FPS: " + (to_string(static_cast<int>(1000 / frameTime)) + "      ").substr(0, 6) + "\t";

	glfwSetWindowTitle(window, windowName.c_str());

}

void Scene::Inputs(GLFWwindow* window) {

	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.Position += camera.speed * camera.Orientation;	// move position foward from orientation
	}

	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.Position += camera.speed * -glm::normalize(glm::cross(camera.Orientation, camera.Up)); // find the left vector from orientation and add to position
	}

	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.Position += camera.speed * -camera.Orientation;	// move position backward from orientation
	}

	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.Position += camera.speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));	// find the right vector from orientation and add to position
	}

	// UP & DOWN (space, ctrl)
	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.Position += camera.speed * camera.Up;
	}
	if (!debugSettings.usingDebugWindow && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera.Position += camera.speed * -camera.Up;
	}

	// MOUSE MOVEMENT
	static bool firstClick = true;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (camera.width / 2), (camera.height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = camera.sensitivity * (float)(mouseY - (camera.height / 2)) / camera.height;
		float rotY = camera.sensitivity * (float)(mouseX - (camera.width / 2)) / camera.width;

		glm::vec3 newOrientation = glm::rotate(camera.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.Orientation, camera.Up)));

		if (!((glm::angle(newOrientation, camera.Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -camera.Up) <= glm::radians(5.0f)))) {

			camera.Orientation = newOrientation;

		}

		camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-rotY), camera.Up);

		glfwSetCursorPos(window, (float(camera.width) / 2), (float(camera.height) / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}



	// SPEED UP (SHIFT)
	static bool speedUp = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

		if (!speedUp) {		// speedUp check prevents the speed from continuously increasing every frame
			camera.speed *= 2;
			speedUp = true;
		}

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {

		if (speedUp) {		// speedUp check prevents the speed from continuously decreasing every frame
			camera.speed /= 2;
			speedUp = false;
		}

	}

}