#pragma once

//if platform is Windows
#ifdef RAINBOW_PLATFORM_WINDOWS
	
	//if we try to build DLL => export / Otherwhise we import the DLL
	#ifdef RAINBOW_BUILD_DLL
		//#define RAINBOW_API __declspec(dllexport)
		#define RAINBOW_API
	#else
		//#define RAINBOW_API __declspec(dllimport)
		#define RAINBOW_API
	#endif

#else 
	#error RAINBOW ENGINE ONLY SUPPORTS WINDOWS !
#endif