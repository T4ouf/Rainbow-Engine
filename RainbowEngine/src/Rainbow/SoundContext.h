#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include <vector>
#include <windows.h>
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#include <al.h>
#include <alc.h>
#include <sndfile.h>
#include <stdio.h>

namespace Rainbow {
	class SoundContext {

	private:

		ALCdevice* Device;
		ALCcontext* context;
		std::vector<std::string> Devices;
		std::string  defaultDevice;


	public:

		SoundContext();
		~SoundContext();

		void GetDevices(std::vector<std::string>& Devices);

		void InitOpenAL();
		void ShutdownOpenAL();


	};
}