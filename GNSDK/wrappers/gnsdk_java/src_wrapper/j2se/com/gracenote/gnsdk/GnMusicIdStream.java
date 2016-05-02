
package com.gracenote.gnsdk;

/** 
* Identifies raw audio received in a continuous stream. 
* <p> 
* {@link GnMusicIdStream} provides services for identifying music within a continuous audio stream. 
* As data is received from the audio stream it is provided to {@link GnMusicIdStream}, when the application 
* wishes to identify the audio it initializes an identification. The results of the identification 
* are delivered asynchronously to a delegate object. 
* <p> 
* {@link GnMusicIdStream} is a long-life object and, for a single audio stream, a single instance should 
* be kept for as long as the application wishes to identify that audio stream. Where multiple audio 
* streams require identification multiple instances of {@link GnMusicIdStream} are also required. 
* <p> 
* {@link GnMusicIdStream} can be started and stopped as the audio stream starts and stops. There is no need 
* to destroy and recreate a {@link GnMusicIdStream} instance due to breaks in the audio stream. 
* <p> 
* <b>Audio Processing</b> 
* <p> 
* After instantiating a {@link GnMusicIdStream} object the next step is to start audio processing and provide 
* raw audio. Raw audio can be provided automatically or manually. 
* <p> 
* To provide audio automatically your audio stream must be represented by an object that implements 
* {@link IGnAudioSource} interface. Gracenote provides {@link GnMic} class on some platforms which is a representation 
* of the device microphone, though you are encouraged to provide custom implementations representing 
* any audio stream source your application needs. 
* <p> 
* Internally {@link GnMusicIdStream} pulls data from the audio source interface in a loop, so some applications 
* may wish to start automatic audio processing in a background thread to avoid stalling the main thread. 
* <p> 
* Raw audio can also be manually provided to {@link GnMusicIdStream}. Audio processing must be started and the 
* audio format provided, this allows {@link GnMusicIdStream} to establish internal buffers and audio 
* processing modules. Once audio processing is started audio can then be written for processing as 
* it is received from the stream. 
* <p> 
* At any point audio processing can be stopped. When stopped automatic data fetching ceases or 
* if audio data is being provided manually attempts to write data for processing 
* manually will fail. Internally {@link GnMusicIdStream} clears and releases all buffers and audio 
* processing modules. Audio processing can be restarted after it is stopped. 
* <p> 
* If an error occurs during manual audio processing an exception is thrown during the audio write API 
* call. If an error occurs during automatic audio processing the internal loop is exited and an exception 
* thrown from the audio processing start API. 
* <p> 
* <b>Identification</b> 
* <p> 
* At any point the application can trigger an identification of the audio stream. The identification 
* process identifies buffered audio. Only up to ~7 seconds of the most recent audio is buffered. 
* If there isn't enough audio buffered for identification it will wait until enough audio is received. 
* <p> 
* The identification process spawns a thread and completes asynchronously. However two identify methods 
* are provided, one for synchronous and one for asynchronous. Where synchronous identification is invoked the 
* identification is still performed asynchronously and results delivered via delegate implementing 
* {@link IGnMusicIdStreamEvents}, but the identify method does not return until the identification is complete. 
* Requests to identify audio while a previous pending identification request is pending will be ignored. 
* <p> 
* Audio can be identified against Gracenote's online database or a local database. The default 
* behavior is to attempt a match against the local database and if a match isn't found try the 
* online database. Local matches are only possible if {@link GnLookupLocalStream} object has been 
* instantiated and a MusicID-Stream fingerprint bundle ingested. See {@link GnLookupLocalStream} for 
* more information on bundle ingestion. 
* <p> 
* An identification process can be canceled. In this case the identification 
* process stops and, if synchronous identification was invoked, the identify method returns. 
* The identify error delegate method will be called with an "aborted" error when cancelled. 
* Note cancelling does not cease audio processing and application can invoke identify again after 
* cancelling. 
* <p> 
* If an error occurs during identification it is reported in one of two ways. 
* If the error occurs in the asynchronous identifying thread the error information is provided 
* via identifying error delegate method and the result available delegate method will not be called. 
* Where this delegate method is invoked no result available delegate method is invoked. 
* If the error occurs prior to the asynchronous identifying thread being launched an exception 
* is thrown from the identifying API. 
* <p> 
* <b>Configuration</b> 
* <p> 
* {@link GnMusicIdStream} is configurable via it's options object. The configuration determines, among 
* other things, if identification is performed against local database, online database or both; 
* the content returned with results (images, external IDs, etc.) 
* See {@link GnMusicIdStreamOptions} for more information. 
* <p> 
* 
* Note: Customers must be licensed to implement use of a MusicID product in an application. 
* Contact your Gracenote support representative with questions about product licensing and 
* entitlement. 
*/ 
 
public class GnMusicIdStream extends GnObject {
  private long swigCPtr;

