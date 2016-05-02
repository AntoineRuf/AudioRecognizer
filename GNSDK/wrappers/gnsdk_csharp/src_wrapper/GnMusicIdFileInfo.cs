
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  Container class for providing media file information to MusicID-File.
*/
public class GnMusicIdFileInfo : GnObject {
  private HandleRef swigCPtr;

  internal GnMusicIdFileInfo(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdFileInfo obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdFileInfo() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdFileInfo(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
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
*  IGnMusicIdFileEvents or IGnMusicIdFileInfoEvents delegate method call.
*/
  public void FingerprintBegin(uint audioSampleRate, uint audioSampleSize, uint audioChannels) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FingerprintBegin(swigCPtr, audioSampleRate, audioSampleSize, audioChannels);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool FingerprintWrite(byte[] audioData, uint audioDataSize) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FingerprintWrite(swigCPtr, audioData, audioDataSize);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Finalizes fingerprint generation.
*  <p><b>Remarks:</b></p>
*  The application must complete the fingerprinting process by calling
*  fingerprint_end when either the audio data terminates, or after receiving
*  a GNSDK_TRUE value.
*  Use the MusicID-File fingerprinting APIs either before processing has begun, or during a
*  IGnMusicIdFileEvents or IGnMusicIdFileInfoEvents delegate method call.
*/
  public void FingerprintEnd() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FingerprintEnd(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Generate a fingerprint from audio pulled from the provided audio source
*  @param audioSource		[in] audio source representing the file being identified
*/
  public void FingerprintFromSource(IGnAudioSource audioSource) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FingerprintFromSource(swigCPtr, IGnAudioSource.getCPtr(audioSource));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Retrieves the current status for a specific FileInfo object.
*  <p><b>Remarks:</b></p>
*  The File Info object's state value indicates what kind of response is available for a FileInfo object after
*  MusicID-File. In the case of an error, error info can be retrieved from the FileInfo object.
*/
  public GnMusicIdFileInfoStatus Status() {
    GnMusicIdFileInfoStatus ret = (GnMusicIdFileInfoStatus)gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Status(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Retrieves the identifier string from a FileInfo object.
*  @return gnsdk_cstr_t Pointer to receive the data value defined for the identifier
*/
  public string Identifier {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Identifier_get(swigCPtr) );
	} 

  }

/**
*  Get the file name
*  @return File name
*/
  public string FileName {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FileName_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_FileName_get(swigCPtr) );
	} 

  }

/**
*  Gets the Gracenote CDDB ID value from a FileInfo object.
*  @return Identifier
*/
  public string CddbId {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_CddbId_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_CddbId_get(swigCPtr) );
	} 

  }

/**
*  Gets the album artist
*  @return Artist name
*/
  public string AlbumArtist {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_AlbumArtist_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_AlbumArtist_get(swigCPtr) );
	} 

  }

/**
*  Gets the album title
*  @return Album title
*/
  public string AlbumTitle {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_AlbumTitle_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_AlbumTitle_get(swigCPtr) );
	} 

  }

/**
*  Gets the track artist
*  @return Track artist
*/
  public string TrackArtist {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackArtist_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackArtist_get(swigCPtr) );
	} 

  }

/**
*  Gets the track title
*  @return Track title
*/
  public string TrackTitle {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackTitle_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackTitle_get(swigCPtr) );
	} 

  }

/**
*  Gets the tag ID
*  @return Tag identifier
*/
  public string TagId {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TagId_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TagId_get(swigCPtr) );
	} 

  }

/**
*  Gets the fingerprint data
*  @return Fingerprint data
*/
  public string Fingerprint {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Fingerprint_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Fingerprint_get(swigCPtr) );
	} 

  }

/**
*  Gets the media ID
*  @return Media identifier
*/
  public string MediaId {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_MediaId_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_MediaId_get(swigCPtr) );
	} 

  }

/**
*  Gets the Media Unique ID (MUI)
*  @return Media unique identifier
*/
  public string Mui {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Mui_set(swigCPtr, value);
    } 
    get {
      string ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Mui_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Gets the CDTOC value
*  @return CDTOC value
*/
  public string CdToc {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_CdToc_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_CdToc_get(swigCPtr) );
	} 

  }

/**
*  Gets the Title Unique Identifier (Tui)
*  @return Title unique identifier
*/
  public string Tui {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Tui_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_Tui_get(swigCPtr) );
	} 

  }

/**
*  Gets the Tui tag
*  @return Tui tag
*/
  public string TuiTag {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TuiTag_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TuiTag_get(swigCPtr) );
	} 

  }

/**
*  Gets the track number
*  @return Track number
*/
  public uint TrackNumber {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackNumber_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_TrackNumber_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Gets the disc number
*  @return Disc number
*/
  public uint DiscNumber {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_DiscNumber_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_DiscNumber_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Retrieves the album response if available
*  @return Album response
*  <p><b>Remarks:</b></p>
*  This function retrieves the album response object of the match for this file information object if available.
*  Use Status() to determine if a response is available for this file information object.
*/
  public GnResponseAlbums AlbumResponse {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_AlbumResponse_get(swigCPtr);
      GnResponseAlbums ret = (cPtr == IntPtr.Zero) ? null : new GnResponseAlbums(cPtr, true);
      return ret;
    } 
  }

/**
*  Retrieves the data match response if available
*  @return Data match response
*  <p><b>Remarks:</b></p>
*  This function retrieves the data match response object of the match for this file information object if available.
*  Data match responses mean the match could be an album or contributor or a mix thereof depending on the query options.
*  Use Status() to determine if a response is available for this file information object.
*/
  public GnResponseDataMatches DataMatchResponse {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_DataMatchResponse_get(swigCPtr);
      GnResponseDataMatches ret = (cPtr == IntPtr.Zero) ? null : new GnResponseDataMatches(cPtr, true);
      return ret;
    } 
  }

/**
*  Retrieves the error information for a FileInfo object. This is related to the status returned.
*  If the status is error, this call returns the extended error information.
*  <p><b>Remarks:</b></p>
*  An error object is returned representing the FileInfo error condition. An error object exception
*  may be thrown if an error occurred retrieving the FileInfo object's error object.
*/
  public GnError ErrorInformation {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfo_ErrorInformation_get(swigCPtr);
      GnError ret = (cPtr == IntPtr.Zero) ? null : new GnError(cPtr, true);
      return ret;
    } 
  }

}

}
