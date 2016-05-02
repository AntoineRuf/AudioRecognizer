package com.gracenote.gnsdk;

class IGnMusicIdFileInfoEventsProxyU extends IGnMusicIdFileInfoEventsProxyL{

	private IGnMusicIdFileInfoEvents interfaceReference;

  	IGnMusicIdFileInfoEventsProxyU (IGnMusicIdFileInfoEvents interfaceReference) {
    	this.interfaceReference = interfaceReference;
  	}

	@Override
  	public void gatherFingerprint(GnMusicIdFileInfo fileinfo, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.gatherFingerprint(fileinfo, currentFile, totalFiles, canceller);
  		}
  	}
	@Override
  	public void gatherMetadata(GnMusicIdFileInfo fileinfo, long currentFile, long totalFiles, IGnCancellable canceller) {
  		if ( interfaceReference != null ) {
  			interfaceReference.gatherMetadata(fileinfo, currentFile, totalFiles, canceller);
  		}  	
  	}

}
