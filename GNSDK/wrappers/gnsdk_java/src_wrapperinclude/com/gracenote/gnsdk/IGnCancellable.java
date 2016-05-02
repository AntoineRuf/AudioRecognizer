package com.gracenote.gnsdk;

/** 
* Interface for defining a Cancellable object 
*/ 
 
public interface IGnCancellable{

/** 
* Set cancel state 
* @param bCancel 	[in] Cancel state 
*/ 
 
	public void setCancel(boolean bCancel);
	
/** 
* Get cancel state 
* @return True of cancelled, false otherwise 
*/ 
 
	public boolean isCancelled();

}

