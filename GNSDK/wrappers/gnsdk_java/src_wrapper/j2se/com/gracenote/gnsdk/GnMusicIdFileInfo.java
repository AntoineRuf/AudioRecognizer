
package com.gracenote.gnsdk;

/** 
*  Container class for providing media file information to MusicID-File. 
*/ 
 
public class GnMusicIdFileInfo extends GnObject {
  private long swigCPtr;

  protected GnMusicIdFileInfo(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMusicIdFileInfo_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdFileInfo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdFileInfo(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Provides uncompressed audio data to a file information object for fingerprint generation. 
*  @param audioData [in] set Pointer to audio data buffer that matches the audio format described in fingerprint_begin(). 
*  @return bool Checks whether the fingerprint generation has received enough audio data 
*  <p><b>Remarks:</b></p> 
*  The provided audio data must be uncompressed PCM data and must match the format given to fingerprintBegin(). 
*  True is returned when the fingerprinting process has received 
*  enough audio data to perform its processing. Any further provided audio data is ignored. 
*  The application must provide audio data until true is returned 
*  to successfully generate an audio fingerprint. 
*  The application must complete the fingerprinting process by calling 
*  fingerprintEnd() when either the audio data terminates, or after true is returned. 
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a 
*  {@link IGnMusicIdFileEvents} or {@link IGnMusicIdFileInfoEvents} delegate method call. 
*/ 
 
    public boolean fingerprintWrite(byte[] audioData) throws GnException {
    	return fingerprintWrite(audioData, audioData.length);
    } 

/** 
*  Retrieves the identifier string from a FileInfo object. 
*  @return gnsdk_cstr_t Pointer to receive the data value defined for the identifier 
*/ 
 
  public String identifier() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_identifier(swigCPtr, this);
  }

/** 
*  Get the file name 
*  @return File name 
*/ 
 
  public String fileName() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_fileName__SWIG_0(swigCPtr, this);
  }

/** 
*  Set the file name 
*  @param value			[in] The file name to set 
*/ 
 
