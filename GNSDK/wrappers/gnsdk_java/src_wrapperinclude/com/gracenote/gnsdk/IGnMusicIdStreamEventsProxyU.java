package com.gracenote.gnsdk;

class IGnMusicIdStreamEventsProxyU extends IGnMusicIdStreamEventsProxyL {

	private IGnMusicIdStreamEvents interfaceReference;

	IGnMusicIdStreamEventsProxyU (IGnMusicIdStreamEvents interfaceReference) {
		this.interfaceReference = interfaceReference;
	}
	
	@Override
	public void musicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable canceller) {
		if ( interfaceReference != null ) {
			interfaceReference.musicIdStreamProcessingStatusEvent( status, canceller );
		}
	}
	
	@Override
	public void musicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable canceller) {
		if ( interfaceReference != null ) {
			interfaceReference.musicIdStreamIdentifyingStatusEvent( status, canceller );
		}
	}	

	@Override
	public void musicIdStreamAlbumResult(GnResponseAlbums result, IGnCancellable canceller) {
		if ( interfaceReference != null ) {
			interfaceReference.musicIdStreamAlbumResult( result, canceller );
		}
	}
	
	@Override
	public void musicIdStreamIdentifyCompletedWithError(GnError pErrorInfo) {
		if ( interfaceReference != null ) {
			interfaceReference.musicIdStreamIdentifyCompletedWithError( pErrorInfo );
		}
	}	
	
	@Override
	public void statusEvent( GnStatus status, long percent_complete, long bytes_total_sent, long bytes_total_received, IGnCancellable canceller ) {
  		if ( (interfaceReference != null) && (interfaceReference instanceof IGnStatusEvents) ) {
  			IGnStatusEvents statusEventsInterfaceReference = (IGnStatusEvents)interfaceReference;
  			statusEventsInterfaceReference.statusEvent( status, percent_complete, bytes_total_sent, bytes_total_received, canceller );
  		}
  	}	
	
}
