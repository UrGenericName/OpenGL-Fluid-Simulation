#pragma once

#include "DebugWindow.h"

using namespace ImGui;
using namespace std;
using namespace glm;

#define PI 3.14159

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
	drawPhysicsTab(scene);
	drawCageTab(scene);

	End();

	windowSize = GetWindowSize();
	windowPosition = GetWindowPos();

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

}

void DebugWindow::drawRenderTab(Scene& scene) {

	// RENDER SETTINGS
	if (BeginTable("ShaderLayoutTable", 2)) {

		TableSetupColumn("Render Settings");
		TableHeadersRow();

		TableNextRow();
		TableNextColumn();
		SliderFloat("Particle Radius", &scene.fluidSimComponent.shaderPipelineComponent.particleRenderRadius, 0.0f, MAX_PARTICLE_RENDER_RADIUS);

		EndTable();
	}

}

void DebugWindow::drawPhysicsTab(Scene& scene) {

	// PHYSICS SETTINGS
	if (BeginTable("ShaderLayoutTable", 3)) {

		TableSetupColumn("Physics Settings");
		TableHeadersRow();

		TableNextRow();
		TableNextColumn();
		if (Button( !scene.fluidSimComponent.physicsPlay ? "Play" : "Pause" )) scene.fluidSimComponent.physicsPlay = !scene.fluidSimComponent.physicsPlay;
		TableNextColumn();
		if (Button("Reset")) {
			scene.fluidSimComponent.FillInnerCage();  
			scene.fluidSimComponent.physicsPlay = false;
		}

		TableNextColumn();
		float particleDensity = scene.fluidSimComponent.GetParticleDensity();
		if (SliderFloat("Particle Density", &particleDensity, MIN_PARTICLE_DENSITY, MAX_PARTICLE_DENSITY)) scene.fluidSimComponent.SetParticleDensity(particleDensity);


		EndTable();
	}

}

void DebugWindow::drawCageTab(Scene& scene) {

	// INNER CAGE
	if (BeginTable("ShaderLayoutTable", 3)) {

		TableSetupColumn("Inner Cage");
		TableHeadersRow();

		vec3 innerCagePos = scene.fluidSimComponent.GetInnerCagePos();
		vec3 innerCageRot = scene.fluidSimComponent.GetInnerCageRot();
		vec3 innerCageSize = scene.fluidSimComponent.GetInnerCageSize();

		TableNextRow();
		TableNextColumn();
		if (DragFloat("X##Inner_Cage_X", &innerCagePos.x, 0.1f, -MAX_CAGE_SIZE / 2.0f, MAX_CAGE_SIZE / 2.0f)) scene.fluidSimComponent.SetInnerCagePos(innerCagePos);
		TableNextColumn();
		if (DragFloat("Y##Inner_Cage_Y", &innerCagePos.y, 0.1f, -MAX_CAGE_SIZE / 2.0f, MAX_CAGE_SIZE / 2.0f)) scene.fluidSimComponent.SetInnerCagePos(innerCagePos);
		TableNextColumn();
		if (DragFloat("Z##Inner_Cage_Z", &innerCagePos.z, 0.1f, -MAX_CAGE_SIZE / 2.0f, MAX_CAGE_SIZE / 2.0f)) scene.fluidSimComponent.SetInnerCagePos(innerCagePos);

		TableNextRow();
		TableNextColumn();
		if (DragFloat("Pitch##Inner_Cage_Pitch", &innerCageRot.x, PI / 16.0f)) scene.fluidSimComponent.SetInnerCageRot(innerCageRot);
		TableNextColumn();
		if (DragFloat("Yaw##Inner_Cage_Yaw", &innerCageRot.y, PI / 16.0f)) scene.fluidSimComponent.SetInnerCageRot(innerCageRot);
		TableNextColumn();
		if (DragFloat("Roll##Inner_Cage_Roll", &innerCageRot.z, PI / 16.0f)) scene.fluidSimComponent.SetInnerCageRot(innerCageRot);

		TableNextRow();
		TableNextColumn();
		if (SliderFloat("Width##Inner_Cage_Width", &innerCageSize.x, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize);
		TableNextColumn();
		if (SliderFloat("Length##Inner_Cage_Length", &innerCageSize.y, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize);
		TableNextColumn();
		if (SliderFloat("Height##Inner_Cage_Height", &innerCageSize.z, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeInnerCage(innerCageSize);

		EndTable();
	}

	// OUTER CAGE
	if (BeginTable("ShaderLayoutTable", 3)) {

		TableSetupColumn("Outer Cage");
		TableHeadersRow();

		vec3 outerCageSize = scene.fluidSimComponent.GetOuterCageSize();

		TableNextRow();
		TableNextColumn();
		if (SliderFloat("Width##Outer_Cage_Width", &outerCageSize.x, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize);
		TableNextColumn();
		if (SliderFloat("Length##Outer_Cage_Length", &outerCageSize.y, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize);
		TableNextColumn();
		if (SliderFloat("Height##Outer_Cage_Height", &outerCageSize.z, 0.0f, MAX_CAGE_SIZE)) scene.fluidSimComponent.ResizeOuterCage(outerCageSize);

		EndTable();
	}

}