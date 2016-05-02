
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Identifies raw audio received in a continuous stream.
*
* GnMusicIdStream provides services for identifying music within a continuous audio stream.
* As data is received from the audio stream it is provided to GnMusicIdStream, when the application
* wishes to identify the audio it initializes an identification. The results of the identification
* are delivered asynchronously to a delegate object.
*
* GnMusicIdStream is a long-life object and, for a single audio stream, a single instance should
* be kept for as long as the application wishes to identify that audio stream. Where multiple audio
* streams require identification multiple instances of GnMusicIdStream are also required.
*
* GnMusicIdStream can be started and stopped as the audio stream starts and stops. There is no need
* to destroy and recreate a GnMusicIdStream instance due to breaks in the audio stream.
*
* <b>Audio Processing</b>
*
* After instantiating a GnMusicIdStream object the next step is to start audio processing and provide
* raw audio. Raw audio can be provided automatically or manually.
*
* To provide audio automatically your audio stream must be represented by an object that implements
* IGnAudioSource interface. Gracenote provides GnMic class on some platforms which is a representation
* of the device microphone, though you are encouraged to provide custom implementations representing
* any audio stream source your application needs.
*
* Internally GnMusicIdStream pulls data from the audio source interface in a loop, so some applications
* may wish to start automatic audio processing in a background thread to avoid stalling the main thread.
*
* Raw audio can also be manually provided to GnMusicIdStream. Audio processing must be started and the
* audio format provided, this allows GnMusicIdStream to establish internal buffers and audio
* processing modules. Once audio processing is started audio can then be written for processing as
* it is received from the stream.
*
* At any point audio processing can be stopped. When stopped automatic data fetching ceases or
* if audio data is being provided manually attempts to write data for processing
* manually will fail. Internally GnMusicIdStream clears and releases all buffers and audio
* processing modules. Audio processing can be restarted after it is stopped.
*
* If an error occurs during manual audio processing an exception is thrown during the audio write API
* call. If an error occurs during automatic audio processing the internal loop is exited and an exception
* thrown from the audio processing start API.
*
* <b>Identification</b>
*
* At any point the application can trigger an identification of the audio stream. The identification
* process identifies buffered audio. Only up to ~7 seconds of the most recent audio is buffered.
* If there isn't enough audio buffered for identification it will wait until enough audio is received.
*
* The identification process spawns a thread and completes asynchronously. However two identify methods
* are provided, one for synchronous and one for asynchronous. Where synchronous identification is invoked the
* identification is still performed asynchronously and results delivered via delegate implementing
* IGnMusicIdStreamEvents, but the identify method does not return until the identification is complete.
* Requests to identify audio while a previous pending identification request is pending will be ignored.
*
* Audio can be identified against Gracenote's online database or a local database. The default
* behavior is to attempt a match against the local database and if a match isn't found try the
* online database. Local matches are only possible if GnLookupLocalStream object has been
* instantiated and a MusicID-Stream fingerprint bundle ingested. See GnLookupLocalStream for
* more information on bundle ingestion.
*
* An identification process can be canceled. In this case the identification
* process stops and, if synchronous identification was invoked, the identify method returns.
* The identify error delegate method will be called with an "aborted" error when cancelled.
* Note cancelling does not cease audio processing and application can invoke identify again after
* cancelling.
*
* If an error occurs during identification it is reported in one of two ways.
* If the error occurs in the asynchronous identifying thread the error information is provided
* via identifying error delegate method and the result available delegate method will not be called.
* Where this delegate method is invoked no result available delegate method is invoked.
* If the error occurs prior to the asynchronous identifying thread being launched an exception
* is thrown from the identifying API.
*
* <b>Configuration</b>
*
* GnMusicIdStream is configurable via it's options object. The configuration determines, among
* other things, if identification is performed against local database, online database or both;
* the content returned with results (images, external IDs, etc.)
* See GnMusicIdStreamOptions for more information.
*
*
* Note: Customers must be licensed to implement use of a MusicID product in an application.
* Contact your Gracenote support representative with questions about product licensing and
* entitlement.
*/
public class GnMusicIdStream : GnObject {
  private HandleRef swigCPtr;

