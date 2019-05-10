#include "SoundManager.h"

#include <locale>
#include <codecvt>        // std::codecvt_utf8
#include <string>

namespace Rainbow {
	
	SoundManager::SoundManager() {
		PlayingSounds = std::unordered_map<std::string, launchableSound>();
	}


	SoundManager::~SoundManager() {

	}

	void SoundManager::launchSound(std::string path, std::string soundID, bool loop) {

		Sound* s = new Sound();

		//converting std::string into std::wstring (wide string with codec UTF-16)
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wpath = converter.from_bytes(path);

		s->setBuffer(s->LoadSound(wpath.c_str()));

		std::thread* t = new std::thread(&Sound::Play, s, loop);

		launchableSound l = { s,t };
		PlayingSounds[soundID] = l;

	}

	void SoundManager::loadSound(std::string path, std::string soundID) {
		Sound* s = new Sound();

		//converting std::string into std::wstring (wide string with codec UTF-16)
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wpath = converter.from_bytes(path);

		s->setBuffer(s->LoadSound(wpath.c_str()));

		//std::thread* t = new std::thread();

		launchableSound l = { s, nullptr };
		PlayingSounds[soundID] = l;
	}

	void SoundManager::destroySound(std::string soundID) {

		try {

			launchableSound l = PlayingSounds.at(soundID);

			if (l.thread != nullptr) {
				if (l.thread->joinable()) {
					l.thread->detach();
				}
				delete l.thread;
			}

			delete l.sound;
			PlayingSounds.erase(soundID);

		}
		catch (std::out_of_range& ex) {
			//if the sound is not mapped...
			ex.what();
		}


	}

	void SoundManager::clear() {

		//We delete all sound of our map

		while (PlayingSounds.size()>0) {
			destroySound(PlayingSounds.begin()->first);
		}

		//just to be sure
		PlayingSounds.clear();
	}

	Sound* SoundManager::getSound(std::string soundID) {

		try {

			launchableSound l = PlayingSounds.at(soundID);
			return l.sound;

		}
		catch (std::out_of_range& ex) {
			//if the sound is not mapped...
			ex.what(); //(do nothing...)
		}

		return nullptr;

	}

	void SoundManager::playSound(Sound* s, std::string soundID, bool loop) {
		launchableSound l;

		try {

			l = PlayingSounds.at(soundID);

			if (l.thread != nullptr) {
				if (l.thread->joinable()) {
					l.thread->detach();
				}
				delete l.thread;
			}

		}
		catch (std::out_of_range& ex) {
			//if the sound is not mapped...
			ex.what(); //(do nothing...)
		}

		std::thread* t = new std::thread(&Sound::Play, s, loop);

		l = { s,t };
		PlayingSounds[soundID] = l;

	}

}
