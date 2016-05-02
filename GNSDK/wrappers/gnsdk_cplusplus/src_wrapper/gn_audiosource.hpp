/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

/* IGnAudioSource.hpp: Gracenote audio helper class */

#ifndef _GNAUDIOSOURCE_HPP_
#define _GNAUDIOSOURCE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk.h"

namespace gracenote
{
	/**
	 * Delegate interface for retrieving audio data from an audio source such as a microphone, audio file
	 * or Internet stream.
	 * Various Gracenote methods consume audio data via audio sources, allowing the transfer
	 * of audio from the audio source to the consumer without requiring the application to
	 * manually pass the data. This can simplify the application's implementation.
	 * Applications are encouraged to implement their own audio source objects, or example if
	 * custom audio file format is used an application may implement an IGnAudioSource interface to
	 * the custom audio format decoder.
	 */
	class IGnAudioSource
	{
	public:
		virtual ~IGnAudioSource() {};

		/**
		 * Initialize the audio source. This will be invoked prior to any other methods. If initialization
		 * fails return a non-zero value. In this case the consumer will not call any other methods
		 * including that to close the audio source.
		 * @return 0 indicates initialization was successful, non-zero otherwise.
		 */
		virtual gnsdk_uint32_t
		SourceInit()  = 0;

		/**
		 * Close the audio source. The consumer will not call any other methods after the source has
		 * been closed
		 */
		virtual void
		SourceClose() = 0;


		/**
		 * Return the number of samples per second of the source audio format. Returns zero if called
		 * prior to SourceInit.
		 * @return Samples per second
		 */
		virtual gnsdk_uint32_t
		SamplesPerSecond() = 0;

		/**
		 * Return the number of bits in a sample of the source audio format. Returns zero if called
		 * prior to SourceInit.
		 * @return Sample size in bits
		 */
		virtual gnsdk_uint32_t
		SampleSizeInBits() = 0;

		/**
		 * Return the number of channels of the source audio format. Returns zero if called
		 * prior to SourceInit.
		 * @return Number of channels
		 */
		virtual gnsdk_uint32_t
		NumberOfChannels() = 0;


		/**
		 * Get audio data from the audio source. This is a blocking call meaning it should
		 * not return until there is data available.
		 * When data is available this method must
		 * copy data to the provided buffer ensuring not to overflow it. The number of bytes
		 * copied to the buffer is returned.
		 * To signal the audio source is unable to deliver anymore data return zero. The
		 * consumer will then stop requesting data and close the audio source.
		 * @param dataBuffer 	[out] Buffer to receive audio data
		 * @param dataSize 		[in]  Size in bytes of buffer
		 * @return Number of bytes copied to the buffer. Return zero to indicate
		 * 		   no more data can be delivered via the audio source.
		 */
		virtual gnsdk_size_t
		GetData(gnsdk_byte_t* dataBuffer, gnsdk_size_t dataSize) = 0;
	};

}  // namespace gracenote

#endif // _GNAUDIOSOURCE_HPP_
