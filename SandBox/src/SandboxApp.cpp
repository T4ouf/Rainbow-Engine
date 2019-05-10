#include "SandboxApp.h"
#include "Rainbow.h"
#include "Parseur.h"
#include <iostream>
#include <chrono>
#include <thread>

Rainbow::Object* player;
	
Rainbow::Force* forwardForce;
Rainbow::Force* rightForce	;
Rainbow::Force* upForce		;

Rainbow::Object* platform;

glm::vec3 oldCameraPosition;

float JUMP_COOLDOWN;
float timeOfLastJump;

bool isSprinting;
bool canJump;

void jump() {
	if (canJump) {
		player->addForce(new Rainbow::Force(*upForce));
		timeOfLastJump = glfwGetTime();
		canJump = false;
	}
}
Rainbow::ButtonFunction jumpCallback = jump;

void movement(float value) {
	if (isSprinting)
		value = value * 2.0f;
	player->addForce(new Rainbow::Force(rightForce->MultiplyByScalar(value)));
}
Rainbow::AnalogButtonFunction sideMovement = movement;

void teleportation() {
	if (player->getPosition().y + 150.0f <= 850.0f)
		player->translate(glm::vec3(0.0f, 150.0f, 0.0f));
}

Rainbow::ButtonFunction teleportationCallback = teleportation;

void sprint() {
	isSprinting = !isSprinting;
}
Rainbow::ButtonFunction sprintCallback = sprint;


Sandbox::Sandbox(){
	std::cout << "In Sandbox Application !\n";
	m_soundManager->launchSound("Ressources/SoundSamples/Music/And So It Begins.wav", "MusicBG", true);

	player = m_player;

	forwardForce = new Rainbow::Force(glm::vec3(0.0f, 0.0f, -0.5f));
	rightForce = new Rainbow::Force(glm::vec3(0.4f, 0.0f, 0.0f));
	upForce = new Rainbow::Force(glm::vec3(0.0f, 1.5f, 0.0f));
	oldCameraPosition = glm::vec3(0.0f);

	JUMP_COOLDOWN = 1.0f;
	timeOfLastJump = 0.0f;

	isSprinting = false;
	canJump = true;
	
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;

	incR = 0.003f;
	incB = 0.003f;
	incG = 0.003f;

	deltaTime = 0.0f;
	lastFrame = 0.0;
	frameNumber = 0;

	glm::vec3 gravityDirection(0.0f, -0.0981f, 0.0f);
	m_gravite = new Rainbow::Force(gravityDirection);
	m_reverseGravity = new Rainbow::Force(gravityDirection*-1.0f);

	//On autorise et paramètre la transparence
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//On active le test de profondeur (z-buffer test)
	glEnable(GL_DEPTH_TEST);
	//On accepte que les pixels qui sont devant (les autres ne seront pas dessinés par dessus)
	glDepthFunc(GL_LESS);

	m_Shader = new Rainbow::Shader("Ressources/Shaders/Material.shader");


	// Material creation
	Gold = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.329412f, 0.223529f, 0.027451f),
		glm::vec3(0.780392f, 0.568627f, 0.113725f),
		glm::vec3(0.992157f, 0.941176f, 0.807843f), 27.8974f);

	Ruby = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.1745f, 0.01175f, 0.01175f),
		glm::vec3(0.61424f, 0.04136f, 0.04136f),
		glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f * 128);

	Chrome = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.25f, 0.25f, 0.25f),
		glm::vec3(0.4f, 0.4f, 0.4f),
		glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f * 128);

	Pearl = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.25f, 0.20725f, 0.20725f),
		glm::vec3(1.0f, 0.829f, 0.829f),
		glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f * 128);

	Copper = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.19125f, 0.0735f, 0.0225f),
		glm::vec3(0.7038f, 0.27048f, 0.0828f),
		glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f * 128);

	Obsidian = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.05375f, 0.05f, 0.06625f),
		glm::vec3(0.18275f, 0.17f, 0.22525f),
		glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f * 128);

	BlackRubber = new Rainbow::Material(m_Shader, nullptr,
		glm::vec3(0.02f, 0.02f, 0.02f),
		glm::vec3(0.01f, 0.01f, 0.01f),
		glm::vec3(0.4f, 0.4f, 0.4f), 10.0f);

	LampMaterial = new Rainbow::Material(Rainbow::LightSourceShader, "Ressources/Textures/texture-caisse.png",
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

	m_Material = Gold;

	m_scene = new Rainbow::Scene();

	Parseur p = Parseur("Ressources/Xml/level1.xml");

	Rainbow::Scene& sceneRef = *m_scene;
	Level lvl = p.parse(sceneRef);

	//Object* Platform = ObjectFactory::CreateCube(glm::vec3(0.0f, 0.0f, 0.0f), 850, 150, true, m_Material);
	Rainbow::Object* Boxe = Rainbow::ObjectFactory::CreateCube(glm::vec3(0.0f, 0.0f, 0.0f), 20, 15, false, Ruby);
	m_player = Boxe;
	m_player->SetBounceCoeff(0.0);
	m_player->setPosition(lvl.startPosX, lvl.startPosY, lvl.startPosZ);
	//platform = Platform;

	Rainbow::Light& l = m_scene->retrieveLight();
	l.m_intensity = 5000;
	l.setPosition(0, 175, 300);

	Rainbow::Object* Lamp = Rainbow::ObjectFactory::CreateCube(l.getPosition(), 25, 1, true, LampMaterial);
	//Lamp->translate(glm::vec3(150.0f, 150.0f, -175.0f));

	Rainbow::Camera& camera = m_scene->retrieveCamera();
	camera.translate(glm::vec3(0.0f, 200.0f, 650.0f));
	//Platform->translate(glm::vec3(0.0f, -450.0f, 0.0f));
	//m_scene->addObject(Platform);
	m_scene->addObject(Boxe);
	m_scene->addObject(Lamp);

	//m_scene->addGlobalForce(m_gravite);

	using namespace Rainbow;

	mapButtonInput(BUTTON_A, jumpCallback);
	mapAnalogButtonInput(ANALOG_LEFTSTICK_X, sideMovement);
	mapButtonInput(BUTTON_X, teleportationCallback);
	mapButtonInput(BUTTON_B, sprintCallback);


}

