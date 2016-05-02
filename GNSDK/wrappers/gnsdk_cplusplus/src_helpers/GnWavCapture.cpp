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
 * GnMic.cpp
 */
#include "GnWavCapture.h"
#include "../src_wrapper/gnsdk_base.hpp"
#include "../src_wrapper/gnsdk_std.hpp"
namespace gracenote
{
	GnWavCapture::GnWavCapture(IGnAudioSource& audioSource, gnsdk_cstr_t output_filename) :
		m_p_audioSource(&audioSource)
	{
		gracenote::gnstd::gn_strcpy(m_filename, sizeof(m_filename), output_filename);


		m_file      = NULL;
		m_data_pos  = 0;
		m_data_size = 0;
		m_total_pos = 0;
	}


	GnWavCapture::~GnWavCapture()
	{
		if (m_file)
			fclose(m_file);
	}


	/*-----------------------------------------------------------------------------
	 *  SourceInit
	 */
	gnsdk_uint32_t
	GnWavCapture::SourceInit()
	{
		gnsdk_uint32_t error;
		gnsdk_uint32_t sample_rate;
		gnsdk_uint32_t bytes_per_second;
		gnsdk_uint16_t bytes_per_sample;
		gnsdk_uint16_t channels;
		gnsdk_uint16_t align;
		gnsdk_uint32_t temp32;
		gnsdk_uint16_t temp16;


		error = m_p_audioSource->SourceInit();
		if (!error)
		{
			m_file = fopen(m_filename, "wb");
			if (m_file)
			{
				/* write the 'RIFF' header */
				fwrite("RIFF", 1, 4, m_file);

				/* write the total size */
				temp32      = 0;
				m_total_pos = ftell(m_file);
				fwrite(&temp32, 1, 4, m_file);

				/* write the 'WAVE' type */
				fwrite("WAVE", 1, 4, m_file);

				/* write the 'fmt ' tag */
				fwrite("fmt ", 1, 4, m_file);

				/* write the format length */
				temp32 = GNSDK_BSWAP32_TO_LE(16);
				fwrite(&temp32, 1, 4, m_file);

				/* write the format (PCM) */
				temp16 = GNSDK_BSWAP16_TO_LE(1);
				fwrite(&temp16, 1, 2, m_file);

				/* write the channels */
				channels = (gnsdk_uint16_t)m_p_audioSource->NumberOfChannels();
				temp16   = GNSDK_BSWAP16_TO_LE(channels);
				fwrite(&temp16, 1, 2, m_file);

				/* write the sample rate */
				sample_rate = m_p_audioSource->SamplesPerSecond();
				temp32      = GNSDK_BSWAP32_TO_LE(sample_rate);
				fwrite(&temp32, 1, 4, m_file);

				/* write the bytes/second */
				bytes_per_sample = (gnsdk_uint16_t)m_p_audioSource->SampleSizeInBits() / 8;
				bytes_per_second = sample_rate * bytes_per_sample * channels;
				temp32           = GNSDK_BSWAP32_TO_LE(bytes_per_second);
				fwrite(&temp32, 1, 4, m_file);

				/* write the block align */
				align  = bytes_per_sample * channels;
				temp16 = GNSDK_BSWAP16_TO_LE(align);
				fwrite(&temp16, 1, 2, m_file);

				/* write the bits/sample */
				temp16 = GNSDK_BSWAP16_TO_LE(bytes_per_sample * 8);
				fwrite(&temp16, 1, 2, m_file);

				/* write the 'data' tag */
				fwrite("data", 1, 4, m_file);

				/* write the data length */
				temp32     = 0;
				m_data_pos = ftell(m_file);
				fwrite(&temp32, 1, 4, m_file);
			}
		}

		return error;
	}


	/*-----------------------------------------------------------------------------
	 *  SourceClose
	 */
	gnsdk_void_t
	GnWavCapture::SourceClose()
	{
		gnsdk_uint32_t temp32;


		m_p_audioSource->SourceClose();
		if (m_file)
		{
			/* update total file size */
			fseek(m_file, m_total_pos, SEEK_SET);
			temp32 = m_data_size + m_data_pos + 4;
			temp32 = GNSDK_BSWAP32_TO_LE(temp32);
			fwrite(&temp32, 1, 4, m_file);

			/* update data size */
			fseek(m_file, m_data_pos, SEEK_SET);
			temp32 = GNSDK_BSWAP32_TO_LE(m_data_size);
			fwrite(&temp32, 1, 4, m_file);

			fclose(m_file);
			m_file = NULL;
		}
	}


	/*-----------------------------------------------------------------------------
	 *  SamplesPerSecond
	 */
	gnsdk_uint32_t
	GnWavCapture::SamplesPerSecond()
	{
		return m_p_audioSource->SamplesPerSecond();
	}


	/*-----------------------------------------------------------------------------
	 *  SampleSizeInBits
	 */
	gnsdk_uint32_t
	GnWavCapture::SampleSizeInBits()
	{
		return m_p_audioSource->SampleSizeInBits();
	}


	/*-----------------------------------------------------------------------------
	 *  NumberOfChannels
	 */
	gnsdk_uint32_t
	GnWavCapture::NumberOfChannels()
	{
		return m_p_audioSource->NumberOfChannels();
	}


	/*-----------------------------------------------------------------------------
	 *  GetData
	 */
	gnsdk_size_t
	GnWavCapture::GetData(gnsdk_byte_t* audio_buffer, gnsdk_size_t buffer_size)
	{
	    gnsdk_size_t bytes_read = m_p_audioSource->GetData(audio_buffer, buffer_size);
		if (m_file && (bytes_read > 0))
		{
			m_data_size += fwrite(audio_buffer, 1, bytes_read, m_file);
		}

		return bytes_read;
	}

} /* namespace gracenote */
