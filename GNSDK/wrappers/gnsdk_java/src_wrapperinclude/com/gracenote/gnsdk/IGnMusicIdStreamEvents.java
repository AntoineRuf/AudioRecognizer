package com.gracenote.gnsdk;

/** 
* Delegate interface for receiving {@link GnMusicIdStream} events 
*/ 
 
public interface IGnMusicIdStreamEvents extends IGnStatusEvents {

/** 
* MusicIdStreamProcessingStatusEvent is currently considered to be experimental. 
* An application should only use this option if it is advised by Gracenote Global Services and Support representative. 
* Contact your Gracenote Global Services and Support representative with any questions about this enhanced functionality. 
* @param status		Status 
* @param canceller		Cancellable that can be used to cancel this processing operation 
*/ 
 
	public void musicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable canceller);
	
/** 
* Provides {@link GnMusicIdStream} identifying status notification 
* @param status		Status 
* @param canceller		Cancellable that can be used to cancel this identification operation 
*/ 
 
	public void musicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable canceller);

/** 
* A result is available for a {@link GnMusicIdStream} identification request 
* @param result		Result 
* @param canceller		Cancellable that can be used to cancel this identification operation 
*/ 
 
	public void musicIdStreamAlbumResult(GnResponseAlbums result, IGnCancellable canceller );
	
/** 
* Identifying request could not be completed due to the reported error condition 
* @param completeError	Error condition information 
*/ 
 
	public void musicIdStreamIdentifyCompletedWithError(GnError pErrorInfo);
	
	public void statusEvent(GnStatus status, long percentComplete, long bytesTotalSent, long bytesTotalReceived, IGnCancellable canceller);

}
