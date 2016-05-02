
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  Performs bulk audio track recognition
*
*  MusicID-File is intended to be used with collections of file-based media.
*  When an application provides decoded audio and text data for each file to the
*  library, the MusicID-File functionality both identifies each file and groups
*  the files into albums.
*
*  <b>Adding Audio Files</b>
*
*  Each audio file your application wishes to identify must be added to the GnMusicIdFile
*  instance with a unique identifier. The unique identifier is used to correlate
*  identification results and audio files.
*
*  Each audio file is represented by a GnMusicIdFileInfo object. You can use the object
*  to add more information about the audio file, such as textual metadata including
*  track title and artist name, and a fingerprint if the audio file can be decoded to PCM.
*
*  Metadata and fingerprints can be added prior to invoking identification, or as requested
*  by GnMusicIdFile during identification through the IGnMusicIdFileEvents delegate.
*  Gracenote recommends using the delegate as GNSDK requests your application to gather metadata
*  or gather a fingerprint when it's needed and disposes of it as soon as possible. Just-in-time
*  gathering of information means heap memory required to store this information is allocated
*  for the shortest possible time. It's likely an application that adds all information
*  prior to invoking identification will experience higher peak heap usage.
*
*  To prevent exhausting heap memory resources your application must also consider the number
*  of files added to GnMusicIdFile. As each audio file is represented by an object the memory
*  required is directly proportional to the number of audio files added. Your application should
*  consider the constraints of the environment and if necessary split the identification of
*  a large collection into multiple GnMusicIdFile operations.
*
*  <b>Identifying Audio Files</b>
*
*  Once audio files are added to GnMusicIdFile your application can invoke any of
*  the identification algorithms TrackID, AlbumID or LibraryID.
*
*  TrackID identifies each audio file individually, without considering the other
*  audio files added.
*
*  AlbumID considers all audio files added aiming to identify what album a group
*  of tracks belongs to. AlbumID is not suitable for use on a large number of files,
*  your application should only invoke AlbumID on smaller groups of audio files
*  believed to belong to an album.
*
*  LibraryID considers all audio files added and is suitable for use on a large
*  number of audio files. It groups the audio files into smaller batches and
*  performs AlbumID on each batch.
*
*  Where online processing is enabled portions of the audio file resolution into
*  albums is performed within Gracenote Service rather than on the device. Online
*  processing must be allowed by your license.
*
*  Note: An identification algorithm can be invoked multiple times on a single
*  GnMusicIdFile instance, but it will only attempt to identify audio files added
*  since the previous identification concluded. To re-recognize an entire collection
*  ensure you use a new GnMusicIdFile object.
*
*  The identification process executes asynchronously in a worker thread and completed
*  asynchronously. However identify methods are provided for both asynchronous and synchronous
*  execution. Where synchronous identification is invoked the identification is still performed
*  asynchronously and results delivered via delegate implementing IGnMusicIdFileEvents, but the
*  identify method does not return until the identification is complete.
*
*  An identification process can be canceled. In this case the identification
*  process stops and, if synchronous identification was invoked, the identify method returns.
*
*  <b>Processing Results</b>
*
*  As results are received they are provided via the IGnMusicIdFileEvents delegate.
*  Results can be albums or data matches depending on how you invoked the identification
*  algorithm.
*
*  Both types of results provide a mechanism to correlate the result to the matching
*  audio file. For example consider an album response, it may contain multiple albums
*  and each album multiple tracks. Where a GnTrack object matches an audio file it can
*  be queried to return the matched audio file identifier.
*
*  <b>Configuration</b>
*
*  GnMusicIdFile is configurable via it's options object. The configuration determines, among
*  other things, if identification is performed against local database, online database or both;
*  the content returned with results (images, external IDs, etc.)
*  See GnMusicIdFileOptions for more information.
*
*/
public class GnMusicIdFile : GnObject {
  private HandleRef swigCPtr;