  internal GnMusicIdStream(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdStream obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdStream() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdStream(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
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
  public GnMusicIdStream(GnUser user, GnMusicIdStreamPreset preset, GnLocale locale, GnMusicIdStreamEventsDelegate pEventDelegate) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicIdStream__SWIG_0(GnUser.getCPtr(user), (int)preset, GnLocale.getCPtr(locale), GnMusicIdStreamEventsDelegate.getCPtr(pEventDelegate)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Establishes an audio stream identification object with locale. The locale is used determine
*  the preferred language and script of stream identification results.
*  Note: Results are only returned in preferred language and script where available.
*  @param user 			[in] Gracenote user
*  @param preset			[in] Gracenote musicID stream preset
*  @param pEventDelegate 	[in] Audio processing and identification query events handler
*/
  public GnMusicIdStream(GnUser user, GnMusicIdStreamPreset preset, GnMusicIdStreamEventsDelegate pEventDelegate) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicIdStream__SWIG_1(GnUser.getCPtr(user), (int)preset, GnMusicIdStreamEventsDelegate.getCPtr(pEventDelegate)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
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
  public static string Version() {
	IntPtr temp = gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_Version(); 
	return GnMarshalUTF8.StringFromNativeUtf8(temp);
}

/**
*  Retrieves the MusicID-Stream SDK's build date string.
*  @return Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after successfully establishing a MusicID-Stream audio channel.
*  The returned string is a constant. Do not attempt to modify or delete.
*  Example build date string: 2008-02-12 00:41 UTC
*/
  public static string BuildDate() {
	IntPtr temp = gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_BuildDate(); 
	return GnMarshalUTF8.StringFromNativeUtf8(temp);
}

/**
* Get GnMusicIdStream options object. Use to configure your GnMusicIdStream instance.
* @return Options objects
*/
  public GnMusicIdStreamOptions Options() {
    GnMusicIdStreamOptions ret = new GnMusicIdStreamOptions(gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_Options(swigCPtr), false);
    return ret;
  }

/**
* Commence retrieving and processing audio from an object implementing the audio source interface.
* This is an alternate and often simpler method for providing audio to GnMusicIdStream
* instead of calling AudioProcessStart (audio format overload) and AudioProcess.
* To use this method the audio source to be identified must be accessible via an IGnAudioSource
* implementation. Custom implementations of IGnAudioSource are encouraged.
* Note: audio is retrieved from the audio source in a loop so some applications may wish to start
* automatic audio processing in a background thread to avoid stalling the main thread.
* @param audioSource	[in] Audio source to be identified
*/
  public void AudioProcessStart(IGnAudioSource audioSource) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AudioProcessStart__SWIG_0(swigCPtr, IGnAudioSource.getCPtr(audioSource));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Initialize manual delivery of audio stream audio to GnMusicIdStream. GnMusicIdStream
* establishes buffers and audio processing modules, readying itself to receive audio.
* @param samplesPerSecond	[in] Number of samples per second
* @param bitsPerSample		[in] Number of bits per sample
* @param numberOfChannels	[in] Number of channels
*/
  public void AudioProcessStart(uint samplesPerSecond, uint bitsPerSample, uint numberOfChannels) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AudioProcessStart__SWIG_1(swigCPtr, samplesPerSecond, bitsPerSample, numberOfChannels);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Stops audio processing. If audio processing was started with an object implementing IGnAudioSource
* the audio source is closed and data is no longer retrieved from that source. If manual audio processing
* was used future attempts to write audio data for processing will fail.
*/
  public void AudioProcessStop() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AudioProcessStop(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AudioProcess(byte[] audioData, uint audioDataLength) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AudioProcess(swigCPtr, audioData, audioDataLength);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* @deprecated Will be removed next release, use IdentifyAlbumAsync and WaitForIdentify instead.
* Identifying the audio in the audio stream and blocks until identification is
* complete. Results are delivered asynchronously via IGnMusicIdStreamEvents delegate.
*/
  public void IdentifyAlbum() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_IdentifyAlbum(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Identifying the audio in the audio stream. Results are delivered
* asynchronously via IGnMusicIdStreamEvents delegate.
*/
  public void IdentifyAlbumAsync() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_IdentifyAlbumAsync(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Wait for currently running identify call to complete (up to timeout_ms milliseconds).
* Returns true if identification completed in the timeout period, false if not
* @param timeout_ms	[in] Timeout in milliseconds
* @return true			True if completed, false if timed out
*/
  public bool WaitForIdentify(uint timeout_ms) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_WaitForIdentify(swigCPtr, timeout_ms);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Cancel the current identify operation blocking until the identification has stopped. 
* Cannot be called from within a GnMusicIdStream delegate callback, use the canceller provided 
* in the callback instead. This will throw an exception if it is used with the automatic mode 
* on.
*/
  public void IdentifyCancel() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_IdentifyCancel(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Get identify cancel state.
* @return Cancel state
*//**
* Specifies automatic recognition should be enable or disabled
* @param bEnable 	[in] Option, default is false. True to enable, false to disable
*
*/
  public void AutomaticIdentifcation(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AutomaticIdentifcation__SWIG_0(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Specifies automatic recognition is enabled or disabled
* @return true			True if automatic recognition is enabled
*
*/
  public bool AutomaticIdentifcation() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_AutomaticIdentifcation__SWIG_1(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Specifies a change in application for a given GnMusicIdStream
* @param event 	[in] One of the GnMusicIdStreamApplicationEventType Enum Values
*
*/
  public void Event(GnMusicIdStreamEvent arg0) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_Event(swigCPtr, (int)arg0);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Provides broadcast metadata to a query handle for improved match resolution
* @param broadcastMetadataKey 		[in] A brodcast metadata input type from the available MusicIDStream Broadcast Metadata Keys  
* @param broadcastMetadataValue 	[in] A string value that corresponds to the defined broadcast metadata key
*
*/
  public void BroadcastMetadata(string broadcastMetadataKey, string broadcastMetadataValue) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_BroadcastMetadata(swigCPtr, broadcastMetadataKey, broadcastMetadataValue);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Get the event handler provided on construction
* @return Event handler
*/
  public GnMusicIdStreamEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicIdStream_EventHandler(swigCPtr);
    GnMusicIdStreamEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnMusicIdStreamEventsDelegate(cPtr, false);
    return ret;
  }

}

}