  public void fileName(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_fileName__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the Gracenote CDDB ID value from a FileInfo object. 
*  @return Identifier 
*/ 
 
  public String cddbId() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_cddbId__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the Gracenote CDDB ID. 
*  @param value			[in] The Gracenote CDDB ID to set 
*/ 
 
  public void cddbId(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_cddbId__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the album artist 
*  @return Artist name 
*/ 
 
  public String albumArtist() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_albumArtist__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the album artist 
*  @param value			[in] The album artist to set 
*/ 
 
  public void albumArtist(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_albumArtist__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the album title 
*  @return Album title 
*/ 
 
  public String albumTitle() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_albumTitle__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the album title 
*  @param value			[in] The album title to set 
*/ 
 
  public void albumTitle(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_albumTitle__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the track artist 
*  @return Track artist 
*/ 
 
  public String trackArtist() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_trackArtist__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the track artist 
*  @param value			[in] The track artist to use 
*/ 
 
  public void trackArtist(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_trackArtist__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the track title 
*  @return Track title 
*/ 
 
  public String trackTitle() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_trackTitle__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the track title 
*  @param value			[in] The track title to set 
*/ 
 
  public void trackTitle(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_trackTitle__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the track number 
*  @return Track number 
*/ 
 
  public long trackNumber() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_trackNumber__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the track number 
*  @param value			[in] The track number to set 
*/ 
 
  public void trackNumber(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_trackNumber__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the disc number 
*  @return Disc number 
*/ 
 
  public long discNumber() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_discNumber__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the disc number 
*  @param value			[in] The disc number to set 
*/ 
 
  public void discNumber(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_discNumber__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the tag ID 
*  @return Tag identifier 
*/ 
 
  public String tagId() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_tagId__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the tag ID 
*  @param value			[in] The tag ID to set 
*/ 
 
  public void tagId(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_tagId__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the fingerprint data 
*  @return Fingerprint data 
*/ 
 
  public String fingerprint() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_fingerprint__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the fingerprint 
*  @param value			[in] The fingerprint to set 
*/ 
 
  public void fingerprint(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_fingerprint__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the media ID 
*  @return Media identifier 
*/ 
 
  public String mediaId() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_mediaId__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the media ID 
*  @param value			[in] The media ID to set 
*/ 
 
  public void mediaId(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_mediaId__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the Media Unique ID (MUI) 
*  @return Media unique identifier 
*/ 
 
  public String mui() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_mui__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the Media Unique ID (MUI) 
*  @param value			[in] The Media Unique ID (MUI) to set 
*/ 
 
  public void mui(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_mui__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the CDTOC value 
*  @return CDTOC value 
*/ 
 
  public String cdToc() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_cdToc__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the CDTOC value 
*  @param value			[in] The CDTOC to set 
*/ 
 
  public void cdToc(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_cdToc__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the Title Unique Identifier (Tui) 
*  @return Title unique identifier 
*/ 
 
  public String tui() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_tui__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the Title Unique Identifier (Tui) 
*  @param value			[in] The Title Unique Identifier (Tui) to set 
*/ 
 
  public void tui(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_tui__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Gets the Tui tag 
*  @return Tui tag 
*/ 
 
  public String tuiTag() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_tuiTag__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets the Tui tag 
*  @param value			[in] The Tui tag to set 
*/ 
 
  public void tuiTag(String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_tuiTag__SWIG_1(swigCPtr, this, value);
  }

/** 
*  Initializes fingerprint generation. 
*  @param audioSampleRate	[in] set Sample frequency of audio to be provided: 11 kHz, 22 kHz, or 44 kHz 
*  @param audioSampleSize	[in] set Sample rate of audio to be provided (in 8-bit, 16-bit, or 32-bit bytes per sample) 
*  @param audioChannels	[in] set Number of channels for audio to be provided (1 or 2) 
*  <p><b>Remarks:</b></p> 
*  The MusicID-File fingerprinting APIs allow applications to provide audio data as a method of 
*  identification. This enables MusicID-File to perform identification based on the audio itself, as 
*  opposed to performing identification using only the associated metadata. 
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a 
*  {@link IGnMusicIdFileEvents} or {@link IGnMusicIdFileInfoEvents} delegate method call. 
*/ 
 
  public void fingerprintBegin(long audioSampleRate, long audioSampleSize, long audioChannels) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_fingerprintBegin(swigCPtr, this, audioSampleRate, audioSampleSize, audioChannels);
  }

/** 
*  Provides uncompressed audio data for fingerprint generation. 
*  @param audioData 		[in] pointer to audio data buffer that matches the audio format described in FingerprintBegin(). 
*  @param audioDataSize 	[in] size of audio data buffer (in bytes) 
*  @return bool Checks whether the fingerprint generation has received enough audio data 
*  <p><b>Remarks:</b></p> 
*  The provided audio data must be uncompressed PCM data and must match the format given to fingerprintBegin(). 
*  Returns true value when the fingerprinting process has received 
*  enough audio data to perform its processing. Any further provided audio data is ignored. 
*  The application must provide audio data until true is returned 
*  to successfully generate an audio fingerprint. 
*  The application must complete the fingerprinting process by calling 
*  FingerprintEnd() when either the audio data terminates, or after true is returned. 
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a 
*  {@link IGnMusicIdFileEvents} or {@link IGnMusicIdFileInfoEvents} delegate method call. 
*/ 
 
  public boolean fingerprintWrite(byte[] audioData, long audioDataSize) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_fingerprintWrite__SWIG_0(swigCPtr, this, audioData, audioDataSize);
  }

/** 
*  Finalizes fingerprint generation. 
*  <p><b>Remarks:</b></p> 
*  The application must complete the fingerprinting process by calling 
*  fingerprint_end when either the audio data terminates, or after receiving 
*  a GNSDK_TRUE value. 
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a 
*  {@link IGnMusicIdFileEvents} or {@link IGnMusicIdFileInfoEvents} delegate method call. 
*/ 
 
  public void fingerprintEnd() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfo_fingerprintEnd(swigCPtr, this);
  }

/** 
*  Generate a fingerprint from audio pulled from the provided audio source 
*  @param audioSource		[in] audio source representing the file being identified 
*/ 
 
  public void fingerprintFromSource(IGnAudioSource audioSource) throws com.gracenote.gnsdk.GnException {
IGnAudioSourceProxyU audioSourceProxy = new IGnAudioSourceProxyU(audioSource);
    {
      gnsdk_javaJNI.GnMusicIdFileInfo_fingerprintFromSource(swigCPtr, this, IGnAudioSourceProxyL.getCPtr(audioSourceProxy), audioSourceProxy);
    }
  }

/** 
*  Retrieves the current status for a specific FileInfo object. 
*  <p><b>Remarks:</b></p> 
*  The File Info object's state value indicates what kind of response is available for a FileInfo object after 
*  MusicID-File. In the case of an error, error info can be retrieved from the FileInfo object. 
*/ 
 
  public GnMusicIdFileInfoStatus status() throws com.gracenote.gnsdk.GnException {
    return GnMusicIdFileInfoStatus.swigToEnum(gnsdk_javaJNI.GnMusicIdFileInfo_status(swigCPtr, this));
  }

/** 
*  Retrieves the error information for a FileInfo object. This is related to the status returned. 
*  If the status is error, this call returns the extended error information. 
*  <p><b>Remarks:</b></p> 
*  An error object is returned representing the FileInfo error condition. An error object exception 
*  may be thrown if an error occurred retrieving the FileInfo object's error object. 
*/ 
 
  public GnError errorInformation() throws com.gracenote.gnsdk.GnException {
    return new GnError(gnsdk_javaJNI.GnMusicIdFileInfo_errorInformation(swigCPtr, this), true);
  }

/** 
*  Retrieves the album response if available 
*  @return Album response 
*  <p><b>Remarks:</b></p> 
*  This function retrieves the album response object of the match for this file information object if available. 
*  Use Status() to determine if a response is available for this file information object. 
*/ 
 
  public GnResponseAlbums albumResponse() throws com.gracenote.gnsdk.GnException {
    return new GnResponseAlbums(gnsdk_javaJNI.GnMusicIdFileInfo_albumResponse(swigCPtr, this), true);
  }

/** 
*  Retrieves the data match response if available 
*  @return Data match response 
*  <p><b>Remarks:</b></p> 
*  This function retrieves the data match response object of the match for this file information object if available. 
*  Data match responses mean the match could be an album or contributor or a mix thereof depending on the query options. 
*  Use Status() to determine if a response is available for this file information object. 
*/ 
 
  public GnResponseDataMatches dataMatchResponse() throws com.gracenote.gnsdk.GnException {
    return new GnResponseDataMatches(gnsdk_javaJNI.GnMusicIdFileInfo_dataMatchResponse(swigCPtr, this), true);
  }

/** 
*  Provides uncompressed audio data to a file information object for fingerprint generation. 
*  @param audioData 		[in] Native data buffer containing sample audio that matches audio format described in 
*  						fingerprintBegin(). 
*  @param audioDataSize 	[in] set Size of audio data buffer (in bytes) 
*  @return bool Checks whether the fingerprint generation has received enough audio data 
*  <p><b>Remarks:</b></p> 
*  The provided audio data must be uncompressed PCM data and must match the format given to fingerprintBegin(). 
*  True is returned when the fingerprinting process has received 
*  enough audio data to perform its processing. Any further provided audio data is ignored. 
*  The application must provide audio data until true is returned 
*  to successfully generate an audio fingerprint. 
*  The application must complete the fingerprinting process by calling 
*  fingerprintEnd() when either the audio data terminates, or after true is returned. 
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a 
*  {@link IGnMusicIdFileEvents} or {@link IGnMusicIdFileInfoEvents} delegate method call. 
*/ 
 
  public boolean fingerprintWrite(java.nio.ByteBuffer audioData, long audioDataSize) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfo_fingerprintWrite__SWIG_1(swigCPtr, this, audioData, audioDataSize);
  }

}
