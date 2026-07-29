#pragma once

#include "DebugWindow.h"

using namespace ImGui;
using namespace std;
using namespace glm;

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

	if (BeginTable("ShaderLayoutTable", 4)) {

		TableSetupColumn("Type");
		TableSetupColumn("x");
		TableSetupColumn("y");
		TableSetupColumn("z");
		TableHeadersRow();
	

		// INNER CAGE
		TableNextRow();
		TableNextColumn();
		Text("Inner Cage");
		TableNextColumn();

		vec3 innerCageSize = scene.fluidSimComponent.getInnerCageSize();

		if (SliderFloat("##Inner_Cage_Width", &innerCageSize.x, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize.x, innerCageSize.y, innerCageSize.z);
		TableNextColumn();
		if (SliderFloat("##Inner_Cage_Length", &innerCageSize.y, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize.x, innerCageSize.y, innerCageSize.z);
		TableNextColumn();
		if (SliderFloat("##Inner_Cage_Height", &innerCageSize.z, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize.x, innerCageSize.y, innerCageSize.z);


		// OUTER CAGE
		TableNextRow();
		TableNextColumn();
		Text("Outer Cage");
		TableNextColumn();

		vec3 outerCageSize = scene.fluidSimComponent.getOuterCageSize();

		if (SliderFloat("##Outer_Cage_Width", &outerCageSize.x, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize.x, outerCageSize.y, outerCageSize.z);
		TableNextColumn();
		if (SliderFloat("##Outer_Cage_Length", &outerCageSize.y, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize.x, outerCageSize.y, outerCageSize.z);
		TableNextColumn();
		if (SliderFloat("##Outer_Cage_Height", &outerCageSize.z, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize.x, outerCageSize.y, outerCageSize.z);



		EndTable();
	}

}