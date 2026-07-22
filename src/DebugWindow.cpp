#pragma once

#include "DebugWindow.h"

using namespace ImGui;
using namespace std;

DebugWindow::DebugWindow(GLFWwindow* window) { initImgui(window); }

DebugWindow::~DebugWindow() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}

void DebugWindow::initImgui(GLFWwindow* window) {

	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& io = GetIO();
	(void)io;
	StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

}

void DebugWindow::drawImgui(Scene& scene) {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	scene.debugSettings.usingDebugWindow = GetIO().WantCaptureMouse;

	if (IsKeyPressed(ImGuiKey_Tab)) scene.debugSettings.drawWindow = !scene.debugSettings.drawWindow;

	if (!scene.debugSettings.drawWindow) { EndFrame();  return; }


	// DRAW WINDOW
	Begin("Debug");
	Separator();

	double frameTime = scene.getFrameTime();
	Text("FT(ms): %.3f\t\tFPS: %d", frameTime, static_cast<int>(1000 / frameTime));

	drawRenderTab(scene);

	End();

	windowSize = GetWindowSize();
	windowPosition = GetWindowPos();

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

}

void DebugWindow::drawRenderTab(Scene& scene) {

	if (BeginTable("ShaderLayoutTable", 1)) {

		TableSetupColumn("Physics Settings");
		TableHeadersRow();

		float width = scene.liquidSimComponent.getWidth();
		float length = scene.liquidSimComponent.getLength();
		float height = scene.liquidSimComponent.getHeight();

		TableNextRow();
		TableNextColumn();
		if (SliderFloat("Width", &width, 0.0f, MAX_CAGE_SIZE)) scene.liquidSimComponent.Resize(width, length, height);

		TableNextRow();
		TableNextColumn();
		if (SliderFloat("Length", &length, 0.0f, MAX_CAGE_SIZE)) scene.liquidSimComponent.Resize(width, length, height);

		TableNextRow();
		TableNextColumn();
		if (SliderFloat("Height", &height, 0.0f, MAX_CAGE_SIZE)) scene.liquidSimComponent.Resize(width, length, height);

		EndTable();
	}

}