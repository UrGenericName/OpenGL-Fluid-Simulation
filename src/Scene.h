#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Mesh.h"
#include "Camera.h"
#include "DebugSettings.h"
#include "LiquidSimComponent.h"
#include "ShaderPipelineComponent.h"

class Scene {
public:

	LiquidSimComponent liquidSimComponent;

	DebugSettings debugSettings;

	Camera& camera;
	glm::vec3 backgroundColor = { 0.17f, 0.17f, 0.17f };

	Scene(Camera& i_camera);
	~Scene();

	void Draw(GLFWwindow* window);
	double getFrameTime() { return frameTime; }

private:

	double frameTime = 0;

	void setWindowTitle(GLFWwindow* window, double frameTime);
	void Inputs(GLFWwindow* window);

};