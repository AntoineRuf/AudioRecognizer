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

#include "GnMic.h"

namespace gracenote
{
	GnMic::GnMic(gnsdk_uint32_t samplerate, gnsdk_uint16_t bitdepth, gnsdk_uint16_t channels)
	{
		m_samplerate = samplerate;
		m_bitdepth   = bitdepth;
		m_channels   = channels;

		m_micHandle = NULL;
		m_micEvent  = NULL;

		m_bRunning      = false;
		m_full_buffers  = NULL;
		m_empty_buffers = NULL;
		m_full_count    = 0;
		m_empty_count   = 0;

		InitializeCriticalSection(&m_cs);
	}


	GnMic::~GnMic(void)
	{
		SourceClose();

		if (m_micHandle)
			waveInClose(m_micHandle);

		if (m_micEvent)
			CloseHandle(m_micEvent);

		while (m_empty_buffers)
		{
			buffer_list_t* next = m_empty_buffers->next;
			GlobalFree(m_empty_buffers);
			m_empty_buffers = next;
		}
		while (m_full_buffers)
		{
			buffer_list_t* next = m_full_buffers->next;
			GlobalFree(m_full_buffers);
			m_full_buffers = next;
		}

		DeleteCriticalSection(&m_cs);
	}


	/*-----------------------------------------------------------------------------
	 *  SourceInit
	 */
	gnsdk_uint32_t
	GnMic::SourceInit()
	{
		MMRESULT	result;
		UINT		numDevs;

		numDevs = waveInGetNumDevs();
		if (numDevs == 0)
		{
			return GNSDKERR_InitFailed;
		}

		m_micEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		WAVEFORMATEX format;
		format.wFormatTag      = WAVE_FORMAT_PCM;
		format.wBitsPerSample  = m_bitdepth;
		format.nChannels       = m_channels;
		format.nSamplesPerSec  = m_samplerate;
		format.nAvgBytesPerSec = format.nSamplesPerSec*format.nChannels*format.wBitsPerSample/8;
		format.nBlockAlign     = format.nChannels*format.wBitsPerSample/8;
		format.cbSize          = 0;

		result = waveInOpen(&m_micHandle, WAVE_MAPPER, &format, (DWORD_PTR)_staticWaveInProc, (DWORD_PTR) this, CALLBACK_FUNCTION|WAVE_FORMAT_DIRECT);
		if (result)
		{
			DWORD error = GetLastError();
			GNSDK_UNUSED(error);
			GNSDK_ASSERT(!result);
			return GNSDKERR_InitFailed;
		}

		/* Set up and prepare 2 buffers for mic at first*/
		for (int i = 0; i < 2; i += 1)
		{
			buffer_list_t* buffer = _get_from_empty_list();
			if (buffer)
			{
				result = waveInPrepareHeader(m_micHandle, &buffer->waveHdr, sizeof(WAVEHDR));
				GNSDK_ASSERT(!result);

				result = waveInAddBuffer(m_micHandle, &buffer->waveHdr, sizeof(WAVEHDR));
				GNSDK_ASSERT(!result);
			}
		}

		result = waveInStart(m_micHandle);
		if (result)
		{
			GNSDK_ASSERT(!result);
			return GNSDKERR_InitFailed;
		}

		return GNSDKERR_NoError;
	}


	/*-----------------------------------------------------------------------------
	 *  SourceClose
	 */
	gnsdk_void_t
	GnMic::SourceClose()
	{
		MMRESULT result;

		if (m_bRunning)
		{
			EnterCriticalSection(&m_cs);
			{
				m_bRunning = false;
			}
			LeaveCriticalSection(&m_cs);

			result = waveInStop(m_micHandle);
			GNSDK_ASSERT(!result);

			result = waveInReset(m_micHandle);
			GNSDK_ASSERT(!result);
		}
	}


	/*-----------------------------------------------------------------------------
	 *  SamplesPerSecond
	 */
	gnsdk_uint32_t
	GnMic::SamplesPerSecond()
	{
		return m_samplerate;
	}


	/*-----------------------------------------------------------------------------
	 *  SampleSizeInBits
	 */
	gnsdk_uint32_t
	GnMic::SampleSizeInBits()
	{
		return m_bitdepth;
	}


	/*-----------------------------------------------------------------------------
	 *  NumberOfChannels
	 */
	gnsdk_uint32_t
	GnMic::NumberOfChannels()
	{
		return m_channels;
	}


