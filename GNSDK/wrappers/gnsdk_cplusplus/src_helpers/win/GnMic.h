#pragma once
#include "../../src_wrapper/gn_audiosource.hpp"

#include <Windows.h>

namespace gracenote
{
	/**
	*  This class represents Microphone as IGnAudioSource. Use this class when working with microphone
	*/
	class GnMic : public gracenote::IGnAudioSource
	{
	public:
		GnMic(gnsdk_uint32_t samplerate, gnsdk_uint16_t bitdepth, gnsdk_uint16_t channels);
		virtual ~GnMic(void);

		/*
		** GnAudioSource Implementation
		*/

		/**
		* Initialize Microphone as IGnAudioSource
		* @return errorCode 0 = sucess, non 0 = failure
		*/
		virtual gnsdk_uint32_t	SourceInit();

		/**
		* Close Microphone 
		*/
		virtual gnsdk_void_t	SourceClose();

		/*
		* Audio Samples Per Scecond 
		* @return samplePerSecond 
		*/
		virtual gnsdk_uint32_t	SamplesPerSecond();

		/**
		* Audio Sample Size in Bits
		* @return SampleSizeInBits
		*/
		virtual gnsdk_uint32_t	SampleSizeInBits();

		/**
		* Audio Number of Channels
		* @return Number of channels
		*/
		virtual gnsdk_uint32_t	NumberOfChannels();


		/**
		* Get audio data from microphone
		* @param audio_buffer Adudio Buffer
		* @param buffer_size  Audio Buffer Size
		* @return populated_buffer_size populated buffer size
		*/
		virtual gnsdk_size_t	GetData(gnsdk_byte_t* audio_buffer, gnsdk_size_t buffer_size);
	
	private:
		typedef struct s_buffer_list
		{
			WAVEHDR					waveHdr;
			gnsdk_size_t			bytes_used;
			struct s_buffer_list*	next;

		} buffer_list_t;

		static void CALLBACK 	_staticWaveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
		void 					_waveInProc      (HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

		void					_add_to_full_list   (buffer_list_t* buffer);
		void					_add_to_empty_list  (buffer_list_t* buffer);
		buffer_list_t*			_get_from_empty_list();
	
		gnsdk_uint32_t			m_samplerate;
		gnsdk_uint16_t			m_bitdepth;
		gnsdk_uint16_t			m_channels;

		HWAVEIN					m_micHandle;

		buffer_list_t*			m_full_buffers;
		buffer_list_t*			m_empty_buffers;
		gnsdk_uint32_t			m_full_count;
		gnsdk_uint32_t			m_empty_count;

		bool					m_bRunning;
		HANDLE					m_micEvent;
		CRITICAL_SECTION		m_cs;
	};

} /* namespace gracenote */