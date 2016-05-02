package com.gracenote.gnsdk;

class IGnMusicIdFileEventsProxyU extends IGnMusicIdFileEventsProxyL {
  
	private IGnMusicIdFileEvents interfaceReference;

	public IGnMusicIdFileEventsProxyU(IGnMusicIdFileEvents interfaceReference) {
		this.interfaceReference = interfaceReference;
	}

	@Override
	public void musicIdFileStatusEvent(GnMusicIdFileInfo fileinfo, GnMusicIdFileCallbackStatus status, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.musicIdFileStatusEvent(fileinfo, status, currentFile, totalFiles, canceller);
  		}
  	}

	@Override
  	public void gatherFingerprint(GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.gatherFingerprint(fileInfo, currentFile, totalFiles, canceller);
  		}  	
  	}

	@Override
  	public void gatherMetadata(GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.gatherMetadata(fileInfo, currentFile, totalFiles, canceller);
  		}   	
  	}

	@Override
  	public void musicIdFileAlbumResult(GnResponseAlbums album_result, long current_album, long total_albums, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.musicIdFileAlbumResult(album_result, current_album, total_albums, canceller);
  		}  	
  	}

	@Override
  	public void musicIdFileMatchResult(GnResponseDataMatches matches_result, long current_album, long total_albums, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.musicIdFileMatchResult(matches_result, current_album, total_albums, canceller);
  		}  	
  	}

	@Override
  	public void musicIdFileResultNotFound(GnMusicIdFileInfo fileinfo, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.musicIdFileResultNotFound(fileinfo, currentFile, totalFiles, canceller);
  		}  	  	
  	}

	@Override
  	public void musicIdFileComplete(GnError completeError) {
  		if ( interfaceReference != null ) {
  			interfaceReference.musicIdFileComplete( completeError );
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
