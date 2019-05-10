#pragma once

#include <thread>
#include <unordered_map>
#include "Sound.h"

namespace Rainbow {

	typedef struct {
		Sound* sound;
		std::thread* thread;
	}launchableSound;

	class SoundManager{
	private:

		std::unordered_map<std::string, launchableSound> PlayingSounds;

	public:
		SoundManager();
		~SoundManager();

		void launchSound(std::string path, std::string soundID, bool loop);
		void loadSound(std::string path, std::string soundID);
		void destroySound(std::string soundID);
		void clear();

		Sound* getSound(std::string soundID);
		void playSound(Sound* s, std::string soundID, bool loop);

	};
}