  protected GnMusicIdStream(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMusicIdStream_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdStream obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdStream(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnMusicIdStreamEvents pEventDelegate;
	private IGnMusicIdStreamEventsProxyU eventHandlerProxy;
	private IGnAudioSource audioSource;
	private IGnAudioSourceProxyU audioSourceProxyU;
	private GnLocale locale;
	
/** 
* Provides audio manually for processing by {@link GnMusicIdStream}. 
* This should not be called if 
* audio processing was started with an object implementing the audio source interface. 
* @param audioData			[in] Native data buffer containing sample audio 
*/ 
 
	public void audioProcess(byte[] audioData) throws com.gracenote.gnsdk.GnException {
		this.audioProcess(audioData,(long)audioData.length);
  	}

/** 
*  Establishes an audio stream identification object with locale. The locale is used determine 
*  the preferred language and script of stream identification results. 
*  Note: Results are only returned in preferred language and script where available. 
*  @param user 			[in] Gracenote user 
*  @param preset 			[in] Gracenote musicID stream preset 
*  @param locale 			[in] Gracenote locale 
*  @param pEventDelegate 	[in] Audio processing and identification query events handler 
*/ 
 
  public GnMusicIdStream(GnUser user, GnMusicIdStreamPreset preset, GnLocale locale, IGnMusicIdStreamEvents pEventDelegate) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventDelegate != null )
	{
		eventHandlerProxy = new IGnMusicIdStreamEventsProxyU(pEventDelegate);
	}
	this.pEventDelegate = pEventDelegate; // <REFERENCE_NAME_CHECK><TYPE>IGnMusicIdStreamEvents</TYPE><NAME>pEventDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				  // <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnMusicIdStream__SWIG_0(GnUser.getCPtr(user), user, preset.swigValue(), GnLocale.getCPtr(locale), locale, (eventHandlerProxy==null)?0:IGnMusicIdStreamEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

/** 
*  Establishes an audio stream identification object with locale. The locale is used determine 
*  the preferred language and script of stream identification results. 
*  Note: Results are only returned in preferred language and script where available. 
*  @param user 			[in] Gracenote user 
*  @param preset			[in] Gracenote musicID stream preset 
*  @param pEventDelegate 	[in] Audio processing and identification query events handler 
*/ 
 
  public GnMusicIdStream(GnUser user, GnMusicIdStreamPreset preset, IGnMusicIdStreamEvents pEventDelegate) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventDelegate != null )
	{
		eventHandlerProxy = new IGnMusicIdStreamEventsProxyU(pEventDelegate);
	}
	this.pEventDelegate = pEventDelegate; // <REFERENCE_NAME_CHECK><TYPE>IGnMusicIdStreamEvents</TYPE><NAME>pEventDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				  // <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnMusicIdStream__SWIG_1(GnUser.getCPtr(user), user, preset.swigValue(), (eventHandlerProxy==null)?0:IGnMusicIdStreamEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

/** 
*  Retrieves the MusicID-Stream SDK's version string. 
*  @return Version string if successful 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after successfully establishing a MusicID-Stream audio channel. 
*  The returned string is a constant. Do not attempt to modify or delete. 
*  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build) 
*  Major: New functionality 
*  Minor: New or changed features 
*  Improvement: Improvements and fixes 
*  Build: Internal build number 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnMusicIdStream_version();
  }

/** 
*  Retrieves the MusicID-Stream SDK's build date string. 
*  @return Build date string of the format: YYYY-MM-DD hh:mm UTC 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after successfully establishing a MusicID-Stream audio channel. 
*  The returned string is a constant. Do not attempt to modify or delete. 
*  Example build date string: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnMusicIdStream_buildDate();
  }

/** 
* Get {@link GnMusicIdStream} options object. Use to configure your {@link GnMusicIdStream} instance. 
* @return Options objects 
*/ 
 
  public GnMusicIdStreamOptions options() {
    return new GnMusicIdStreamOptions(gnsdk_javaJNI.GnMusicIdStream_options(swigCPtr, this), false);
  }

/** 
* Commence retrieving and processing audio from an object implementing the audio source interface. 
* This is an alternate and often simpler method for providing audio to {@link GnMusicIdStream} 
* instead of calling AudioProcessStart (audio format overload) and AudioProcess. 
* To use this method the audio source to be identified must be accessible via an {@link IGnAudioSource} 
* implementation. Custom implementations of {@link IGnAudioSource} are encouraged. 
* Note: audio is retrieved from the audio source in a loop so some applications may wish to start 
* automatic audio processing in a background thread to avoid stalling the main thread. 
* @param audioSource	[in] Audio source to be identified 
*/ 
 
  public void audioProcessStart(IGnAudioSource audioSource) throws com.gracenote.gnsdk.GnException {
audioSourceProxyU = new IGnAudioSourceProxyU(audioSource);this.audioSource=audioSource; // <REFERENCE_NAME_CHECK><TYPE>IGnAudioSource</TYPE><NAME>audioSource</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
    {
      gnsdk_javaJNI.GnMusicIdStream_audioProcessStart__SWIG_0(swigCPtr, this, IGnAudioSourceProxyL.getCPtr(audioSourceProxyU), audioSourceProxyU);
    }
  }

/** 
* Initialize manual delivery of audio stream audio to {@link GnMusicIdStream}. {@link GnMusicIdStream} 
* establishes buffers and audio processing modules, readying itself to receive audio. 
* @param samplesPerSecond	[in] Number of samples per second 
* @param bitsPerSample		[in] Number of bits per sample 
* @param numberOfChannels	[in] Number of channels 
*/ 
 
