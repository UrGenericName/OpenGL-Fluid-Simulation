#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Mesh.h"
#include "Camera.h"
#include "DebugSettings.h"
#include "LiquidSimComponent.h"

class Scene {
public:

	Shader* lineShader;
	Shader* shader;
	DebugSettings debugSettings;

	LiquidSimComponent liquidSimComponent;

	Camera& camera;

	std::vector<Mesh*> meshCollection;
	glm::vec3 backgroundColor = { 0.17f, 0.17f, 0.17f };

	Scene(Camera& i_camera);
	~Scene();

	void Draw(GLFWwindow* window);
	double getFrameTime() { return frameTime; }

private:

	double frameTime = 0;

	void Inputs(GLFWwindow* window);
	void setWindowTitle(GLFWwindow* window, double frameTime);

};