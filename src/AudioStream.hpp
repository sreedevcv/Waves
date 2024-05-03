#pragma once


#include "portaudio.h"

#include "Audio.hpp"
#include <vector>

class AudioStream {
private:
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	AudioMetaData metaData;

	void logError();
	int callback(
		const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags
	);

public:
	AudioStream(AudioMetaData audioMetaData);
	~AudioStream();

	template<typename T>
	void openStream(std::vector<T> data)
	{
		err = Pa_OpenStream(
			&stream, 
			&outputParameters, 
			&outputParameters, 
			metaData.sampleRate, 
			64, 
			paClipOff, 
			// callback, 
			data
		);

		if (err != paNoError) {
			logError();
			return;
		}
	}
};