#pragma once
#include "Rainbow.h"

struct CreatedObject{
	Rainbow::Object* obj;
	bool isSelected;
	std::string type;
};

class LevelEditor : public Rainbow::Application {
private:

	// Shader
	Rainbow::Shader* m_Shader;

	// Materials
	Rainbow::Material* Gold;
	Rainbow::Material* Ruby;
	Rainbow::Material* Chrome;
	Rainbow::Material* Pearl;
	Rainbow::Material* Copper;
	Rainbow::Material* Obsidian;
	Rainbow::Material* BlackRubber;
	Rainbow::Material* LampMaterial;
	static const char* m_materialsAvailable[];
	int m_currentMaterialInCombo;
	Rainbow::Material* m_currentMaterialSelected;

	Rainbow::Scene* scene;

	// Background color
	float m_colorBackground[3];

	// Music file path
	char m_musicFilePath[100];
	int m_musicFilePathSize = 100;

	// Graphical Objects -----------------------------------
	static const char* m_objectsAvailable[]; // Objects types
	int m_currentObjectInCombo; // Object selected in combo to be created
								// Object* m_currentSelectedObject; // Point to a Object selected in the interface, new or selected by clicking on it in the level

	// Created objects
	std::unordered_map<Rainbow::Object*, std::string> m_existingObjectsXML;
	std::vector<CreatedObject> m_existingObjects;

	// Start and finish
	bool m_startPlaced, m_finishPlaced;
	int m_startX, m_startY, m_startZ, m_finishX, m_finishY, m_finishZ;
	int m_finishWidth, m_finishHeight, m_finishLength;
	Rainbow::Object* m_startCube, *m_finishCube;

	// Cube
	int m_cubeX, m_cubeY, m_cubeZ;
	float m_cubeSize, m_cubeMass;
	bool m_cubeIsAnchor;

	// Boxe
	int m_boxeX, m_boxeY, m_boxeZ;
	float m_boxeSizeX, m_boxeSizeY, m_boxeSizeZ, m_boxeMass;
	bool m_boxeIsAnchor;

	// Sphere
	int m_sphereX, m_sphereY, m_sphereZ;
	float m_sphereRadius, m_sphereMass;
	bool m_sphereIsAnchor;

	// Button Create
	bool m_displayCreateBtn;

	// Level Name and XML file generation
	char m_levelName[30];
	int m_levelNameSize = 30;
	bool m_displayLevelNameWindow;
	bool m_displayFileGenerationSuccessWindow;
	char m_levelFilePath[100];
	int m_levelFilePathSize = 100;

	// Inputs
	int m_joystickPresent;

	//  ----------------------------------- METHODS  -----------------------------------

	// Interface ImGui Windows
	void createObjectWindow();
	void listObjectsWindow();
	void mousePositionWindow();
	void backgroundColorWindow();
	void levelNameWindow();
	void fileGenerationSuccessWindow();
	void musicFileWindow();

	// Interface ImGui Graphical Objects
	void startItemsImGuiRender();
	void finishItemsImGuiRender();
	void cubeItemsImGuiRender();
	void sphereItemsImGuiRender();
	void boxeItemsImGuiRender();

	// Structure creation
	void startCreation();
	void finishCreation();
	void cubeCreation();
	void sphereCreation();
	void boxeCreation();

	// File creation and finish
	void generateXMLFile();

	// Interactions with mouse
	void processMouseAction();

	// Interactions with controller / joystick
	void processJoystickInput();

public:
	LevelEditor();
	~LevelEditor();

	void OnUpdate(float delta) override;
	void OnRender() override;
	void OnImGuiRender() override;

};

//Defining entry point of the program
Rainbow::Application* Rainbow::CreateApplication() {

	return new LevelEditor();
}