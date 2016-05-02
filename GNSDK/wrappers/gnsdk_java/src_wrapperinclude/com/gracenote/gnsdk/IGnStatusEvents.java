package com.gracenote.gnsdk;

/** 
* Delegate interface for receiving status updates as GNSDK operations are performed. 
*/ 
 
public interface IGnStatusEvents{

/** 
* Status change notification method. Override to receive notification. 
* @param status				[in] Status type 
* @param percentComplete		[in] Operation progress 
* @param bytesTotalSent		[in] Total number of bytes sent 
* @param bytesTotalReceived	[in] Total number of bytes received 
* @param canceller				[in] Object that can be used to canel the operation 
*/ 
 
	public void statusEvent(GnStatus status, long percentComplete, long bytesTotalSent, long bytesTotalReceived, IGnCancellable canceller);

}