	/*-----------------------------------------------------------------------------
	 *  GetData
	 */
	gnsdk_size_t
	GnMic::GetData(gnsdk_byte_t* audio_buffer, gnsdk_size_t buffer_size)
	{
		gnsdk_size_t read_size = 0;

		if (m_bRunning)
		{
			/* wait for buffer to appear on full queue */
			if (m_full_buffers == NULL)
			{
				WaitForSingleObject(m_micEvent, INFINITE);
			}

			if (m_full_buffers != NULL)
			{
				/* take from head of full buffers */
				buffer_list_t* buffer = m_full_buffers;

				read_size = buffer->waveHdr.dwBufferLength - buffer->bytes_used;
				if (read_size > buffer_size)
					read_size = buffer_size;

				memcpy(audio_buffer, &buffer->waveHdr.lpData[buffer->bytes_used], read_size);
				buffer->bytes_used += read_size;

				if (buffer->bytes_used == buffer->waveHdr.dwBufferLength)
				{
					/* all used up, move to next full and
					** add empty buffer to empty list */
					EnterCriticalSection(&m_cs);
					{
						m_full_buffers = m_full_buffers->next;
						if (m_full_buffers == NULL)
							ResetEvent(m_micEvent);
						m_full_count -= 1;

						_add_to_empty_list(buffer);
					}
					LeaveCriticalSection(&m_cs);
				}
			}
		}

		return read_size;
	}


	/*-----------------------------------------------------------------------------
	 *  _waveInProc
	 */
	void
	GnMic::_waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
	{
		MMRESULT result;

		(void)dwInstance;
		(void)dwParam2;

		EnterCriticalSection(&m_cs);

		switch (uMsg)
		{
		case WIM_OPEN:
			m_bRunning = true;
			ResetEvent(m_micEvent);
			break;

		case WIM_DATA:
			{
				buffer_list_t* buffer = (buffer_list_t*)dwParam1;

				/* add this buffer to full queue */
				_add_to_full_list(buffer);

				/* if still running, prepare another buffer for mic */
				if (m_bRunning)
				{
					result = waveInUnprepareHeader(hwi, &buffer->waveHdr, sizeof(WAVEHDR));
					GNSDK_ASSERT(!result);

					/* get new buffer from empty queue */
					buffer = _get_from_empty_list();
					if (buffer)
					{
						result = waveInPrepareHeader(hwi, &buffer->waveHdr, sizeof(WAVEHDR));
						GNSDK_ASSERT(!result);

						result = waveInAddBuffer(hwi, &buffer->waveHdr, sizeof(WAVEHDR));
						GNSDK_ASSERT(!result);
					}
					else
					{
						/* out of mem, bail */
						m_bRunning = false;
					}
				}

				/* signal that a buffer is available */
				SetEvent(m_micEvent);
			}
			break;

		case WIM_CLOSE:
			SetEvent(m_micEvent);
			break;
		}

		LeaveCriticalSection(&m_cs);
	}


	/*-----------------------------------------------------------------------------
	 *  _staticWaveInProc
	 */
	void CALLBACK
	GnMic::_staticWaveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
	{
		GnMic* me = (GnMic*)dwInstance;


		me->_waveInProc(hwi, uMsg, dwInstance, dwParam1, dwParam2);
	}


	/*-----------------------------------------------------------------------------
	 *  _add_to_full_list
	 */
	void
	GnMic::_add_to_full_list(buffer_list_t* buffer)
	{
		buffer_list_t* list_end = m_full_buffers;


		if (list_end == NULL)
		{
			m_full_buffers = buffer;
		}
		else
		{
			while (list_end && list_end->next)
				list_end = list_end->next;

			list_end->next = buffer;
		}

		buffer->next  = NULL;
		m_full_count += 1;
	}


	/*-----------------------------------------------------------------------------
	 *  _add_to_empty_list
	 */
	void
	GnMic::_add_to_empty_list(buffer_list_t* buffer)
	{
		buffer->next    = m_empty_buffers;
		m_empty_buffers = buffer;

		m_empty_count     += 1;
		buffer->bytes_used = 0;
	}


	/*-----------------------------------------------------------------------------
	 *  _get_from_empty_list
	 */
	GnMic::buffer_list_t*
	GnMic::_get_from_empty_list()
	{
		buffer_list_t* buffer = m_empty_buffers;


		if (buffer != NULL)
		{
			m_empty_buffers = m_empty_buffers->next;
			m_empty_count  -= 1;
		}
		else
		{
			/* create extra buffer */
			buffer = (buffer_list_t*)GlobalAlloc(GMEM_FIXED, sizeof(*buffer) + 2048);
			if (buffer)
			{
				memset(buffer, 0, sizeof(*buffer) + 2048);

				buffer->waveHdr.lpData         = (char*)buffer + sizeof(*buffer);
				buffer->waveHdr.dwBufferLength = 2048;
			}
		}

		return buffer;
	}

} /* namespace gracenote */