package com.gracenote.gnsdk;

class IGnPlaylistCollectionSyncEventsProxyU extends IGnPlaylistCollectionSyncEventsProxyL {

	private IGnPlaylistCollectionSyncEvents interfaceReference;
	
  	public IGnPlaylistCollectionSyncEventsProxyU( IGnPlaylistCollectionSyncEvents interfaceReference ) {
  		this.interfaceReference = interfaceReference;
	}
	
	@Override  
  	public void onUpdate(GnPlaylistCollection collection, GnPlaylistIdentifier identifier, GnPlaylistEventsIdentiferStatus status, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.onUpdate(collection, identifier, status, canceller);
  		}
  	}

}