Sandbox::~Sandbox(){
	delete Gold;
	delete Ruby;
	delete Chrome;
	delete Pearl;
	delete Copper;
	delete Obsidian;
	delete LampMaterial;

	delete m_Shader;

	delete m_gravite;

	m_scene->clearScene();
	delete m_scene;
}

void Sandbox::OnUpdate(float delta){
	//Maj du temps pour la camera
	double currentFrame = glfwGetTime();

	deltaTime = 60 * (currentFrame - lastFrame);

	lastFrame = currentFrame;

	processInput();

	//Slow down
	m_player->addForce(new Rainbow::Force(glm::vec3(-0.1f * m_player->GetSpeed().x, 0.0f, -0.1f * m_player->GetSpeed().z)));

	m_scene->UpdatePhysic(deltaTime);
	//Only move camera when big movement is achieved
	glm::vec3 newCameraPosition(m_player->getPosition() + glm::vec3(0.0f, 20.0f, 250.0f));
	if ((oldCameraPosition - newCameraPosition).length() > 0.8f) {
		oldCameraPosition = newCameraPosition;
		m_scene->retrieveCamera().m_position = newCameraPosition;
	}

	if (m_player->getPosition().y < -200.0f) {
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	if (currentFrame - timeOfLastJump > JUMP_COOLDOWN) {
		canJump = true;
	}

}

void Sandbox::OnRender() {
	
	if (r >= 0.4) {
		incR = -incR;
	}
	if (r < 0) {
		incR = -incR;
	}
	if (b >= 0.4) {
		incB = -incB;
	}
	if (b < 0) {
		incB = -incB;
	}
	if (g >= 0.4) {
		incG = -incG;

	}
	if (g < 0) {
		incG = -incG;
	}

	r += incR + incB - incG;
	b += incR - incB + incG;
	g += -incR + incB + incG;

	m_scene->setBackgroundColor(1 - r, 1 - g, 1 - b);

	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	frameNumber++;

	if (isSprinting) {
		m_player->setMaterial(LampMaterial);
	}
	else {
		m_player->setMaterial(Ruby);
	}

	m_scene->Render(Rainbow::Renderer::getInstance());
}

void Sandbox::OnImGuiRender() {
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::Button("Gravite++")) {
		m_scene->addGlobalForce(m_gravite); //A VERIFIER SI CE N'EST PAS AJOUTE PLUSIEURS FOIS..
	}
	else if (ImGui::Button("Gravite--")) {
		m_scene->addGlobalForce(m_reverseGravity);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

