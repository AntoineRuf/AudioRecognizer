#pragma once
#include "../src_wrapper/gn_audiosource.hpp"

#if HAVE_BASS_DECODER
	#include "bass.h"
#else
	#include <stdio.h> /* for FILE */
#endif

namespace gracenote
{
	/**
	*  This class represents AudioFile as IGnAudioSource. Use this class when working with audio files.
	*/
	class GnAudioFile : public gracenote::IGnAudioSource
	{
	public:
		GnAudioFile(gnsdk_cstr_t filename);
		virtual ~GnAudioFile(void);

		/*
		** GnAudioSource Implementation
		*/

		/**
		* Initialize Audio File as GnAudioSource
		* @return errorCode 0 = sucess, non 0 = failure
		*/
		virtual gnsdk_uint32_t	SourceInit();

		/**
		* Close AudioSource 
		*/
		virtual gnsdk_void_t	SourceClose();

		/*
		* Audio File Samples Per Scecond 
		* @return samplePerSecond 
		*/
		virtual gnsdk_uint32_t	SamplesPerSecond();

		/**
		* Audio File Sample Size in Bits
		* @return SampleSizeInBits
		*/
		virtual gnsdk_uint32_t	SampleSizeInBits();

		/**
		* Audio file Number of Channels
		* @return Number of channels
		*/
		virtual gnsdk_uint32_t	NumberOfChannels();

		/**
		* Get audio data from file
		* @param audio_buffer Adudio Buffer
		* @param buffer_size  Audio Buffer Size
		* @return populated_buffer_size populated buffer size
		*/
		virtual gnsdk_size_t	GetData(gnsdk_byte_t* audio_buffer, gnsdk_size_t buffer_size);


	private:
		gnsdk_char_t		m_filename[300];
		gnsdk_uint32_t		m_sampleRate;
		gnsdk_uint32_t		m_sampleSize;
		gnsdk_uint32_t		m_numChannels;

#if HAVE_BASS_DECODER
		HSTREAM				m_chan;
#else
		FILE*				m_file;
#endif
	};

}
