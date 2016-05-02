package com.gracenote.gnsdk;

/** 
* Delegate interface for retrieving audio data from an audio source such as a microphone, audio file 
* or Internet stream. 
* Various Gracenote methods consume audio data via audio sources, allowing the transfer 
* of audio from the audio source to the consumer without requiring the application to 
* manually pass the data. This can simplify the application's implementation. 
* Applications are encouraged to implement their own audio source objects, or example if 
* custom audio file format is used an application may implement an {@link IGnAudioSource} interface to 
* the custom audio format decoder. 
*/ 
 
public interface IGnAudioSource {

/** 
* Initialize the audio source. This will be invoked prior to any other methods. If initialization 
* fails return a non-zero value. In this case the consumer will not call any other methods 
* including that to close the audio source. 
* @return 0 indicates initialization was successful, non-zero otherwise. 
*/ 
 
  	public long sourceInit();

/** 
* Close the audio source. The consumer will not call any other methods after the source has 
* been closed 
*/ 
 
  	public void sourceClose();

/** 
* Return the number of samples per second of the source audio format. Returns zero if called 
* prior to SourceInit. 
* @return Samples per second 
*/ 
 
  	public long samplesPerSecond();

/** 
* Return the number of bits in a sample of the source audio format. Returns zero if called 
* prior to SourceInit. 
* @return Sample size in bits 
*/ 
 
  	public long sampleSizeInBits();

/** 
* Return the number of channels of the source audio format. Returns zero if called 
* prior to SourceInit. 
* @return Number of channels 
*/ 
 
  	public long numberOfChannels();

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
 
  	public long getData(java.nio.ByteBuffer dataBuffer, long dataSize);
  	
}
