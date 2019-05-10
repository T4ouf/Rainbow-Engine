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

	class Sound{

	private :

		ALuint m_Source;
		ALuint m_Buffer;
		LPCWSTR m_Filename;
		ALint m_Status;

		float m_gain;

	public:


		Sound();
		~Sound();

		ALuint getSource();
		void setSource(ALuint Source);

		ALuint getBuffer();
		void setBuffer(ALuint Buffer);

		LPCWSTR getFilename();
		void setFilename(LPCWSTR Filename);

		ALint getStatus();
		void setStatus(ALint Status);

		ALuint LoadSound(const LPCWSTR Filename);

		void Play(bool LoopPlay);

		void Pause();

		void Stop();

		void setGain(float gain);
	};

}
