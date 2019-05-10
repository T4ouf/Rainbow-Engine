
#include "SoundContext.h"
#include "Sound.h"

namespace Rainbow {

	SoundContext::SoundContext() {
		Device = NULL;
		context = NULL;
		GetDevices(Devices);
		defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
		InitOpenAL();

	}

	SoundContext::~SoundContext() {
		ShutdownOpenAL();
	}

	void SoundContext::GetDevices(std::vector<std::string>& Devices) {
		// empty vector
		Devices.clear();

		// get devices availables
		const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

		if (DeviceList) {
			// extract devices from DeviceList
			while (strlen(DeviceList) > 0) {
				Devices.push_back(DeviceList);
				DeviceList += strlen(DeviceList) + 1;
			}
		}
	}


	void SoundContext::InitOpenAL() {

		// Initialize Open AL
		Device = alcOpenDevice(NULL); // open default device
		if (Device != NULL) {
			context = alcCreateContext(Device, NULL); // create context
			if (context != NULL) {
				alcMakeContextCurrent(context); // set active context
			}
		}

	}

	void SoundContext::ShutdownOpenAL() {

		// Desactivate context
		alcMakeContextCurrent(NULL);

		// Destroy context
		alcDestroyContext(context);

		// Close device
		alcCloseDevice(Device);
	}


}
