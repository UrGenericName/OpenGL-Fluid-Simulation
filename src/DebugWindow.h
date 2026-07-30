#pragma once

#include "imgui.h"
#include "Mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "Scene.h"
#include <chrono>
#include <fstream>
#include <filesystem>
#include <format>

#include "DebugSettings.h"

#define MAX_PARTICLE_RENDER_RADIUS 1.0f
#define MAX_CAGE_SIZE 16.0f

class DebugWindow {
public:

	DebugWindow(GLFWwindow* window);
	~DebugWindow();
	void drawImgui(Scene& scene);

private:

	void initImgui(GLFWwindow* window);

	void drawRenderTab(Scene& scene);
	void drawPhysicsTab(Scene& scene);
	void drawCageTab(Scene& scene);

	ImVec2 windowSize;
	ImVec2 windowPosition;

};