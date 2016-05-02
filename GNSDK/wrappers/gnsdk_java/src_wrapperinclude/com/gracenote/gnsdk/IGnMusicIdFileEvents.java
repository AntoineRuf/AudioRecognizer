package com.gracenote.gnsdk;

/** 
*  Delegate interface for receiving data retrieval and status updates as various 
*  MusicID-File operations are performed 
*/ 
 
public interface IGnMusicIdFileEvents extends IGnStatusEvents {

/** 
*  Retrieves the current status. 
*  @param fileInfo 		[in] FileInfo object that the callback operates on 
*  @param status 			[in] FileInfo status 
*  @param currentFile 		[in] Current number of the file being processed 
*  @param totalFiles 		[in] Total number of files to be processed by the callback 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*/ 
 
	public void musicIdFileStatusEvent(GnMusicIdFileInfo fileInfo, GnMusicIdFileCallbackStatus status, long currentFile, long totalFiles, IGnCancellable canceller);

/** 
*  Callback function declaration for a fingerprint generation request. 
*  @param fileInfo 		[in] FileInfo object that the callback operates on 
*  @param currentFile  	[in] Current number of the file being processed 
*  @param totalFiles 		[in] Total number of files to be processed 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*  <p><b>Remarks:</b></p> 
*  The application can implement this callback to use the fingerprint_begin(), fingerprint_write() and fingerprint_end() APIs with the given FileInfo object to 
			   generate a fingerprint from raw audio. If your application already has created the fingerprint for the respective file, 
			   the application should implement this callback to use the GnMusicIdFileInfo.set*() API to set any metadata values in the FileInfo object. 
			   This callback is called only if no fingerprint has already been set for the passed FileInfo object. 
*/ 
 
  	public void gatherFingerprint(GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller);

/** 
*  Callback function declaration for a metadata gathering request. 
*  @param fileInfo 		[in] FileInfo object that the callback operates on 
*  @param currentFile 		[in] Current number of the file being processed 
*  @param totalFiles 		[in] Total number of files to be processed 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*  <p><b>Remarks:</b></p> 
*   The application should implement this callback to use the GnMusicIdFileInfo.set*() API to set any metadata values in the FileInfo object. 
			   This callback is called only if no metadata has already been set for the passed FileInfo. 
*/ 
 
  	public void gatherMetadata(GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller);

/** 
*  Callback function declaration for a result available notification. 
*  @param albumResult  	[in] Album response 
*  @param currentAlbum 	[in] Current number of the album in this response 
*  @param totalAlbums 		[in] Total number of albums in this response 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*  <p><b>Remarks:</b></p> 
*  The provided response will include results for one or more files. 
*/ 
 
  	public void musicIdFileAlbumResult(GnResponseAlbums albumResult, long currentAlbum, long totalAlbums, IGnCancellable canceller);

/** 
*  Callback function declaration for a result available notification. 
*  @param matchesResult	[in] Match response 
*  @param currentAlbum 	[in] Current number of the album in this response 
*  @param totalAlbums 		[in] Total number of albums in this response 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*  <p><b>Remarks:</b></p> 
*  The provided response will include results for one or more files. 
*/ 
 
  	public void musicIdFileMatchResult(GnResponseDataMatches matchesResult, long currentAlbum, long totalAlbums, IGnCancellable canceller);

/** 
*  Callback function declaration for a no results notification. 
*  @param fileInfo 		[in] Set FileInfo object that the callback operates on 
*  @param currentFile 		[in] Current number of the file that is not found 
*  @param totalFiles 		[in] Total number of files to be processed 
*  @param canceller		[in] Object that can be used to cancel processing if desired 
*/ 
 
  	public void musicIdFileResultNotFound(GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller);

/** 
*  Callback function declaration for MusicID-File processing completion. 
*  @param completeError 	[in] Final error value of MusicID-File operation 
*/ 
 
  	public void musicIdFileComplete(GnError completeError);
  	
  	public void statusEvent(GnStatus status, long percentComplete, long bytesTotalSent, long bytesTotalReceived, IGnCancellable canceller);

}
