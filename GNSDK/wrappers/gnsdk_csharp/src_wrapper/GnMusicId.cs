
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  \class GnMusicId
*  Provides services for audio recognition using CD TOC-based search,
*  text-based search, fingerprint, and identifier lookup functionality.
*
*  GnMusicId is a one-shot object, meaning it's life time is scoped to a single
*  recognition event and your application should create a new one for each
*  recognition.
*
*  Recognition can be performed with various inputs, including text inputs, for
*  a text search; identifiers, to retrieve a response for a known Gracenote database
*  record; plus others.
*
*  Recognitions can also be targeted or generic. A targeted
*  search for only albums can be invoked via any FindAlbums methods, while a
*  generic search can be performed using any FindMatches method.
*
*  During a recognition event status events can be received via a delegate object
*  that implements IGnStatusEvents.
*
*  A recognition event can be cancelled by the GnMusicId cancel method or by the
*  "canceller" provided in each events delegate method.
*
*  GnMusicId recognition events are performed synchronously, with the response object
*  returned to your application.
*
*  GnMusicId can also generate fingerprint data from raw audio. Generating fingerprints
*  is preferred when a device cannot immediately perform recognition, perhaps because it
*  is temporarily disconnected from the Internet, and wishes to do so later. Fingerprint
*  data is much smaller that raw audio, putting less demand on storage resources.
*
*  GnMusicId is configurable via it's options object. See GnMusicIdOptions for more
*  information.
*
*  Note: Customers must be licensed to implement use of a MusicID product in an application.
*  Contact your Gracenote support representative with questions about product licensing and
*  entitlement.
*/
public class GnMusicId : GnObject {
  private HandleRef swigCPtr;

