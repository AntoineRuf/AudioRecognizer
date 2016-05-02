/*
 *
 *  GRACENOTE, INC. PROPRIETARY INFORMATION
 *  This software is supplied under the terms of a license agreement or
 *  nondisclosure agreement with Gracenote, Inc. and may not be copied
 *  or disclosed except in accordance with the terms of that agreement.
 *  Copyright(c) 2000-2014. Gracenote, Inc. All Rights Reserved.
 *
 */

/*
 * GnAudioFile.cpp
 */

#include "GnAudioFile.h"
#include "../src_wrapper/gnsdk_std.hpp"
#include "../src_wrapper/gnsdk_base.hpp"

#if HAVE_BASS_DECODER
	/* Bass stuff */
#else
	#include <memory.h> /* for memcmp */
#endif

#ifdef _WIN32
	#include <windows.h>
#endif

namespace gracenote
{
	GnAudioFile::GnAudioFile(gnsdk_cstr_t filename)
	{
#ifdef _WIN32
		WCHAR wbuf[300];
		MultiByteToWideChar(CP_UTF8, 0, filename, -1, wbuf, 300);
		WideCharToMultiByte(CP_ACP, 0, wbuf, -1, m_filename, sizeof(m_filename), 0, 0);
#else
		gnstd::gn_strcpy(m_filename, sizeof(m_filename), filename);
#endif
		m_sampleRate  = 0;
		m_sampleSize  = 0;
		m_numChannels = 0;

#if HAVE_BASS_DECODER	
		m_chan = 0;
#else
		m_file = NULL;
#endif
	}


	GnAudioFile::~GnAudioFile(void)
	{
#if HAVE_BASS_DECODER
		BASS_Free();
#else
		if (m_file)
			fclose(m_file);
#endif
	}


	/*-----------------------------------------------------------------------------
	 *  SourceInit
	 */
	gnsdk_uint32_t
	GnAudioFile::SourceInit()
	{
#if HAVE_BASS_DECODER
		if (m_chan == 0)
		{
			/* setup output - "no sound" device, 44100hz, stereo, 16 bits */
			if (!BASS_Init(0, 44100, 0, NULL, NULL))
			{
				if (BASS_ErrorGetCode() != BASS_ERROR_ALREADY) 
					return GNSDKERR_InitFailed;
			}

			/* not playing anything, so don't need an update thread */
			BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 0);

			/* try streaming the file/url */
			m_chan = BASS_StreamCreateFile(FALSE, m_filename, 0, 0, BASS_STREAM_DECODE);
			if (m_chan)
			{
				BASS_CHANNELINFO	info;

				if (BASS_ChannelGetInfo(m_chan, &info))
				{
					m_sampleRate = info.freq;
					m_numChannels = info.chans;

					if (info.flags & BASS_SAMPLE_8BITS)
						m_sampleSize = 8;
					else if (info.flags & BASS_SAMPLE_FLOAT)
						m_sampleSize = 32;
					else
						m_sampleSize = 16;

					return GNSDKERR_NoError;
				}
			}

			return GNSDKERR_InitFailed;
		}
#else
		gnsdk_byte_t	buffer[32];
		gnsdk_uint32_t	temp32;
		gnsdk_uint16_t	temp16;
		gnsdk_size_t    readsize;

		/* support only WAV files */
		m_file = fopen(m_filename, "rb");
		if (m_file == NULL)
		{
			return GNSDKERR_InitFailed;
		}

		fread(buffer, 1, 8, m_file);
		if (memcmp(buffer, "RIFF", 4) == 0)
		{
			readsize = fread(buffer, 1, 4, m_file);
			while (readsize == 4)
			{
				if (memcmp(buffer, "WAVE", 4) == 0)
				{
					readsize = fread(buffer, 1, 4, m_file);
					while (readsize == 4)
					{
						if (memcmp(buffer, "fmt ", 4) == 0)
						{
							/* read the format length */
							fread(&temp32, 4, 1, m_file);
							temp32 = GNSDK_BSWAP32_FROM_LE(temp32);

							/* read the format (PCM) */
							fread(&temp16, 2, 1, m_file);
							temp16 = GNSDK_BSWAP16_FROM_LE(temp16);

							/* read the channels */
							fread(&temp16, 2, 1, m_file);
							m_numChannels = GNSDK_BSWAP16_FROM_LE(temp16);

							/* write the sample rate */
							fread(&temp32, 4, 1, m_file);
							m_sampleRate = GNSDK_BSWAP32_FROM_LE(temp32);

							/* read the bytes/second */
							fread(&temp32, 4, 1, m_file);
							/* read the block align */
							fread(&temp16, 2, 1, m_file);

							/* read the bits/sample */
							fread(&temp16, 2, 1, m_file);
							m_sampleSize = GNSDK_BSWAP16_FROM_LE(temp16);

							/* read the 'data' tag */
							fread(buffer, 4, 1, m_file);
							/* read the data length */
							fread(&temp32, 4, 1, m_file);

							return GNSDKERR_NoError;
						}
						else
						{
							/* read the chunk length */
							fread(&temp32, 4, 1, m_file);
							temp32 = GNSDK_BSWAP32_FROM_LE(temp32);
							fseek(m_file, temp32, SEEK_SET);
							readsize = fread(buffer, 1, 4, m_file);
						}
					}
				}
				else
				{
					/* read the chunk length */
					fread(&temp32, 4, 1, m_file);
					temp32 = GNSDK_BSWAP32_FROM_LE(temp32);
					fseek(m_file, temp32, SEEK_SET);
					readsize = fread(buffer, 1, 4, m_file);
				}
			}
		}
#endif

		return GNSDKERR_InitFailed;
	}


	/*-----------------------------------------------------------------------------
	 *  SourceClose
	 */
	gnsdk_void_t
	GnAudioFile::SourceClose()
	{
#if HAVE_BASS_DECODER
		BASS_StreamFree(m_chan);
		m_chan = 0;
#else
		if (m_file)
		{
			fclose(m_file);
			m_file = NULL;
		}
#endif
	}


	/*-----------------------------------------------------------------------------
	 *  SamplesPerSecond
	 */
	gnsdk_uint32_t
	GnAudioFile::SamplesPerSecond()
	{
		return m_sampleRate;
	}


	/*-----------------------------------------------------------------------------
	 *  SampleSizeInBits
	 */
	gnsdk_uint32_t
	GnAudioFile::SampleSizeInBits()
	{
		return m_sampleSize;
	}


	/*-----------------------------------------------------------------------------
	 *  NumberOfChannels
	 */
	gnsdk_uint32_t
	GnAudioFile::NumberOfChannels()
	{
		return m_numChannels;
	}


	/*-----------------------------------------------------------------------------
	 *  GetData
	 */
	gnsdk_size_t
	GnAudioFile::GetData(gnsdk_byte_t* audio_buffer, gnsdk_size_t buffer_size)
	{
		gnsdk_size_t bytes_read = 0;

#if HAVE_BASS_DECODER
		if (BASS_ChannelIsActive(m_chan))
		{
			bytes_read = BASS_ChannelGetData(m_chan, audio_buffer, buffer_size);
			if (bytes_read == (gnsdk_size_t)-1) /* error */
				bytes_read = 0;
		}
#else
		if (m_file)
		{
			bytes_read = fread(audio_buffer, 1, buffer_size, m_file);
		}
#endif

		return bytes_read;
	}


} /* namespace gracenote */
