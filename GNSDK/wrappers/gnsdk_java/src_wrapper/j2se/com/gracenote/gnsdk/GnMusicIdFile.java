
package com.gracenote.gnsdk;

/** 
*  Performs bulk audio track recognition 
* <p> 
*  MusicID-File is intended to be used with collections of file-based media. 
*  When an application provides decoded audio and text data for each file to the 
*  library, the MusicID-File functionality both identifies each file and groups 
*  the files into albums. 
* <p> 
*  <b>Adding Audio Files</b> 
* <p> 
*  Each audio file your application wishes to identify must be added to the {@link GnMusicIdFile} 
*  instance with a unique identifier. The unique identifier is used to correlate 
*  identification results and audio files. 
* <p> 
*  Each audio file is represented by a {@link GnMusicIdFileInfo} object. You can use the object 
*  to add more information about the audio file, such as textual metadata including 
*  track title and artist name, and a fingerprint if the audio file can be decoded to PCM. 
* <p> 
*  Metadata and fingerprints can be added prior to invoking identification, or as requested 
*  by {@link GnMusicIdFile} during identification through the {@link IGnMusicIdFileEvents} delegate. 
*  Gracenote recommends using the delegate as GNSDK requests your application to gather metadata 
*  or gather a fingerprint when it's needed and disposes of it as soon as possible. Just-in-time 
*  gathering of information means heap memory required to store this information is allocated 
*  for the shortest possible time. It's likely an application that adds all information 
*  prior to invoking identification will experience higher peak heap usage. 
* <p> 
*  To prevent exhausting heap memory resources your application must also consider the number 
*  of files added to {@link GnMusicIdFile}. As each audio file is represented by an object the memory 
*  required is directly proportional to the number of audio files added. Your application should 
*  consider the constraints of the environment and if necessary split the identification of 
*  a large collection into multiple {@link GnMusicIdFile} operations. 
* <p> 
*  <b>Identifying Audio Files</b> 
* <p> 
*  Once audio files are added to {@link GnMusicIdFile} your application can invoke any of 
*  the identification algorithms TrackID, AlbumID or LibraryID. 
* <p> 
*  TrackID identifies each audio file individually, without considering the other 
*  audio files added. 
* <p> 
*  AlbumID considers all audio files added aiming to identify what album a group 
*  of tracks belongs to. AlbumID is not suitable for use on a large number of files, 
*  your application should only invoke AlbumID on smaller groups of audio files 
*  believed to belong to an album. 
* <p> 
*  LibraryID considers all audio files added and is suitable for use on a large 
*  number of audio files. It groups the audio files into smaller batches and 
*  performs AlbumID on each batch. 
* <p> 
*  Where online processing is enabled portions of the audio file resolution into 
*  albums is performed within Gracenote Service rather than on the device. Online 
*  processing must be allowed by your license. 
* <p> 
*  Note: An identification algorithm can be invoked multiple times on a single 
*  {@link GnMusicIdFile} instance, but it will only attempt to identify audio files added 
*  since the previous identification concluded. To re-recognize an entire collection 
*  ensure you use a new {@link GnMusicIdFile} object. 
* <p> 
*  The identification process executes asynchronously in a worker thread and completed 
*  asynchronously. However identify methods are provided for both asynchronous and synchronous 
*  execution. Where synchronous identification is invoked the identification is still performed 
*  asynchronously and results delivered via delegate implementing {@link IGnMusicIdFileEvents}, but the 
*  identify method does not return until the identification is complete. 
* <p> 
*  An identification process can be canceled. In this case the identification 
*  process stops and, if synchronous identification was invoked, the identify method returns. 
* <p> 
*  <b>Processing Results</b> 
* <p> 
*  As results are received they are provided via the {@link IGnMusicIdFileEvents} delegate. 
*  Results can be albums or data matches depending on how you invoked the identification 
*  algorithm. 
* <p> 
*  Both types of results provide a mechanism to correlate the result to the matching 
*  audio file. For example consider an album response, it may contain multiple albums 
*  and each album multiple tracks. Where a {@link GnTrack} object matches an audio file it can 
*  be queried to return the matched audio file identifier. 
* <p> 
*  <b>Configuration</b> 
* <p> 
*  {@link GnMusicIdFile} is configurable via it's options object. The configuration determines, among 
*  other things, if identification is performed against local database, online database or both; 
*  the content returned with results (images, external IDs, etc.) 
*  See {@link GnMusicIdFileOptions} for more information. 
* <p> 
*/ 
 
public class GnMusicIdFile extends GnObject {
  private long swigCPtr;