  internal GnMusicId(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMusicId_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicId obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicId() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicId(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Constructs a music identification query object with a Gracenote user and event delegate
*  @param user          [in] Set GnUser object representing the user making the GnMusicId request
*  @param pEventHandler [in-opt] Set Optional status event handler to get bytes sent, received, or completed.
*/
  public GnMusicId(GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicId__SWIG_0(GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnMusicId(GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicId__SWIG_1(GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Constructs a music identification query object with a Gracenote user, locale and event delegate
*  @param user          [in] Set GnUser object representing the user making the GnMusicId request
*  @param locale		 [in] Locale representing region and language preferred for MusicID-Stream responses
*  @param pEventHandler [in-opt] Set Optional status event handler to get bytes sent, received, or completed.
*/
  public GnMusicId(GnUser user, GnLocale locale, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicId__SWIG_2(GnUser.getCPtr(user), GnLocale.getCPtr(locale), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnMusicId(GnUser user, GnLocale locale) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicId__SWIG_3(GnUser.getCPtr(user), GnLocale.getCPtr(locale)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Retrieves externally- and internally-generated Gracenote
*  fingerprint Extraction (GNFPX) or Cantametrix (CMX) fingerprint data.
*  @return String fingerprint data
*/
  public string FingerprintDataGet() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnMusicId_FingerprintDataGet(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Initializes native fingerprint generation for a MusicID query.
*  @param fpType 			[in] One of the GnFingerprintType fingerprint data types,
*  						either Gracenote Fingerprint Extraction (GNFPX) or Cantametrix (CMX)
*  @param audioSampleRate 	[in] Sample rate of audio to be provided in Hz (for example,44100)
*  @param audioSampleSize 	[in] Size of a single sample of audio to be provided: 8 for 8-bit audio
*  						(0-255 integers), 16 for 16-bit audio , and 32 for 32-bit audio (floating point)
*  @param audioChannels 	[in] Number of channels for audio to be provided (1 or 2)
*/
  public void FingerprintBegin(GnFingerprintType fpType, uint audioSampleRate, uint audioSampleSize, uint audioChannels) {
    gnsdk_csharp_marshalPINVOKE.GnMusicId_FingerprintBegin(swigCPtr, (int)fpType, audioSampleRate, audioSampleSize, audioChannels);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool FingerprintWrite(byte[] audioData, uint audioDataSize) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnMusicId_FingerprintWrite(swigCPtr, audioData, audioDataSize);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Finalizes native fingerprint generation for a MusicID query handle.
*  <p><b>Remarks:</b></p>
*  Call this API when the audio stream ends; this alerts the system that it has received all the
*  available audio for the particular stream.
*  If FingerprintWrite() returns True before the stream ends, we recommend that you:
*  <ul>
*  <li>Stop providing audio at that time, since enough has been received.
*  <li>Do not FingerprintEnd(), as this is unnecessary.
*  </ul>
*  Fingerprints may be generated based on the call to this API; however, this is not guaranteed.
*/
  public void FingerprintEnd() {
    gnsdk_csharp_marshalPINVOKE.GnMusicId_FingerprintEnd(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Creates a fingerprint from the given audio stream represented by an implementation
*  of IGnAudioSource. Once completed call FingerprintDataGet() for cases where the application needs
*  to retrieve the raw fingerprint value from storage.
*  This is an alternate and often simpler method for generating a
*  fingerprint instead of calling FingerprintBegin, FingerprintWrite and FingerprintEnd.
*  To use this method the audio source to be fingerprinted must be accessible via an IGnAudioSource
*  implementation. Custom implementations of IGnAudioSource are encouraged.
*  @param audioSource		[in] Audio source to fingerprint
*  @param fpType			[in] One of the GnFingerprintType fingerprint data types,
*  						either Gracenote Fingerprint Extraction (GNFPX) or Cantametrix (CMX)
*/
  public void FingerprintFromSource(IGnAudioSource audioSource, GnFingerprintType fpType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicId_FingerprintFromSource(swigCPtr, IGnAudioSource.getCPtr(audioSource), (int)fpType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Performs a MusicID query for album results based on text input .
*  @param albumTitle           [in] Album title
*  @param trackTitle           [in] Track title
*  @param albumArtistName      [in] Album Artist name
*  @param trackArtistName      [in] Track Artist name
*  @param composerName         [in] Album Composer ( e.g. Classical, Instrumental, Movie Score)
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(string albumTitle, string trackTitle, string albumArtistName, string trackArtistName, string composerName) {
  System.IntPtr tempalbumTitle = GnMarshalUTF8.NativeUtf8FromString(albumTitle);
  System.IntPtr temptrackTitle = GnMarshalUTF8.NativeUtf8FromString(trackTitle);
  System.IntPtr tempalbumArtistName = GnMarshalUTF8.NativeUtf8FromString(albumArtistName);
  System.IntPtr temptrackArtistName = GnMarshalUTF8.NativeUtf8FromString(trackArtistName);
  System.IntPtr tempcomposerName = GnMarshalUTF8.NativeUtf8FromString(composerName);
    try {
      GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_0(swigCPtr, tempalbumTitle, temptrackTitle, tempalbumArtistName, temptrackArtistName, tempcomposerName), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempalbumTitle);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(temptrackTitle);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempalbumArtistName);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(temptrackArtistName);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempcomposerName);
    }
  }

/**
*  Performs a MusicID query for album results using CD TOC
*  @param CDTOC             [in] Compact Disc Table Of Contents
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
*  Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(string CDTOC) {
    GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_1(swigCPtr, CDTOC), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a MusicID query for album results using CD TOC togther with fingerprint data
*  @param CDTOC             	[in] Compact Disc Table Of Contents
*  @param strFingerprintData	[in] Fingerprint data
*  @param fpType            	[in] One of the #GnFingerprintType fingerprint types
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
*  Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(string CDTOC, string strFingerprintData, GnFingerprintType fpType) {
  System.IntPtr tempstrFingerprintData = GnMarshalUTF8.NativeUtf8FromString(strFingerprintData);
    try {
      GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_2(swigCPtr, CDTOC, tempstrFingerprintData, (int)fpType), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempstrFingerprintData);
    }
  }

/**
*  Performs a MusicID query for album results using fingerprint data and finger print type.
*  @param fingerprintData 	[in] Fingerprint data
*  @param fpType 			[in] One of the #GnFingerprintType fingerprint types
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(string fingerprintData, GnFingerprintType fpType) {
    GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_3(swigCPtr, fingerprintData, (int)fpType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a MusicID query for album results.
*  @param gnDataObject      [in] Gracenote data object
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(GnDataObject gnDataObject) {
    GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_4(swigCPtr, GnDataObject.getCPtr(gnDataObject)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a MusicID query for album results.
*  @param audioSource     	[in] A valid IGnAudioSource object.
*  @param fpType 			[in] One of the #GnFingerprintType fingerprint types
*  @return An instance of GnResponseAlbums that contain Album metadata.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseAlbums FindAlbums(IGnAudioSource audioSource, GnFingerprintType fpType) {
    GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindAlbums__SWIG_5(swigCPtr, IGnAudioSource.getCPtr(audioSource), (int)fpType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a MusicID query for best Matches results, being GnAlbum and/or GnContributor matches ordered in priority.
*  @param albumTitle             [in] Album title
*  @param trackTitle             [in] Track title
*  @param albumArtistName        [in] Album Artist name
*  @param trackArtistName        [in] Track Artist name
*  @param composerName           [in] Album Composer ( e.g. Classical, Instrumental, Movie Score)
*  @return Response containing Album, Track and Artist metadata.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnResponseDataMatches FindMatches(string albumTitle, string trackTitle, string albumArtistName, string trackArtistName, string composerName) {
  System.IntPtr tempalbumTitle = GnMarshalUTF8.NativeUtf8FromString(albumTitle);
  System.IntPtr temptrackTitle = GnMarshalUTF8.NativeUtf8FromString(trackTitle);
  System.IntPtr tempalbumArtistName = GnMarshalUTF8.NativeUtf8FromString(albumArtistName);
  System.IntPtr temptrackArtistName = GnMarshalUTF8.NativeUtf8FromString(trackArtistName);
  System.IntPtr tempcomposerName = GnMarshalUTF8.NativeUtf8FromString(composerName);
    try {
      GnResponseDataMatches ret = new GnResponseDataMatches(gnsdk_csharp_marshalPINVOKE.GnMusicId_FindMatches(swigCPtr, tempalbumTitle, temptrackTitle, tempalbumArtistName, temptrackArtistName, tempcomposerName), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempalbumTitle);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(temptrackTitle);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempalbumArtistName);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(temptrackArtistName);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempcomposerName);
    }
  }

/**
* Get the event handler provided on construction
* @return Event handler
*/
  public GnStatusEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicId_EventHandler(swigCPtr);
    GnStatusEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnStatusEventsDelegate(cPtr, false);
    return ret;
  }

/**
* Get GnMusicId options object. Use to configure your GnMusicId instance.
* @return Options objects
*/
  public GnMusicIdOptions Options() {
    GnMusicIdOptions ret = new GnMusicIdOptions(gnsdk_csharp_marshalPINVOKE.GnMusicId_Options(swigCPtr), false);
    return ret;
  }

/**
* Set cancel state
* @param bCancel 	[in] Cancel state
*/
  public virtual void SetCancel(bool bCancel) {
    gnsdk_csharp_marshalPINVOKE.GnMusicId_SetCancel(swigCPtr, bCancel);
  }

/**
* Get cancel state.
* @return Cancel state
*/
  public virtual bool IsCancelled() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnMusicId_IsCancelled(swigCPtr);
    return ret;
  }

/**
*  Retrieves the MusicID library version string.
*  @return gnsdk_cstr_t Version string, if successful
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully.
*  The returned string is a constant. Do not attempt to modify or delete.
*
*  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
*
*  Major: New functionality
*
*  Minor: New or changed features
*
*  Improvement: Improvements and fixes
*
*  Build: Internal build number
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicId_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the MusicID SDK's build date string.
*  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully.
*  The returned string is a constant. Do not attempt to modify or delete.
*
*  Example build date string: 2008-02-12 00:41 UTC
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicId_BuildDate_get(swigCPtr) );
	} 

  }

}

}
