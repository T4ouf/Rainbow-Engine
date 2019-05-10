#pragma once

//#include "Rainbow_pch.h"
#include "SoundContext.h"
#include "SoundManager.h"
#include <unordered_map>
#include "Core.h"


namespace Rainbow {

	typedef enum {

		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,

		BUTTON_RIGHTCROSS,
		BUTTON_LEFTCROSS,
		BUTTON_UPCROSS,
		BUTTON_DOWNCROSS,

		BUTTON_LB,
		BUTTON_RB,

		BUTTON_BACK,
		BUTTON_START,

		BUTTON_LSTICK_PRESS,
		BUTTON_RSTICK_PRESS

	}ControllerButton;

	typedef enum {

		ANALOG_LEFTSTICK_X,
		ANALOG_LEFTSTICK_Y,

		ANALOG_RIGHTSTICK_X,
		ANALOG_RIGHTSTICK_Y,

		ANALOG_RIGHTTRIGGER,
		ANALOG_LEFTTRIGGER

	}ControllerAnalogButton;

	//Defining the Button function pointer type
	typedef void(*ButtonFunction)(void);

	//Defining the Analog Button function pointer type
	typedef void(*AnalogButtonFunction)(float);	//Must have a param that is the analogic value of the button


	class RAINBOW_API Application{

	private:
		std::unordered_map<ControllerButton, ButtonFunction> m_mapControllerButton;
		std::unordered_map<ControllerAnalogButton, AnalogButtonFunction> m_mapControllerAnalogButton;

	protected: 
		SoundContext* m_soundContext;
		SoundManager* m_soundManager;

	public:
		Application();
		virtual ~Application();

		//Adding a correspondance between a button and a function (adding to the map)
		void mapButtonInput(ControllerButton b, ButtonFunction f);
		void mapAnalogButtonInput(ControllerAnalogButton AnalogB, AnalogButtonFunction f);
		
		//Function that process all the input that are in the maps
		void processInput();

		void Run();

		virtual void OnUpdate(float delta) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	//Creation of a Rainbow Application => MUST BE DEFINED IN THE CLIENT
	Application* CreateApplication();


}

