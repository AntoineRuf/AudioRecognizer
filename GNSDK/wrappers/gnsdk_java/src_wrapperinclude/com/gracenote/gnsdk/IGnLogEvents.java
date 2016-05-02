package com.gracenote.gnsdk;

/** 
* Delegate interface for receiving logging messages from GNSDK 
*/ 
 
public interface IGnLogEvents {

	public boolean logMessage(int packageId, GnLogMessageType messageType, long errorCode, String message);

}
