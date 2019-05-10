#include "Sound.h"

namespace Rainbow {

	Sound::Sound() {
		alGenSources(1, &m_Source);
		alGenBuffers(1, &m_Buffer);
	}


	Sound::~Sound() {
		alSourcei(m_Source, AL_BUFFER, 0);
		alDeleteSources(1, &m_Source);
		// Delete buffer
		alDeleteBuffers(1, &m_Buffer);
	}


	ALuint Sound::getSource() {
		return m_Source;
	}
	void Sound::setSource(ALuint Source) {
		m_Source = Source;

	}

	ALuint Sound::getBuffer() {
		return m_Buffer;
	}
	void Sound::setBuffer(ALuint Buffer) {
		m_Buffer = Buffer;
	}

	LPCWSTR Sound::getFilename() {
		return m_Filename;
	}
	void Sound::setFilename(LPCWSTR Filename) {
		m_Filename = Filename;
	}

	ALint Sound::getStatus() {
		return m_Status;
	}
	void Sound::setStatus(ALint Status) {
		m_Status = Status;
	}




	ALuint Sound::LoadSound(const LPCWSTR Filename) {
		// Open audio file with libsndfile

		SF_INFO FileInfos;
		SNDFILE* File = sf_wchar_open(Filename, SFM_READ, &FileInfos);
		if (!File) {
			std::cout << "error : " << sf_strerror(NULL) << std::endl;
			return 0;
		}
		// Get number of sample and sample rate (nomber of samples to read per sec)
		ALsizei NbSamples = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
		ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

		std::vector<ALshort> Samples(NbSamples);
		if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples) {
			return 0;
		}
		sf_close(File);

		// Get format from number of channels
		ALenum Format;
		switch (FileInfos.channels) {
		case 1:  Format = AL_FORMAT_MONO16; break;
		case 2:  Format = AL_FORMAT_STEREO16; break;
		default: std::cout << "Format problem" << std::endl;  return 0;
		}

		// init new buffer 
		ALuint Buffer;
		alGenBuffers(1, &Buffer);

		// fill with samples read
		alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

		// check errors
		if (alGetError() != AL_NO_ERROR) {
			return 0;
		}

		m_Buffer = Buffer;

		return Buffer;
	}

	void Sound::Play(bool LoopPlay){

		alSourcei(m_Source, AL_BUFFER, m_Buffer);
		alSourcei(m_Source, AL_LOOPING, LoopPlay);
		alSourcePlay(m_Source);
		do {
			// loop to play
			alGetSourcei(m_Source, AL_SOURCE_STATE, &m_Status);

		} while (m_Status == AL_PLAYING);
	}

	void Sound::Pause(){

		alSourcePause(m_Source);

	}

	void Sound::Stop()	{
		//TODO
	}

	void Sound::setGain(float gain){

		m_gain = gain;
		alSourcef(m_Source, AL_GAIN, gain);

	}
}

