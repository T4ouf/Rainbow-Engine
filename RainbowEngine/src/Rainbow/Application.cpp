#include "Application.h"

#include "Macros.h"
#include "Renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Rainbow {

	void emptyFunc() {
		return;
	}

	void emptyAnalogFunc(float f) {
		return;
	}

	Application::Application(){


		//On vérifie que l'on a réussi à initialiser glfw
		if (glfwInit() == false) {

			std::cerr << "ERREUR INITIALISATION GLFW !";
			return;
		}

		//4 AA
		glfwWindowHint(GLFW_SAMPLES, 4);

		//def la version de OpenGL utilisée: ici 3.3 (Modern OpenGL)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


		//vérifie que OpenGL version >= 3
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		//Création d'une fenêtre OpenGL
		GLFWwindow* fen;
		//					largeur, hauteur,   titre
		fen = glfwCreateWindow(960, 540, "Rainbow Engine Application", NULL, NULL);


		//On vérifie que la fenêtre s'est bien créée:
		//Si il y a eu un problème:
		if (!fen) {
			std::cerr << "ERREUR DANS LA CREATION DE LA FENETRE !";
			glfwTerminate();	//On termine le processus
			return;
		}

		//On met notre fenêtre comme context principal
		glfwMakeContextCurrent(fen);

		//on def la freq de rafraichissement
		// 1 = frequence de rafraichissement du moniteur (60FPS)
		glfwSwapInterval(1);


		//autorise les versions les plus récentes de openGL
		glewExperimental = true;
		
		// /!\initialise glew APRES l'avoir lié au context/!\ 
		if (glewInit() != GLEW_OK) {

			std::cerr << "ERREUR INITIALISATION DE GLEW !";
			glfwTerminate();	//On termine le processus
			return;

		}

		//On autorise et paramètre la transparence
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//On active le test de profondeur (z-buffer test)
		glEnable(GL_DEPTH_TEST);
		//On accepte que les pixels qui sont devant (les autres ne seront pas dessinés par dessus)
		glDepthFunc(GL_LESS);

		// Prépare à l'utilisation de ImGui
		ImGui::CreateContext();

		//Initialise ImGui
		ImGui_ImplGlfwGL3_Init(fen, true);

		// Choix du style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsClassic();

		//Creating the maps
		m_mapControllerButton = std::unordered_map<ControllerButton, ButtonFunction>();
		m_mapControllerAnalogButton = std::unordered_map<ControllerAnalogButton, AnalogButtonFunction>();

		//init buttons with empty func
		m_mapControllerButton[BUTTON_A] = emptyFunc;
		m_mapControllerButton[BUTTON_B] = emptyFunc;
		m_mapControllerButton[BUTTON_X] = emptyFunc;
		m_mapControllerButton[BUTTON_Y] = emptyFunc;

		m_mapControllerButton[BUTTON_RIGHTCROSS] = emptyFunc;
		m_mapControllerButton[BUTTON_LEFTCROSS] = emptyFunc;
		m_mapControllerButton[BUTTON_UPCROSS] = emptyFunc;
		m_mapControllerButton[BUTTON_DOWNCROSS] = emptyFunc;

		m_mapControllerButton[BUTTON_LB] = emptyFunc;
		m_mapControllerButton[BUTTON_RB] = emptyFunc;
		m_mapControllerButton[BUTTON_BACK] = emptyFunc;
		m_mapControllerButton[BUTTON_START] = emptyFunc;

		m_mapControllerButton[BUTTON_LSTICK_PRESS] = emptyFunc;
		m_mapControllerButton[BUTTON_RSTICK_PRESS] = emptyFunc;

		//init analog with empty func
		m_mapControllerAnalogButton[ANALOG_LEFTSTICK_X] = emptyAnalogFunc;
		m_mapControllerAnalogButton[ANALOG_LEFTSTICK_Y] = emptyAnalogFunc;
		m_mapControllerAnalogButton[ANALOG_RIGHTSTICK_X] = emptyAnalogFunc;
		m_mapControllerAnalogButton[ANALOG_RIGHTSTICK_Y] = emptyAnalogFunc;

		m_mapControllerAnalogButton[ANALOG_RIGHTTRIGGER] = emptyAnalogFunc;
		m_mapControllerAnalogButton[ANALOG_LEFTTRIGGER] = emptyAnalogFunc;

		m_soundContext = new SoundContext();
		m_soundManager = new SoundManager();

	}


	Application::~Application(){
		delete m_soundManager;
		delete m_soundContext;
	}


	void Application::mapButtonInput(ControllerButton b, ButtonFunction f) {

		//Add the button to the map (replace if already mapped)
		m_mapControllerButton[b] = f;

	}

	void Application::mapAnalogButtonInput(ControllerAnalogButton AnalogB, AnalogButtonFunction f) {

		//Add the Analog button to the map (replace if already mapped)
		m_mapControllerAnalogButton[AnalogB] = f;

	}

	void Application::processInput() {

		// Get controller's state
		int nbJoystickAxes, nbJoystickButtons; // 6 and 14 for xbox 360

		// 0 : left joystick  -> axe X (cosinus) (left -1 -> 1 right)
		// 1 : left joystick  -> axe Y (sinus) (down -1 -> 1 up)
		// 2 : right joystick -> axe X (cosinus) (left -1 -> 1 right)
		// 3 : right joystick -> axe Y (sinus) (down -1 -> 1 up)
		// 4 : LT button (free -1 -> triggered 1)
		// 5 : RT button (free -1 -> triggered 1)
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &nbJoystickAxes);


		// 0 : A button
		// 1 : B button
		// 2 : X button
		// 3 : Y button
		// 4 : LB button
		// 5 : RB button
		// 6 : back/select button
		// 7 : start button
		// 8 : left joystick click
		// 9 : right joystick click
		// 10 : top cross
		// 11 : right cross
		// 12 : bottom cross
		// 13 : left cross
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &nbJoystickButtons);

		if (buttons == NULL || axes == NULL) {
			//no Joystick plugged
			//Error Message ?
			return;
		}

		try {
			// Process actions

			//TODO : RELEASE BUTTON ACTION
			if (buttons[0] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_A);
				f();
			}
			if (buttons[1] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_B);
				f();
			}
			if (buttons[2] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_X);
				f();
			}
			if (buttons[3] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_Y);
				f();
			}
			if (buttons[4] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_LB);
				f();
			}
			if (buttons[5] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_RB);
				f();
			}
			if (buttons[6] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_BACK);
				f();
			}
			if (buttons[7] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_START);
				f();
			}
			if (buttons[8] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_LSTICK_PRESS);
				f();
			}
			if (buttons[9] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_RSTICK_PRESS);
				f();
			}
			if (buttons[10] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_UPCROSS);
				f();
			}
			if (buttons[11] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_RIGHTCROSS);
				f();
			}
			if (buttons[12] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_DOWNCROSS);
				f();
			}
			if (buttons[13] == GLFW_PRESS) {
				auto f = m_mapControllerButton.at(BUTTON_LEFTCROSS);
				f();
			}
		}
		catch (std::out_of_range& ex) {
			//ex is launched if the button si not mapped (maybe mapping it with void func is better ?)
			ex.what(); //(do nothing...)
		}

		//Analog stick (stick are always processed)
		try {
			//stick starts at 0 (-1 - 1)
			auto f = m_mapControllerAnalogButton.at(ANALOG_LEFTSTICK_X);
			f(axes[0]);

			f = m_mapControllerAnalogButton.at(ANALOG_LEFTSTICK_Y);
			f(axes[1]);

			f = m_mapControllerAnalogButton.at(ANALOG_RIGHTSTICK_X);
			f(axes[2]);

			f = m_mapControllerAnalogButton.at(ANALOG_RIGHTSTICK_Y);
			f(axes[3]);


			//Triggers starts at 0 (0 - 2)
			f = m_mapControllerAnalogButton.at(ANALOG_LEFTTRIGGER);
			f(axes[4] + 1);

			f = m_mapControllerAnalogButton.at(ANALOG_RIGHTTRIGGER);
			f(axes[5] + 1);

		}
		catch (std::out_of_range& ex) {
			//ex is launched if the button si not mapped (maybe mapping it with void func is better ?)
			ex.what(); //(do nothing...)
		}

	}

	void Application::Run()	{
	
		
		GLFWwindow* fen = glfwGetCurrentContext();
		Renderer* renderer = Renderer::getInstance();
		while (!glfwWindowShouldClose(fen)) {

			GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			//Avant le dessin on nettoie tout
			renderer->Clear();

			//Ouvre une fenêtre ImGui
			ImGui_ImplGlfwGL3_NewFrame();

			OnUpdate(0.0f);
			OnRender();
			OnImGuiRender();

			//Dessine l'interface ImGUI
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			//On echange les framesBuffers 
			glfwSwapBuffers(fen);

			glfwPollEvents();

		}

		// Cleanup
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();

		exit(EXIT_SUCCESS);
	}


}

