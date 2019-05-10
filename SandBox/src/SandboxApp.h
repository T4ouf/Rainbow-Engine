#pragma once
#include "Rainbow.h"

class Sandbox : public Rainbow::Application {

private:
	Rainbow::Material* Gold;
	Rainbow::Material* Ruby;
	Rainbow::Material* Chrome;
	Rainbow::Material* Pearl;
	Rainbow::Material* Copper;
	Rainbow::Material* Obsidian;
	Rainbow::Material* BlackRubber;
	Rainbow::Material* LampMaterial;


	Rainbow::Scene* m_scene;

	Rainbow::Material* m_Material;

	Rainbow::Texture* m_Texture;

	//Création du shader
	Rainbow::Shader* m_Shader;

	Rainbow::Force* m_gravite;
	Rainbow::Force* m_reverseGravity;


	float deltaTime;
	double lastFrame;

	int frameNumber;

	Rainbow::Object* m_player;

	void ProcessInputCamera(GLFWwindow *window);

	float r;
	float g;
	float b;

	float incR;
	float incB;
	float incG;

public:

	Sandbox();
	~Sandbox();

	void OnUpdate(float delta) override;
	void OnRender() override;
	void OnImGuiRender() override;

};

//Defining entry point of the program
Rainbow::Application* Rainbow::CreateApplication() {
	return new Sandbox();
}
