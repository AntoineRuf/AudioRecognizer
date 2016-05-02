package com.gracenote.gnsdk;

/** 
* Delegate interface for providing persistent serialized Gracenote user object storage and retrieval 
*/ 
 
public interface IGnUserStore {
  
  	public GnString loadSerializedUser(String clientId);

  	public boolean storeSerializedUser(String clientId, String userData);

}