  public void audioProcessStart(long samplesPerSecond, long bitsPerSample, long numberOfChannels) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_audioProcessStart__SWIG_1(swigCPtr, this, samplesPerSecond, bitsPerSample, numberOfChannels);
  }

/** 
* Stops audio processing. If audio processing was started with an object implementing {@link IGnAudioSource} 
* the audio source is closed and data is no longer retrieved from that source. If manual audio processing 
* was used future attempts to write audio data for processing will fail. 
*/ 
 
  public void audioProcessStop() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_audioProcessStop(swigCPtr, this);
  }

/** 
* Provides audio manually for processing by {@link GnMusicIdStream}. This should not be called if 
* audio processing was started with an object implementing the audio source interface. 
* @param audioData			[in] Buffer containing sample audio 
* @param audioDataLength	[in] Number of bytes of audio in pAudioBuffer 
*/ 
 
  public void audioProcess(byte[] audioData, long audioDataLength) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_audioProcess__SWIG_0(swigCPtr, this, audioData, audioDataLength);
  }

/** 
* @deprecated Will be removed next release, use IdentifyAlbumAsync and WaitForIdentify instead. 
* Identifying the audio in the audio stream and blocks until identification is 
* complete. Results are delivered asynchronously via {@link IGnMusicIdStreamEvents} delegate. 
*/ 
 
  public void identifyAlbum() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_identifyAlbum(swigCPtr, this);
  }

/** 
* Identifying the audio in the audio stream. Results are delivered 
* asynchronously via {@link IGnMusicIdStreamEvents} delegate. 
*/ 
 
  public void identifyAlbumAsync() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_identifyAlbumAsync(swigCPtr, this);
  }

/** 
* Wait for currently running identify call to complete (up to timeout_ms milliseconds). 
* Returns true if identification completed in the timeout period, false if not 
* @param timeout_ms	[in] Timeout in milliseconds 
* @return true			True if completed, false if timed out 
*/ 
 
  public boolean waitForIdentify(long timeout_ms) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdStream_waitForIdentify(swigCPtr, this, timeout_ms);
  }

/** 
* Cancel the current identify operation blocking until the identification has stopped.  
* Cannot be called from within a {@link GnMusicIdStream} delegate callback, use the canceller provided  
* in the callback instead. This will throw an exception if it is used with the automatic mode  
* on. 
*/ 
 
  public void identifyCancel() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_identifyCancel(swigCPtr, this);
  }

/** 
* Get identify cancel state. 
* @return Cancel state 
*//** 
* Specifies automatic recognition should be enable or disabled 
* @param bEnable 	[in] Option, default is false. True to enable, false to disable 
* <p> 
*/ 
 
  public void automaticIdentifcation(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_automaticIdentifcation__SWIG_0(swigCPtr, this, bEnable);
  }

/** 
* Specifies automatic recognition is enabled or disabled 
* @return true			True if automatic recognition is enabled 
* <p> 
*/ 
 
  public boolean automaticIdentifcation() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdStream_automaticIdentifcation__SWIG_1(swigCPtr, this);
  }

/** 
* Specifies a change in application for a given {@link GnMusicIdStream} 
* @param event 	[in] One of the {@link GnMusicIdStreamApplicationEventType} Enum Values 
* <p> 
*/ 
 
  public void event(GnMusicIdStreamEvent event) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_event(swigCPtr, this, event.swigValue());
  }

/** 
* Provides broadcast metadata to a query handle for improved match resolution 
* @param broadcastMetadataKey 		[in] A brodcast metadata input type from the available MusicIDStream Broadcast Metadata Keys   
* @param broadcastMetadataValue 	[in] A string value that corresponds to the defined broadcast metadata key 
* <p> 
*/ 
 
  public void broadcastMetadata(String broadcastMetadataKey, String broadcastMetadataValue) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_broadcastMetadata(swigCPtr, this, broadcastMetadataKey, broadcastMetadataValue);
  }

/** 
* Get the event handler provided on construction 
* @return Event handler 
*/ 
 
  public IGnMusicIdStreamEvents eventHandler() {
	return pEventDelegate;
}

/** 
* Provides audio manually for processing by {@link GnMusicIdStream}. Data is provided via a 
* native data buffer. 
* This should not be called if 
* audio processing was started with an object implementing the audio source interface. 
* @param dataBuffer	[in] Native data buffer containing sample audio 
* @param dataSize	    [in] Number of bytes of audio in pAudioBuffer 
*/ 
 
  public void audioProcess(java.nio.ByteBuffer dataBuffer, long dataSize) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStream_audioProcess__SWIG_1(swigCPtr, this, dataBuffer, dataSize);
  }

}