  internal GnMusicIdFile(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdFile obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdFile() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdFile(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnMusicIdFile(GnUser user, GnMusicIdFileEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicIdFile__SWIG_0(GnUser.getCPtr(user), GnMusicIdFileEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnMusicIdFile(GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnMusicIdFile__SWIG_1(GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Retrieves the GnMusicIdFileOptions object.
*/
  public GnMusicIdFileOptions Options() {
    GnMusicIdFileOptions ret = new GnMusicIdFileOptions(gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_Options(swigCPtr), false);
    return ret;
  }

/**
*  Initiates TrackId processing.
*
*  @param processType		[in] specifies what you get back
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  TrackId processing performs MusicID-File recognition on each given FileInfo independently
*  and is intended to be used with small number of tracks that do not relate to other tracks in
*  the user’s collection.
*/
  public void DoTrackId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoTrackId(swigCPtr, (int)processType, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Initiates TrackId processing asynchronously.
*
*  @param processType		[in] specifies what you get back
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  TrackId processing performs MusicID-File recognition on each given FileInfo independently
*  and is intended to be used with small number of tracks that do not relate to other tracks in
*  the user’s collection.
*/
  public void DoTrackIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoTrackIdAsync(swigCPtr, (int)processType, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Initiates AlbumId processing.
*
*  @param processType		[in] Process type specifies what you get back
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  AlbumId processing performs MusicID-File recognition on all of the given FileInfos as a group.
*  This type of processing can be more accurate than TrackId processing, as AlbumId processing matches
*  the files to albums. Intended to be used with a small number of related tracks.
*/
  public void DoAlbumId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoAlbumId(swigCPtr, (int)processType, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Initiates AlbumId processing asynchronously .
*
*  @param processType		[in] Process type specifies what you get back
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  AlbumId processing performs MusicID-File recognition on all of the given FileInfos as a group.
*  This type of processing can be more accurate than TrackId processing, as AlbumId processing matches
*  the files to albums. Intended to be used with a small number of related tracks.
*/
  public void DoAlbumIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoAlbumIdAsync(swigCPtr, (int)processType, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Initiates LibraryId processing.
*
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  LibraryId processing performs MusicID-File recognition on a large number of given FileInfos. This
*  processing divides the given group of FileInfos into workable batches, and then processes each batch
*  using AlbumId functionality.
*/
  public void DoLibraryId(GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoLibraryId(swigCPtr, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Initiates LibraryId processing asyncronously
*
*  @param responseType		[in] match response or album response
*
*  <p><b>Remarks:</b></p>
*  LibraryId processing performs MusicID-File recognition on a large number of given FileInfos. This
*  processing divides the given group of FileInfos into workable batches, and then processes each batch
*  using AlbumId functionality.
*/
  public void DoLibraryIdAsync(GnMusicIdFileResponseType responseType) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_DoLibraryIdAsync(swigCPtr, (int)responseType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public static uint kTimeValueInfinite {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_kTimeValueInfinite_set(value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_kTimeValueInfinite_get();
      return ret;
    } 
  }

/**
*  Wait for a MusicID-File operation to complete, wait for the specified number of milliseconds.
*  @param timeoutValue		[in] Length of time to wait in milliseconds
*  <p><b>Remarks:</b></p>
*  Use this function to set a wait for TrackId, AlbumId, or LibraryId processing to complete for
*  a given GnMusicIdFile instance.
*/
  public void WaitForComplete(uint timeoutValue) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_WaitForComplete__SWIG_0(swigCPtr, timeoutValue);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Wait for a MusicID-File operation to complete with infinite wait time.
*  <p><b>Remarks:</b></p>
*  Use this function to set a wait for TrackId, AlbumId, or LibraryId processing to complete for
*  a given GnMusicIdFile instance.
*/
  public void WaitForComplete() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_WaitForComplete__SWIG_1(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnMusicIdFileEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_EventHandler(swigCPtr);
    GnMusicIdFileEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnMusicIdFileEventsDelegate(cPtr, false);
    return ret;
  }

/**
* Set cancel state
*/
  public void Cancel() {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_Cancel(swigCPtr);
  }

/**
*  Retrieves the MusicID-File library's version string.
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully.
*  The returned string is a constant. Do not attempt to modify or delete.
*
*  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
*
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the MusicID-File library's build date string.
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_BuildDate_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the GnMusicIdFileInfoManager object.
*/
  public GnMusicIdFileInfoManager FileInfos {
    get {
      GnMusicIdFileInfoManager ret = new GnMusicIdFileInfoManager(gnsdk_csharp_marshalPINVOKE.GnMusicIdFile_FileInfos_get(swigCPtr), false);
      return ret;
    } 
  }

}

}
