package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Delegate interface for receiving playlist synchronization events 
* <p> 
* Synchronization events are generated when a synchronization process is 
* executed. 
*/ 
 
public interface IGnPlaylistCollectionSyncEvents {

	public void onUpdate(GnPlaylistCollection collection, GnPlaylistIdentifier identifier, GnPlaylistEventsIdentiferStatus status, IGnCancellable canceller);

}
