#pragma once
#include "../src_wrapper/gn_audiosource.hpp"

#include <stdio.h>

namespace gracenote
{
	class GnWavCapture : public gracenote::IGnAudioSource
	{
	public:
		GnWavCapture(IGnAudioSource& audioSource, gnsdk_cstr_t output_filename);
		virtual ~GnWavCapture();

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
		gnsdk_char_t			m_filename[300];
		FILE*					m_file;

		gnsdk_size_t			m_data_size;
		long					m_data_pos;
		long					m_total_pos;

		IGnAudioSource*			m_p_audioSource;
	};
}