  protected GnMusicIdFile(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMusicIdFile_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdFile obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdFile(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnMusicIdFileEvents pEventHandler;
	private IGnMusicIdFileEventsProxyU eventHandlerProxy;

/** 
*  Constructs an audio track identification object 
*  @param user 			[in] Gracenote user object representing the user making the {@link GnMusicIdFile} request 
*  @param pEventHandler	[in] Delegate object for receiving processing events 
*/ 
 
  public GnMusicIdFile(GnUser user, IGnMusicIdFileEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnMusicIdFileEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnMusicIdFileEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnMusicIdFile__SWIG_0(GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnMusicIdFileEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

/** 
*  Constructs an audio track identification object 
*  @param user 			[in] Gracenote user object representing the user making the {@link GnMusicIdFile} request 
*/ 
 
  public GnMusicIdFile(GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnMusicIdFileEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnMusicIdFileEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnMusicIdFile__SWIG_1(GnUser.getCPtr(user), user);
}

/** 
*  Retrieves the MusicID-File library's version string. 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. 
*  The returned string is a constant. Do not attempt to modify or delete. 
* <p> 
*  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build) 
* <p> 
*  Major: New functionality 
*  Minor: New or changed features 
*  Improvement: Improvements and fixes 
*  Build: Internal build number 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnMusicIdFile_version();
  }

/** 
*  Retrieves the MusicID-File library's build date string. 
*  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. 
*  The returned string is a constant. Do not attempt to modify or delete. 
* <p> 
*  Example build date string: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnMusicIdFile_buildDate();
  }

/** 
*  Retrieves the {@link GnMusicIdFileOptions} object. 
*/ 
 
  public GnMusicIdFileOptions options() {
    return new GnMusicIdFileOptions(gnsdk_javaJNI.GnMusicIdFile_options(swigCPtr, this), false);
  }

/** 
*  Retrieves the {@link GnMusicIdFileInfoManager} object. 
*/ 
 
  public GnMusicIdFileInfoManager fileInfos() {
    return new GnMusicIdFileInfoManager(gnsdk_javaJNI.GnMusicIdFile_fileInfos(swigCPtr, this), false);
  }

/** 
*  Initiates TrackId processing. 
* <p> 
*  @param processType		[in] specifies what you get back 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  TrackId processing performs MusicID-File recognition on each given FileInfo independently 
*  and is intended to be used with small number of tracks that do not relate to other tracks in 
*  the user’s collection. 
*/ 
 
  public void doTrackId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doTrackId(swigCPtr, this, processType.swigValue(), responseType.swigValue());
  }

/** 
*  Initiates TrackId processing asynchronously. 
* <p> 
*  @param processType		[in] specifies what you get back 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  TrackId processing performs MusicID-File recognition on each given FileInfo independently 
*  and is intended to be used with small number of tracks that do not relate to other tracks in 
*  the user’s collection. 
*/ 
 
  public void doTrackIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doTrackIdAsync(swigCPtr, this, processType.swigValue(), responseType.swigValue());
  }

/** 
*  Initiates AlbumId processing. 
* <p> 
*  @param processType		[in] Process type specifies what you get back 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  AlbumId processing performs MusicID-File recognition on all of the given FileInfos as a group. 
*  This type of processing can be more accurate than TrackId processing, as AlbumId processing matches 
*  the files to albums. Intended to be used with a small number of related tracks. 
*/ 
 
  public void doAlbumId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doAlbumId(swigCPtr, this, processType.swigValue(), responseType.swigValue());
  }

/** 
*  Initiates AlbumId processing asynchronously . 
* <p> 
*  @param processType		[in] Process type specifies what you get back 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  AlbumId processing performs MusicID-File recognition on all of the given FileInfos as a group. 
*  This type of processing can be more accurate than TrackId processing, as AlbumId processing matches 
*  the files to albums. Intended to be used with a small number of related tracks. 
*/ 
 
  public void doAlbumIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doAlbumIdAsync(swigCPtr, this, processType.swigValue(), responseType.swigValue());
  }

/** 
*  Initiates LibraryId processing. 
* <p> 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  LibraryId processing performs MusicID-File recognition on a large number of given FileInfos. This 
*  processing divides the given group of FileInfos into workable batches, and then processes each batch 
*  using AlbumId functionality. 
*/ 
 
  public void doLibraryId(GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doLibraryId(swigCPtr, this, responseType.swigValue());
  }

/** 
*  Initiates LibraryId processing asyncronously 
* <p> 
*  @param responseType		[in] match response or album response 
* <p> 
*  <p><b>Remarks:</b></p> 
*  LibraryId processing performs MusicID-File recognition on a large number of given FileInfos. This 
*  processing divides the given group of FileInfos into workable batches, and then processes each batch 
*  using AlbumId functionality. 
*/ 
 
  public void doLibraryIdAsync(GnMusicIdFileResponseType responseType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_doLibraryIdAsync(swigCPtr, this, responseType.swigValue());
  }

/** 
*  Wait for a MusicID-File operation to complete, wait for the specified number of milliseconds. 
*  @param timeoutValue		[in] Length of time to wait in milliseconds 
*  <p><b>Remarks:</b></p> 
*  Use this function to set a wait for TrackId, AlbumId, or LibraryId processing to complete for 
*  a given {@link GnMusicIdFile} instance. 
*/ 
 
  public void waitForComplete(long timeoutValue) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_waitForComplete__SWIG_0(swigCPtr, this, timeoutValue);
  }

/** 
*  Wait for a MusicID-File operation to complete with infinite wait time. 
*  <p><b>Remarks:</b></p> 
*  Use this function to set a wait for TrackId, AlbumId, or LibraryId processing to complete for 
*  a given {@link GnMusicIdFile} instance. 
*/ 
 
  public void waitForComplete() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFile_waitForComplete__SWIG_1(swigCPtr, this);
  }

/** 
* Get the event handler provided on construction 
* @return Event handler 
*/ 
 
  public IGnMusicIdFileEvents eventHandler() {
	return pEventHandler;
}

/** 
* Set cancel state 
*/ 
 
  public void cancel() {
    gnsdk_javaJNI.GnMusicIdFile_cancel(swigCPtr, this);
  }

}
